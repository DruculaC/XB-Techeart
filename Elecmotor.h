/*------------------------------------------------------------------*-
   A.H (v1.00)
  ------------------------------------------------------------------
   COPYRIGHT
   ---------
   This code is copyright (c) 2001 by Richard Zhang. 
-*------------------------------------------------------------------*/

// ------ Public data type declarations ----------------------------
// typedef tByte tBargraph;

// ------ Public constants -----------------------------------------
// #define BARGRAPH_MAX (255)
// #define BARGRAPH_MIN (0)
#define Elecmotor_code_head 0xc8
#define Elecmotor_code_address 0xe0
#define Elecmotor_code_open 0xc1

// ------ Public function prototypes -------------------------------
void Elecmotor_Init(void);
void Elecmotor_update(void);
void Elecmotor_coding(void);

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
