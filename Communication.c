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

#include "Communication.h"
#include "UART.h"
#include "Timer.h"

// ------ Public variable definitions ------------------------------
tByte myTxRxData[7];

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------

// ------ Private constants ----------------------------------------
bit Sent_G;

/*------------------------------------------------------------------*-
  UART_send_code()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void UART_send_code(void)
   {	
	myTxRxData[0] = 0x55;
	myTxRxData[1] = 0x55;
	myTxRxData[2] = 0xff;
	myTxRxData[3] = 0x55;
	myTxRxData[4] = 0x50;
	myTxRxData[5] = 0x00;
	Senddata(myTxRxData, 6);
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
