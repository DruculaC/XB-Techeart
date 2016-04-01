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

#include "Alarm.h"
#include "IIC.h"
#include "Speech.h"
#include "Timer.h"

// ------ Public variable definitions ------------------------------

// ------ Public variable declarations -----------------------------
extern bit KBI_G;

// ------ Private variables ----------------------------------------
tByte Sensor_Int_SourceSystem;
tByte Sensor_Int_SourceMFF;
bit Alarm_G;
// ------ Private constants ----------------------------------------


/*------------------------------------------------------------------*-
  Alarm_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Alarm_Init(void)
	{
	Sensor_Int_SourceSystem = 0;
	Sensor_Int_SourceMFF = 0;	
	Alarm_G = 0;
	}

/*------------------------------------------------------------------*-
  Alarm_update()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Alarm_update(void)
	{
	Analyse_KBI();
		
	if(Alarm_G)
		{
		Goto_speech(Ticktack);
		}
	}

/*------------------------------------------------------------------*-
  Analyse_KBI()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Analyse_KBI(void)
	{
	if(KBI_G)
		{		
		KBI_G = 0;
		
		Sensor_Int_SourceSystem = 0;
		Sensor_Int_SourceMFF = 0;
		
		// Read INT_SOURCE register(0x0c), determine source of interrupt.
		Sensor_Int_SourceSystem = Single_Read_IIC(0x0c);
		// Set up case statement to service all possible interrupts.
		if((Sensor_Int_SourceSystem &0x04) == 0x04)
			{
			// If it is MT_FF set the interrupt, read FF_MT_SRC register(0x16).
			Sensor_Int_SourceMFF = Single_Read_IIC(0x16);
			if((Sensor_Int_SourceMFF &0x80) == 0x80)
				{				
				Alarm_G = 1;
				}
			}
		}	
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
