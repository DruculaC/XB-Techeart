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

#include "Clock.h"
#include "Battery.h"
#include "Speech.h"

// ------ Public variable definitions ------------------------------
extern bit Alarm_G;

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------
tByte Clock_second;
tByte Clock_minute;

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  Clock_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Clock_Init(void)
	{
	Clock_second = 0;
	Clock_minute = 0;
	}

/*------------------------------------------------------------------*-
  Clock_update()
  Initialisation function for the switch library.
  1s/ticket.
-*------------------------------------------------------------------*/
void Clock_update(void)
	{
	Clock_second += 1;

	if(Clock_second >= 60)
		{
		Clock_second = 0;
		Clock_minute += 1;
		if(Clock_minute >= 60)
			{
			Clock_minute = 0;
			}
		
		// Detect battery every minute.
		Battery_detection();				
		}
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
