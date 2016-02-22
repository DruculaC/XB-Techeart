/*------------------------------------------------------------------*-
   Delay.C (v1.00)
  ------------------------------------------------------------------
   Delay program for other program.

   COPYRIGHT
   ---------
   This code is copyright (c) 2001 by Richard Zhang.
-*------------------------------------------------------------------*/

#include "Main.h"
#include "Port.h"

#include "Delay.h"

// ------ Public variable definitions ------------------------------

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------
tWord Timeout_loop;

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  SWITCH_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Delay(tWord time_a)
   {
   Timeout_loop = time_a;

   // Simple loop timeout...
   while(++Timeout_loop != 0);
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
