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

#include "hSch51.h"
#include "Clock.h"
#include "Battery.h"
#include "Speech.h"
#include "Receiver.h"

// ------ Public variable definitions ------------------------------
extern bit Alarm_G;
extern bit ID_certificated_G;
extern bit System_EN_G;
extern tByte Speech_time;
extern bit XB_open_flag;
extern bit ID_disable_G;


// ------ Public variable declarations -----------------------------
bit hSCH_sleep_EN;
tByte hSCH_sleep_EN_time;
tByte ID_disable_time;

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
	
	hSCH_sleep_EN = 1;
	hSCH_sleep_EN_time = 0;
	
	ID_disable_G = 0;
	ID_disable_time = 0;
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
	// Change system status.
	System_change();
	
	// Reset RXD power after a short time.
	RXD_power_reset();
	
	if(ID_disable_G)
		{
		ID_disable_time += 1;
		if(ID_disable_time > 3)
			{
			ID_disable_time = 0;
			ID_disable_G = 0;
			}
		}
	
	if(hSCH_sleep_EN)
		{
		test_port = ~test_port;
		hSCH_sleep_EN_time += 1;
		if(hSCH_sleep_EN_time > 10)
			{
			hSCH_sleep_EN_time = 0;
			hSCH_sleep_EN = 0;
			XB_open_flag = 0;
			
			Speech_RST = 0;
			Speech_EN = 0;
			hSCH_Go_To_Sleep();
			}
		}	
	}

/*------------------------------------------------------------------*-
  System_change()
  Initialisation function for the switch library.
  1s/ticket.
-*------------------------------------------------------------------*/
void System_change(void)
	{
	if(ID_certificated_G)
		{
		ID_certificated_G = 0;
		System_EN_G = ~System_EN_G;
		// If system is enabled, deploy the vibration sensor and ultrasonic sensor.
		if(System_EN_G == 1)
			{
			Goto_speech(System_open);
			XB_open_flag = 0;
			}
		else
			{
			Goto_speech(System_closed);		
			XB_open_flag = 0;
			}
		}
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
