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

#include "KBI.h"
#include "Receiver.h"
#include "IIC.h"
#include "Speech.h"

// ------ Public variable definitions ------------------------------
bit KBI_G;
// ------ Public variable declarations -----------------------------
extern bit System_EN_G;
extern bit hSCH_sleep_EN;

// ------ Private variables ----------------------------------------
tByte Sensor_Int_SourceSystem;
tByte Sensor_Int_SourceMFF;
tByte Sensor_Int_SourcePulse;
tByte Sensor_Int_SourceTransient;
tByte Sensor_Int_SourcePL;

bit Alarm_G;
bit Device_layflat_G;
// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  KBI_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void KBI_Init(void)
	{
	KBI_G = 0;
	
	// Set P0.4, PIN23 to input mode, Sensor_INT1
	P0M1 |= 0x10;
	P0M2 &= 0xef;

	// Set PIN23, PIN24 to low voltage interrupt, PIN26 to high pulse interrupt.
	KBLS1 |= 0x18;
	KBLS0 |= 0x1a;
	// Set KBI flag and enable.
	KBIF &= 0xe5;
	KBIE |= 0x1a;
	EKB = 1;

	Sensor_Int_SourceSystem = 0;
	Sensor_Int_SourceMFF = 0;
	Sensor_Int_SourcePulse = 0;
	Sensor_Int_SourceTransient = 0;
	Sensor_Int_SourcePL = 0;
	Alarm_G = 0;
	Device_layflat_G = 0;
	}

/*-----------------------------------------------------------
	KBI_ISR()
	键盘中断，使芯片从省电模式中唤醒
-----------------------------------------------------------*/
void KBI_ISR(void) interrupt 7
	{
	KBIF &= 0xe5;

	// Enable PD sleep mode.
	hSCH_sleep_EN = 1;
	
	Sensor_Int_SourceSystem = 0;
	Sensor_Int_SourceMFF = 0;
	Sensor_Int_SourceTransient = 0;
	Sensor_Int_SourcePulse = 0;
	Sensor_Int_SourcePL = 0;
	
	// Read INT_SOURCE register(0x0c), determine source of interrupt.
	Sensor_Int_SourceSystem = Single_Read_IIC(0x0c);
	
	// Set up case statement to service all possible interrupts.
	// If it is double tap pulse.
	if((Sensor_Int_SourceSystem &0x08) == 0x08)
		{
		// If it is ta set the interrupt, read FF_MT_SRC register(0x16).
		Sensor_Int_SourcePulse = Single_Read_IIC(0x22);
		if((Sensor_Int_SourcePulse &0x80) == 0x80)
			{				
			RXD_power_on();
			}
		return;
		}

	// If it is motion and free fall.
	if((Sensor_Int_SourceSystem &0x04) == 0x04)
		{
		// If it is MT_FF set the interrupt, read FF_MT_SRC register(0x16).
		Sensor_Int_SourceMFF = Single_Read_IIC(0x16);
		if(((Sensor_Int_SourceMFF &0x80) == 0x80)&&(System_EN_G))
			{				
			Alarm_G = 1;
			}
		}
	// If it is transient.
	if((Sensor_Int_SourceSystem &0x20) == 0x20)
		{
		// If it is MT_FF set the interrupt, read FF_MT_SRC register(0x16).
		Sensor_Int_SourceTransient = Single_Read_IIC(0x1e);
		if(((Sensor_Int_SourceTransient &0x40) == 0x40)&&(System_EN_G)&&(Device_layflat_G))
			{				
			Alarm_G = 1;
			}
		}
	
	// If it is Portait and Landscape.
	if((Sensor_Int_SourceSystem &0x10) == 0x10)
		{
		// If it is MT_FF set the interrupt, read FF_MT_SRC register(0x16).
		Sensor_Int_SourcePL = Single_Read_IIC(0x10);
		if((Sensor_Int_SourcePL &0x40) == 0x40)
			{				
			Device_layflat_G = 1;
			}
		else
			{
			Device_layflat_G = 0;
			}
			
		if(((Sensor_Int_SourcePL &0xc0) == 0x80)&&(System_EN_G))
			{
			Alarm_G = 1;
			}	
		}

	
	KBI_G = 1;
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
