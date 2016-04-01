/*------------------------------------------------------------------*-
   IIC.C (v1.00)
  ------------------------------------------------------------------
   IIC program for other program.

   COPYRIGHT
   ---------
   This code is copyright (c) 2016 by Richard Zhang.
-*------------------------------------------------------------------*/

#include "Main.h"
#include "Port.h"

#include "IIC.h"
#include "Delay.h"

// ------ Public variable definitions ------------------------------

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------
tByte IIC_buffer[8];		// IIC buffer data.
tByte CTRL_REG1_data;	// The data in CTRL_REG1.

// ------ Private constants ----------------------------------------


/*------------------------------------------------------------------*-
  IIC_Init()
  Program for IIC send a whole byte, include start stop and ack
-*------------------------------------------------------------------*/
void IIC_Init(void)
	{
	// Set the sensor in 100Hz ODR, Standby
	Single_Write_IIC(0x2a, 0x18);
	// ELE = 1, OAE = 1, enable X, Y, disable Z.
	Single_Write_IIC(0x15, 0xd8);
	// Threshold value is 1g for 0.063g/count.
	Single_Write_IIC(0x17, 0x10);
	// Debounce counter is 300ms, the value is 300ms/10ms = 30, 0x1e.
	Single_Write_IIC(0x18, 0x0a);
	// Enable FF_MT interrupt function.
	Single_Write_IIC(0x2d, 0x04);
	// Route the FF_MT interrupt to INT1 hardware pin.
	Single_Write_IIC(0x2e, 0x04);
	// Read the CTRL_REG1.
	CTRL_REG1_data = Single_Read_IIC(0x2a);
	CTRL_REG1_data |= 0x01;
	// Set the sensor in active mode.
	Single_Write_IIC(0x2A, CTRL_REG1_data);
	}

/*------------------------------------------------------------------*-
  Single_Write_IIC()
  Program for IIC send a whole byte, include start stop and ack
-*------------------------------------------------------------------*/
void Single_Write_IIC(tByte REG_Address, tByte REG_data)
	{
	IIC_Start();                  //起始信号
	IIC_SendByte(SlaveAddress);   //发送设备地址+写信号
	IIC_SendByte(REG_Address);    //内部寄存器地址
	IIC_SendByte(REG_data);       //内部寄存器数据
	IIC_Stop();                   //发送停止信号
	}

/*------------------------------------------------------------------*-
  Single_Read_IIC()
  Program for IIC read a whole byte, include start stop and ack
-*------------------------------------------------------------------*/
tByte Single_Read_IIC(tByte REG_Address)
	{  
	tByte REG_data;
	IIC_Start();                          //起始信号
	IIC_SendByte(SlaveAddress);           //发送设备地址+写信号
	IIC_SendByte(REG_Address);            //发送存储单元地址，从0开始	
	IIC_Start();                          //起始信号
	IIC_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	REG_data = IIC_RecvByte();            //读出寄存器数据
	IIC_SendACK(1);
	IIC_Stop();                           //停止信号
	return REG_data; 
	}

/*------------------------------------------------------------------*-
  Multiple_read_IIC()
  Program for IIC read a whole byte, include start stop and ack
-*------------------------------------------------------------------*/
void Multiple_read_IIC(tByte Start_add, tByte Read_count)
{   
	tByte i;
	IIC_Start();                          	//起始信号
	IIC_SendByte(SlaveAddress);           	//发送设备地址+写信号
	IIC_SendByte(Start_add);               //发送存储单元地址，从0x01开始	
	IIC_Start();                          	//起始信号
	IIC_SendByte(SlaveAddress+1);         	//发送设备地址+读信号
	for (i=0; i<Read_count; i++)   			//连续读取6个地址数据，存储中BUF
		{
		IIC_buffer[i] = IIC_RecvByte();     //IIC_buffer[0]存储0x32地址中的数据
		if (i == Read_count-1)
			{
			IIC_SendACK(1);                	//最后一个数据需要回NOACK
			}
		else
			{
			IIC_SendACK(0);                	//回应ACK
			}
		}
	IIC_Stop();                          	//停止信号
	Delay(LOOP_TIMEOUT_INIT_005ms);
	}

/*------------------------------------------------------------------*-
  IIC_SendByte()
  Program for IIC send a byte.
-*------------------------------------------------------------------*/
void IIC_SendByte(tByte dat)
	{
	tByte i;
	for (i=0; i<8; i++)        //8位计数器
		{
		dat <<= 1;              //移出数据的最高位
		SDA = CY;               //送数据口
		SCL = 1;                //拉高时钟线
		Delay5us();             //延时
		SCL = 0;                //拉低时钟线
		Delay5us();             //延时
		}
	IIC_RecvACK();
	}

/*------------------------------------------------------------------*-
  IIC_RecvByte()
  Program for IIC receive a byte.
-*------------------------------------------------------------------*/
tByte IIC_RecvByte()
	{
	tByte i;
	tByte dat = 0;

	SDA = 1;                   //使能内部上拉,准备读取数据,
	for (i=0; i<8; i++)        //8位计数器
		{
		dat <<= 1;
		SCL = 1;                //拉高时钟线
		Delay5us();             //延时
		dat |= SDA;             //读数据               
		SCL = 0;                //拉低时钟线
		Delay5us();             //延时
		}
	return dat;
	}

/*------------------------------------------------------------------*-
  IIC_Start()
  Program for IIC start signal.
-*------------------------------------------------------------------*/
void IIC_Start()
	{
	SDA = 1;
	SCL = 1;
	Delay5us();
	SDA = 0;
	Delay5us();
	SCL = 0;
	}

/*------------------------------------------------------------------*-
  IIC_Stop()
  Program for IIC stop signal.
-*------------------------------------------------------------------*/
void IIC_Stop()
	{
	SDA = 0;
	SCL = 1;
	Delay5us();
	SDA = 1;
	Delay5us();
	}

/*------------------------------------------------------------------*-
  IIC_SendACK()
  Program for IIC send ACK signal.
-*------------------------------------------------------------------*/
void IIC_SendACK(bit ack)
	{
	SDA = ack;
	SCL = 1;
	Delay5us();
	SCL = 0;
	Delay5us();
	}

/*------------------------------------------------------------------*-
  IIC_RecvACK()
  Program for IIC receive ACK signal.
-*------------------------------------------------------------------*/
bit IIC_RecvACK()
	{
	SCL = 1;
	Delay5us();
	CY = SDA;
	SCL = 0;
	Delay5us();
	return CY;
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/