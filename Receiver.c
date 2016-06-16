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

#include "Receiver.h"
#include "Speech.h"

// ------ Public variable definitions ------------------------------

// ------ Public variable declarations -----------------------------
extern bit XB_open_flag;

// ------ Private variables ----------------------------------------
tByte RXD_power_EN_time;

// ------ Private constants ----------------------------------------
/*------------------------------------------------------------------*-
  Receiver_init()
  Reset RXD power after 10s.
-*------------------------------------------------------------------*/
void Receiver_init(void)
	{
	RXD_power_EN_time = 0;
	RXD_power_EN = 1;
	ID_module_EN = 0;
//	RXD = 0;
	}

/*------------------------------------------------------------------*-
  RXD_power_reset()
  Reset RXD power after 10s.
-*------------------------------------------------------------------*/
void RXD_power_reset(void)
	{
	if(RXD_power_EN == 0)
		{
		RXD_power_EN_time += 1;
		if(RXD_power_EN_time > 9)
			{
			RXD_power_off();
			
			if(XB_open_flag)
				XB_open_flag = 0;
			}
		}	
	}

/*------------------------------------------------------------------*-
  RXD_power_on()
  Reset RXD power after 10s.
-*------------------------------------------------------------------*/
void RXD_power_on(void)
	{
	RXD_power_EN_time = 0;
	RXD_power_EN = 0;
	ID_module_EN = 1;
//	Speech_reset();
//	RXD = 1;
	}

/*------------------------------------------------------------------*-
  RXD_power_off()
  Reset RXD power after 10s.
-*------------------------------------------------------------------*/
void RXD_power_off(void)
	{
	RXD_power_EN_time = 0;
	RXD_power_EN = 1;
	ID_module_EN = 0;
//	RXD = 0;
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
