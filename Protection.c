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

#include "Protection.h"

// ------ Public variable definitions ------------------------------
bit Vibration_G_elecmotor;
bit Vibration_G_wireless;
tWord Vibration_reset_time;
tByte Protection_count_time;
// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------

// ------ Private constants ----------------------------------------
/*------------------------------------------------------------------*-
  Protection_init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Protection_init(void)
   {
	Vibration_G_elecmotor = 0;
	Vibration_G_wireless = 0;
	Vibration_reset_time = 0;
	Protection_count_time = 0;
	}

/*------------------------------------------------------------------*-
  Protection_Vibration_detection()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Protection_Vibration_detection(void)
   {
	if((!Vertical_sensor)||(!Horizontal_sensor)||(!Micromotion_sensor)||(wheeled_rotate))
		{
		Protection_count_time += 1;
		if(Protection_count_time >= 2)
			{
			Vibration_G_elecmotor = 1;
			Vibration_G_wireless = 1;
			Vibration_reset_time = 0;			
			}	
		}
	else
		Protection_count_time = 0;
		
	if((Vibration_G_elecmotor)||(Vibration_G_wireless))
		{
		Vibration_reset_time += 1;
		if(Vibration_reset_time > 5000)
			{
			Vibration_G_elecmotor = 0;
			
			if(Vibration_reset_time > 10000)
				{
				Vibration_reset_time = 0;
				Vibration_G_wireless = 0;
				}
			}
		}
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
