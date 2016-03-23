/*------------------------------------------------------------------*-
   A.H (v1.00)
  ------------------------------------------------------------------
   COPYRIGHT
   ---------
   This code is copyright (c) 2001 by Richard Zhang. 
-*------------------------------------------------------------------*/

// ------ Public data type declarations ----------------------------

// ------ Public constants -----------------------------------------
#define No_voice (1)
#define First_touch (2)
#define Stolen_motor (3)
#define Battery_insufficient (4)
#define Battery_5km (5)
#define Battery_10km (6)
#define Battery_15km (7)
#define Battery_20km (8)
#define Battery_35km (9)
#define Appreciate_life (10)
#define Shengbaolong_brand (11)
#define Reminder (12)
#define Stolen_battery (13)
#define Siren (14)
#define Open_lock (15)
#define Close_lock (16)
#define Second_touch (17)
#define Battery_sufficient (18)
#define System_deployed (19)
#define Tailing_brand (20)
#define Taili_brand (21)
#define Xinri_brand (22)
#define Huanghe_brand (23)
#define Tick (24)
#define Ticktack (25)
#define Taili_speech (26)
#define Youhu_brand (29)
#define Lvneng_brand (30)

// ------ Public function prototypes -------------------------------
void Speech_Init(void);
void Send_speech(tByte count_a, tByte time_b);
void Speech_update(void);
void Speech_s_update(void);
void Goto_speech(tByte count_b);
void Custom_speech(void);
void Speech_broadcast(void);

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
