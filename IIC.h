/*------------------------------------------------------------------*-
   IIC.H (v1.00)
  ------------------------------------------------------------------
   COPYRIGHT
   ---------
   This code is copyright (c) 2016 by Richard Zhang. 
-*------------------------------------------------------------------*/

// ------ Public data type declarations ----------------------------

// ------ Public constants -----------------------------------------
//#define	SlaveAddress 0x3a 			// Slave address for MMA8451, SA0 = 1.
#define	SlaveAddress 0x38					// Slave address for MMA8451, SA0 = 0;


// ------ Public function prototypes -------------------------------
// void IIC_Init(void);
// void Multiple_read_IIC(tByte Start_add, tByte Read_count);
void Single_Write_IIC(tByte REG_Address, tByte REG_data);
tByte Single_Read_IIC(tByte REG_Address);
void IIC_SendByte(tByte dat);
tByte IIC_RecvByte();
void IIC_Start();
void IIC_Stop();
void IIC_SendACK(bit ack);
bit IIC_RecvACK();
void IIC_Init(void);

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
