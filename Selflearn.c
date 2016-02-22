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

#include "Selflearn.h"
#include "Speech.h"
#include "ISP_DataFlash.h"
#include "UART.h"

// ------ Public variable definitions ------------------------------
bit Self_learn_G;

// ------ Public variable declarations -----------------------------
extern bit Received_finished_G;
extern tByte Received_cache[7];

// ------ Private variables ----------------------------------------
tWord Self_learn_HVtime;
tByte Self_learn_level;
tByte Self_learn_mode_duration;

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  SWITCH_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Selflearn_Init(void)
   {
	// Set Self_learn_port (P0.1) to input mode.
	P0M1 |= 0x02;
	P0M2 &= 0xfd;
 	Self_learn_level = 0;
	Self_learn_mode_duration = 0;
	}

/*------------------------------------------------------------------*-
  Selflearn_detection()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Selflearn_detection(void)
   {
	if((Key_switch)&&(Self_learn_port))
		{
		Self_learn_HVtime += 1;
		if(Self_learn_HVtime >= 6000)
			{
			Self_learn_HVtime = 6001;
			Self_learn_level = 0;
			Self_learn_G = 0;
			}
		}
	else if((Key_switch)&&(!Self_learn_port))
		{
		if(Self_learn_HVtime >= 300)
			{
			Self_learn_HVtime = 0;
			Self_learn_level += 1;
			}
		}
		
	if(Self_learn_level > 5)
		{
		Self_learn_level = 0;
		Self_learn_G = 1;
		Goto_speech(Ticktack);
		}
	}

/*------------------------------------------------------------------*-
  Self_learn_action()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Self_learn_action(void)
	{
	if(Self_learn_G)
		{
		if(Received_finished_G)
			{
			Self_learn_programming();
			Received_finished_G = 0;
			Self_learn_G = 0;
			Goto_speech(Ticktack);
			}
		}
	}

/*------------------------------------------------------------------*-
  Self_learn_reset()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Self_learn_reset(void)
	{
	if(Self_learn_G)
		{
		Self_learn_mode_duration += 1;
		if(Self_learn_mode_duration > 5)
			{
			Self_learn_mode_duration = 0;
			Self_learn_G = 0;
			}
		}
	}

/*------------------------------------------------------------------*-
  Self_learn_programming()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Self_learn_programming(void)
	{
	Flash_Page_Erase(0x3000);
	Flash_Write_Data(0x3000, Received_cache[5]);		
	Flash_Write_Data(0x3001, Received_cache[4]);		
	Flash_Write_Data(0x3002, Received_cache[3]);		
	Flash_Write_Data(0x3003, Received_cache[2]);		
	Flash_Write_Data(0x3004, Received_cache[1]);
	Flash_Write_Data(0x3005, Received_cache[0]);
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
