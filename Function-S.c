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

#include "Function-S.h"
#include "ISP_DataFlash.h"
#include "Speech.h"
#include "Selflearn.h"
#include "Protection.h"

// ------ Public variable definitions ------------------------------
bit Vehicle_poweron_EN;		// Enable flag for vehicle's sorts of power.

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------
tWord Vehicle_poweron_time;	// Delay time of vehicle's power on.

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  Self_learn_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Function_s_update(void)
   {
	Selflearn_detection();
	Self_learn_action();
	
	Protection_Vibration_detection();
	
	Vehicle_poweron_detection();
	}

/*------------------------------------------------------------------*-
  Vehicle_poweron_detection()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Vehicle_poweron_detection(void)
   {
	if(Vehicle_poweron_EN)
		{
		Vehicle_poweron_time += 1;
		if(Vehicle_poweron_time > 2000)
			{
			Vehicle_poweron_time = 0;
			// Turn on electrical vehicle's sorts of power.
			Hall_control = 0;
			Controller_lock = 0;
			Elecdoor_lock = 1;
			Vehicle_poweron_EN = 0;	
			}
		}
	}

/*------------------------------------------------------------------*-
  Function_S_init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Function_S_init(void)
   {
	Selflearn_Init();
	Protection_init();
	
	Vehicle_poweron_EN = 0;
	Vehicle_poweron_time = 0;
	}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
