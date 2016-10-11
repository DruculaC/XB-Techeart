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
#include "Receiver.h"

// ------ Public variable definitions ------------------------------

// ------ Public variable declarations -----------------------------
extern bit KBI_G;
extern bit Alarm_G;
extern tByte hSCH_sleep_EN_time;

// ------ Private variables ----------------------------------------
tByte Alarm_speech_level;

// ------ Private constants ----------------------------------------


/*------------------------------------------------------------------*-
  Alarm_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Alarm_Init(void)
	{
	Alarm_speech_level = 0;
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
		RXD_power_on();
		if(Speech_EN == 0)
			{
			switch(Alarm_speech_level)
				{
				case 0:
					{
					Alarm_speech_level = 1;
					Goto_speech(Catch_thief);
					}
				break;
				case 1:
					{
					Alarm_speech_level = 0;
					Goto_speech(Siren);
					}
				break;
				}			
			}
		hSCH_sleep_EN_time = 0;
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
		}	
	}
	
/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/