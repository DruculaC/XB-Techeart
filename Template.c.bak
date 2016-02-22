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

#include "Template.h"

// ------ Public variable definitions ------------------------------
bit Sw_pressed_G = 0; // The current switch status

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------
static bit LED_state_G;

// ------ Private constants ----------------------------------------
// SW_THRES must be > 1 for correct debounce behaviour
#define SW_THRES (3)

/*------------------------------------------------------------------*-
  SWITCH_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void SWITCH_Init(void)
   {
   Sw_pin = 1; // Use this pin for input
   }


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
