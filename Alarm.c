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
#include "Speech.h"

// ------ Public variable definitions ------------------------------
bit Sensor_to_alarm;
bit Alarm_blocked_G;

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------
tByte Alarm_number;

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  Alarm_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Alarm_Init(void)
   {
	Alarm_blocked_G = 0;
	Alarm_number = 0;
   }

/*------------------------------------------------------------------*-
  Alarm_update()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Alarm_update(void)
   {
	if((Sensor_to_alarm)&&(!Speech_EN)&&(!Alarm_blocked_G))
		{
		Goto_speech(Siren);
		
		Alarm_number += 1;
		if(Alarm_number >= 4)
			{
			Alarm_number = 0;
			Sensor_to_alarm = 0;
			}
		}
	}

/*------------------------------------------------------------------*-
  Alarm_reset()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Alarm_reset(void)
   {
	Alarm_number = 0;
	Sensor_to_alarm = 0;
	Speech_EN = 0;
	Alarm_blocked_G = 0;
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
