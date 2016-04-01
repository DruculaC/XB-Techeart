/*------------------------------------------------------------------*-
   Button.c (v1.00)
  ------------------------------------------------------------------
   Motor key button detecting for motor vehicle.

   COPYRIGHT
   ---------
   This code is copyright (c) 2016 by Richard Zhang.
-*------------------------------------------------------------------*/

#include "Main.h"
#include "Port.h"

#include "Button.h"
#include "Selflearn.h"
#include "Speech.h"

// ------ Public variable definitions ------------------------------
bit System_EN_G;		// Flag for system enabled, 0 for not enabled, 1 for enabled.

// ------ Public variable declarations -----------------------------
extern bit ID_certificated_G;

// ------ Private variables ----------------------------------------
tByte XB_reed_HVtime;
tByte XB_reed_level;

// ------ Private constants ----------------------------------------


/*------------------------------------------------------------------*-
  Button_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Button_Init(void)
   {
	// Set P0.4(XB_reed_switch_port) to input mode.
	P0M1 |= 0x02;
	P0M2 &= 0xfd;
	
	XB_reed_HVtime = 0;
	XB_reed_level = 0;
	System_EN_G = 0;
	}

/*------------------------------------------------------------------*-
	Button_update()
	Update motor's key button, 1 for open, 0 for close, 50ms/ticket
-*------------------------------------------------------------------*/
void Button_update(void)
   {	
	XB_reed_detection();
	
	Self_learn_action();
	
	// Instant broadcast "tick" voice
	Speech_s_update();
	}

/*------------------------------------------------------------------*-
	XB_reed_detection()
-*------------------------------------------------------------------*/
void XB_reed_detection(void)
	{
	if(XB_reed_switch_port)
		{
		XB_reed_HVtime += 1;
		// If exceed 3s, then reset.
		if(XB_reed_HVtime > 60)
			{
			XB_reed_HVtime = 0;
			XB_reed_level = 0;
			}
		}
	else
		{
		if(XB_reed_HVtime >= 4)
			{
			XB_reed_HVtime = 0;
			XB_reed_level += 1;
			}
		}

	// If open and close for 3 times, triggle.
	if(XB_reed_level >= 3)
		{
		XB_reed_level = 0;
		System_EN_G = ~System_EN_G;
		// If system is enabled, deploy the vibration sensor and ultrasonic sensor.
		if(System_EN_G == 1)
			Goto_speech(System_open);
		else
			Goto_speech(System_closed);
		}	
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
