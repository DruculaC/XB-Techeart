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
extern bit Alarm_G;

// ------ Public variable declarations -----------------------------
bit System_EN_G;		// Flag for system enabled, 0 for not enabled, 1 for enabled.
bit XB_open_flag;
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
	XB_open_flag = 0;
	}

/*------------------------------------------------------------------*-
	Button_update()
	Update motor's key button, 1 for open, 0 for close, 100ms/ticket
-*------------------------------------------------------------------*/
void Button_update(void)
   {
	XB_reed_detection();
	
	Self_learn_action();
	}

/*------------------------------------------------------------------*-
	XB_reed_detection()
-*------------------------------------------------------------------*/
void XB_reed_detection(void)
	{
	if((System_EN_G)&&(XB_reed_switch_port)&&(XB_open_flag == 0))
		{
		Alarm_G = 1;
		}
	else if(!XB_reed_switch_port)
		{
		XB_open_flag = 0;
		}
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
