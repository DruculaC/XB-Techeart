/*------------------------------------------------------------------*-
   A.H (v1.00)
  ------------------------------------------------------------------
   COPYRIGHT
   ---------
   This code is copyright (c) 2001 by Richard Zhang. 
-*------------------------------------------------------------------*/

// ------ Public data type declarations ----------------------------

// ------ Public constants -----------------------------------------
// *** Timings vary with compiler optimisation settings ***
#define LOOP_TIMEOUT_INIT_001ms 65444
#define LOOP_TIMEOUT_INIT_005ms 65075
#define LOOP_TIMEOUT_INIT_010ms 64615
#define LOOP_TIMEOUT_INIT_012ms 64430
#define LOOP_TIMEOUT_INIT_050ms 60931
#define LOOP_TIMEOUT_INIT_100ms 56326
#define LOOP_TIMEOUT_INIT_500ms 19486

// ------ Public function prototypes -------------------------------
void Delay(tWord timer);
void Delay5us(void);

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
