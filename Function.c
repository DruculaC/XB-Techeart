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

#include "Function.h"
#include "Sensor.h"
#include "Selflearn.h"
#include "Protection.h"
#include "Battery.h"

// ------ Public variable definitions ------------------------------
tByte ID_certificated_time;
bit Auto_close_G;
tByte Auto_close_time;

// ------ Public variable declarations -----------------------------
extern bit ID_certificated_G;
extern bit Program_blocked_G;
extern bit Sensor_delay_EN;
extern tByte Sensor_delay_time;
extern tByte ID_certificated_count;
extern bit Disable_alarm_mode_G;

// ------ Private variables ----------------------------------------

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  Function_update()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Function_update(void)
   {
	// Detecting electrical vehicle's battery every 2s.
	Battery_detection();
	
	// ID expiring 10s.
	ID_certificated_expire();
	
	// Enable sensor 20s after closing lock.
	Sensor_postpone();
	
	Auto_close_detection();
   }

/*------------------------------------------------------------------*-
  Auto_close_detection()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Auto_close_detection(void)
   {
   if((Vertical_sensor)&&(Horizontal_sensor)&&(Micromotion_sensor)&&(!wheeled_rotate))
		{
		Auto_close_time += 1;
		if(Auto_close_time > 60)
			{
			Auto_close_time = 11;
			Auto_close_G = 1;
			}
		}
	else
		Auto_close_time = 0;
	}

/*------------------------------------------------------------------*-
  Function_init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Function_init(void)
   {
	ID_reset();
	
	Auto_close_time = 0;
	Auto_close_G = 0;
   }

/*------------------------------------------------------------------*-
  ID_reset()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void ID_reset(void)
   {
	ID_certificated_time = 0;
	ID_certificated_G = 0;
	ID_certificated_count = 0;
	}

/*------------------------------------------------------------------*-
  ID_certificated_expire()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void ID_certificated_expire(void)
   {
	// Reset the ID certification.
	if((ID_certificated_G)&&(!Program_blocked_G))
		{
		ID_certificated_time += 1;
		if(ID_certificated_time > 5)
			{
			// Reset ID and enable sensor detecting.
			ID_reset();
			Sensor_enable();
			}		
		}
	}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
