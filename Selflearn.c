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
#include "Receiver.h"

// ------ Public variable definitions ------------------------------
tByte Passwd_reed_switch_time;
// ------ Public variable declarations -----------------------------
extern bit Received_finished_G;
extern tByte Received_cache[7];

extern bit hSCH_sleep_EN;
extern bit Passwd_reed_switch_port;

// ------ Private variables ----------------------------------------

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  Selflearn_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Selflearn_Init(void)
   {
	// Set P0.3(Passwd_reed_switch_port) to input mode.
//	P2M1 |= 0x20;
//	P2M2 &= 0xdf;
	
	Passwd_reed_switch_time = 0;
	}


/*------------------------------------------------------------------*-
  Self_learn_action()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Self_learn_action(void)
	{
	if(!Passwd_reed_switch_port)
		RXD_power_on();

	if((!Passwd_reed_switch_port)&&(Received_finished_G))
		{
		Goto_speech(Ticktack);
		Self_learn_programming();
		Received_finished_G = 0;
		
		// Close passwd matching.
		Passwd_reed_switch_port = 1;
		}
	}

/*------------------------------------------------------------------*-
  Self_learn_reset()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Self_learn_reset(void)
	{
	if(!Passwd_reed_switch_port)
		{
		Passwd_reed_switch_time += 1;
		if(Passwd_reed_switch_time > 10)
			{
			Passwd_reed_switch_time = 0;
			Passwd_reed_switch_port = 1;
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
