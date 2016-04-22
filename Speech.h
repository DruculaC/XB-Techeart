/*------------------------------------------------------------------*-
   A.H (v1.00)
  ------------------------------------------------------------------
   COPYRIGHT
   ---------
   This code is copyright (c) 2001 by Richard Zhang. 
-*------------------------------------------------------------------*/

// ------ Public data type declarations ----------------------------

// ------ Public function prototypes -------------------------------
void Speech_Init(void);
void Send_speech(tByte count_a, tByte time_b);
void Speech_update(void);
void Goto_speech(tByte count_b);
void Speech_broadcast(void);
void Speech_reset(void);
void Speech_s_update(void);

// ------ Public constants -----------------------------------------

#define No_voice (1)
#define First_touch (2)
#define Stolen_motor (3)
#define Appreciate_life (4)
#define Shengbaolong_brand (5)
#define Reminder (6)
#define Siren (7)
#define Battery_can_hold (8)
#define Open_lock (9)
#define Close_lock (10)
#define Kilometer (11)
#define One (12)
#define Two (13)
#define Three (14)
#define Four (15)
#define Five (16)
#define Six (17)
#define Seven (18)
#define Eight (19)
#define Nine (20)
#define Ten (21)
#define Second_touch (22)
#define System_closed (23)
#define Tailing_brand (24)
#define Xinri_brand (25)
#define Tick (26)
#define Ticktack (27)
#define Aima_brand (28)
#define System_open (29)
#define Hundred (30)
#define Zero (31)
#define Fengyang_brand (32)
#define Kaiqi_brand (33)
#define Kangjing_brand (34)
#define Xiangniu_brand (35)

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
