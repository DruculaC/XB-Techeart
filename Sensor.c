/*------------------------------------------------------------------*-
   A.C (v1.00)
  ------------------------------------------------------------------
   Simple switch interface code, with software debounce.

   COPYRIGHT
   ---------
   This code is copyright (c) 2001 by Richard Zhang.
-*------------------------------------------------------------------*/

#include "Main.h"
#include "Port.h"

#include "Sensor.h"
#include "IIC.h"

// ------ Public variable definitions ------------------------------

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------
tByte CTRL_REG1_data;	// The data in CTRL_REG1.

// ------ Private constants ----------------------------------------


/*------------------------------------------------------------------*-
  Sensor_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Sensor_Init(void)
   {
 	// Set the sensor in 400Hz ODR, Standby
	Single_Write_IIC(0x2a, 0x08);
 	// Set the sensor in LP mode.
	Single_Write_IIC(0x2b, 0x03);
	
	/*- Set_PULSE -*/
	// Enable X, Yand Z double pulse with DPA = 0, no double pulse abort.
	Single_Write_IIC(0x21, 0x2a);
	// Set Threshold 3g on X and Y, 5g on Z, 0.063g/LSB
	// Set Threshold 1g on X, Y and Z, 0.063g/LSB, 1g/0.063 = 16 = 0x10.
	Single_Write_IIC(0x23, 0x08);
	Single_Write_IIC(0x24, 0x08);
	Single_Write_IIC(0x25, 0x08);
	// Set time limit for tap detection to 60ms LP mode.
	Single_Write_IIC(0x26, 0x30);
	// Set Latency time to 200ms
	// Set Latency time to 100ms, 100ms/2.5 = 40 = 0x28
	Single_Write_IIC(0x27, 0x28);
	// Set time window for second tap to 300ms.
	// Set time window for second tap to 500ms, 500ms/2.5 = 200 = 0xc8
	Single_Write_IIC(0x28, 0xc8);

	/*- Set_FF_MT -*/
	// ELE = 1, OAE = 1, enable X, Y, Z.
	Single_Write_IIC(0x15, 0xe0);
	// Threshold value is 1g for 0.063g/count, 1g/0.063 = 16 = 0x10.
	// Threshold value is 1g for 0.063g/count, 0.5g/0.063 = 8 = 0x08.
	Single_Write_IIC(0x17, 0x10);
	// Debounce counter is 300ms with ODR 400Hz and LP mode, the value is 300ms/2.5ms = 120, 0x78.
	// Debounce counter is 100ms with ODR 400Hz and LP mode, the value is 100ms/2.5ms = 40, 0x28.
	Single_Write_IIC(0x18, 0x28);
		
	/*- Set_Transient -*/
	// ELE = 1, enable X, Y, Z.
	// ELE = 1, enable X, Y.
	Single_Write_IIC(0x1d, 0x16);
	// Threshold value is 1g for 0.063g/count, 0.5g/0.063 = 8 = 0x08.
	Single_Write_IIC(0x1f, 0x01);
	// Debounce counter is 50ms with ODR 400Hz and LP mode, the value is 50ms/2.5ms = 20, 0x14.
	Single_Write_IIC(0x20, 0x28);
	
	/*- Set_PL -*/
	// Set PL_EN, enable orientation detection
	Single_Write_IIC(0x11, 0x40);
	// Set back/front angle trip threshold to 11, Z < 65, 
	// Set Z-lockout angle trip threshold to 111, 43 degree.
	Single_Write_IIC(0x13, 0xc7);
	// Set XY trip threshold angle to 0x07<<3, 15 degrees.
	// Set hysteresis to 0x04, 14 degrees.
	Single_Write_IIC(0x14, 0x3c);
	// Set Debounce counter, 100ms/2.5 = 40, 0x28.
	Single_Write_IIC(0x12, 0x28);
	
	/*- Set INT1 -*/
	// Route INT1 to System interrupt.
	Single_Write_IIC(0x2d, 0x3c);
	Single_Write_IIC(0x2e, 0x3c);
	
	// Read the CTRL_REG1.
	CTRL_REG1_data = Single_Read_IIC(0x2a);
	CTRL_REG1_data |= 0x01;
	// Set the sensor in active mode.
	Single_Write_IIC(0x2a, CTRL_REG1_data);
	}

/*------------------------------------------------------------------*-
  Set_FF_MT()
  Initialisation function for the switch library.
void Set_FF_MT(void)
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
	
-*------------------------------------------------------------------*/

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
