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

// ------ Public variable declarations -----------------------------
extern bit Received_finished_G;
extern tByte Received_cache[7];

// ------ Private variables ----------------------------------------

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  Selflearn_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Selflearn_Init(void)
   {
	// Set P0.3(Passwd_reed_switch_port) to input mode.
	P2M1 |= 0x20;
	P2M2 &= 0xdf;
	}


/*------------------------------------------------------------------*-
  Self_learn_action()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Self_learn_action(void)
	{
	if((Passwd_reed_switch_port)&&(Received_finished_G))
		{
		Goto_speech(Ticktack);
		Self_learn_programming();
		Received_finished_G = 0;
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
