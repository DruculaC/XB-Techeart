/*------------------------------------------------------------------*-
   Button.C (v1.00)
  ------------------------------------------------------------------
   Motor key button detecting for motor vehicle.

   COPYRIGHT
   ---------
   This code is copyright (c) 2015 by Richard Zhang.
-*------------------------------------------------------------------*/

#include "Main.h"
#include "Port.h"

#include "Button.h"
#include "Elecmotor.h"

// ------ Public variable definitions ------------------------------
bit Key_switch_on_G;		// Flag for motor key turned on.

bit Program_blocked_G;	// When excuting program, block detecting button.

// ------ Public variable declarations -----------------------------
extern tByte Magnet_code[3];
extern bit Vibration_G_elecmotor;

// ------ Private variables ----------------------------------------

// ------ Private constants ----------------------------------------
tByte Key_switch_on_time;		// Time of motor's key turning on.
tByte Key_switch_off_time;		// Time of motor's key turning off.

/*------------------------------------------------------------------*-
  Button_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Button_Init(void)
   {
   Key_switch = 1;	// Use this pin for input
   Key_switch_on_time = 0;
	}

/*------------------------------------------------------------------*-
	Button_update()
	Update motor's key button, 1 for open, 0 for close, 100ms/ticket
-*------------------------------------------------------------------*/
void Button_update(void)
   {
	// If other program is excuting or speeching, block detecting the button status.
	if((Program_blocked_G)||(Speech_EN))
		return;
		
	// if Key = high, it means motor key is turn on.
	if(Key_switch == 1)
		{		
		// Detect 5 times for debounce.
		Key_switch_on_time += 1;
		if(Key_switch_on_time > 5)
			{
			Key_switch_on_time = 5;
			// Set the flag.
			Key_switch_on_G = 1;			
			return;
			}
		
		Key_switch_off_time = 0;
		return;
		}
	// If Key_switch not turn on, then reset the time.
	Key_switch_on_time = 0;

	// If motor has not been vibrated in 5s, detecting motor key turn off state.
	if(!Vibration_G_elecmotor)
		{
		// Detect 15 times for debounce, about 1.5s.
		Key_switch_off_time += 1;
		if(Key_switch_off_time > 15)
			{
			Key_switch_off_time = 15;
			// Reset the flag.
			Key_switch_on_G = 0;
			}
		}
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
