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

#include "Speech.h"
#include "Delay.h"

// ------ Public variable definitions ------------------------------
bit Speech_blocked_G;	// Block other speech program.
bit Speech_busy_G;		// 1 means speech busy already.

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------
tByte Speech_scenario;
tByte Speech_time;
tByte Speech_time_thres;

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  Speech_Init()
  Initialisation function for the speech library.
-*------------------------------------------------------------------*/
void Speech_Init(void)
   {	
	// Set P0.7 PIN19 to input mode, Speech_busy
	P0M1 |= 0x80;
	P0M2 &= 0x7f;

	Speech_EN = 0;
	Speech_RST = 0;
	Speech_data = 0;
	Speech_time = 0;
	Speech_time_thres = 10;
	Speech_busy_G = 0;
	
//	Goto_speech(No_voice);
	Speech_reset();

	Speech_time = 0;
	Goto_speech(Tick);
	}

/*--------------------------------------------------
	Send_speech()
---------------------------------------------------*/
void Send_speech(tByte count_a, tByte time_b)
	{
	tByte i;
	Speech_EN = 1;
	Delay(LOOP_TIMEOUT_INIT_500ms);
	Speech_reset();
	for(i=0; i < count_a; i++)
		{
		Speech_data = 1; 
		Delay(LOOP_TIMEOUT_INIT_001ms);
		Speech_data = 0; 
		Delay(LOOP_TIMEOUT_INIT_001ms);
		}
	Speech_time_thres = time_b;
//	time_b = 0;
	
	Speech_scenario = 0;
	}

/*----------------------------------------------------------------
	Goto_speech()
	Update the speech function for every 1s
------------------------------------------------------------------*/
void Goto_speech(tByte count_b)
	{
	Speech_scenario = count_b;
	}

/*----------------------------------------------------------------
	Speech_update()
	Update the speech function, 1s/ticket.
------------------------------------------------------------------*/
void Speech_update(void)
	{
//	Speech_s_update();
	Speech_broadcast();
	}
	
/*----------------------------------------------------------------
	Speech_reset()
	Send speech reset signal.
------------------------------------------------------------------*/
void Speech_reset(void)
	{
	Speech_RST = 1;
	Delay(LOOP_TIMEOUT_INIT_050ms);
	Speech_RST = 0;
	Delay(LOOP_TIMEOUT_INIT_050ms);
	}

/*----------------------------------------------------------------
	Speech_s_update_s()
	Instant speech update, 1ms/ticket, for now, only "Tich" voice.
void Speech_s_update(void)
	{
	if(Speech_scenario == Tick)
		{
		if(Speech_busy)
			{
			Speech_time += 1;
			if(Speech_time > 100)
				{
				Speech_time = 0;
				Speech_EN = 0;
				Speech_scenario = 0;
				}
			}
		else
			{
			switch(Speech_scenario)
				{
				case Tick:
					{
					Send_speech(Tick, 10);
					}
				break;		
				}		
			}		
		}
	}
------------------------------------------------------------------*/

/*----------------------------------------------------------------
	Speech_broadcast()
   broadcast the various speech.
------------------------------------------------------------------*/
void Speech_broadcast(void)
	{	
//	if((Speech_busy)&&(Speech_scenario != Tick))
	if((Speech_EN)&&(Speech_scenario != Tick))
		{
		Speech_busy_G = 1;
		
		Speech_time += 1;
//		if(Speech_time > 100)
		if(Speech_time > Speech_time_thres)
			{
			Speech_time = 0;
			Speech_EN = 0;
			}
		}
	else
		{		
		// If 4031C no busy signal, then reset enable.
		Speech_time = 0;
		Speech_EN = 0;
		if(Speech_busy_G)
			{
			Speech_busy_G = 0;
			Speech_reset();
			}
			
		switch(Speech_scenario)
			{
			case No_voice:
				{
				Send_speech(No_voice, 5);
				}
			break;
			case First_touch:
				{
				Send_speech(First_touch, 15);
				}
			break;
			case Stolen_motor:
				{
				Send_speech(Stolen_motor, 45);
				}
			break;
			case Appreciate_life:
				{
				Send_speech(Appreciate_life, 25);
				}
			break;
			case Shengbaolong_brand:
				{
				Send_speech(Shengbaolong_brand, 10);
				}
			break;
			case Reminder:
				{
				Send_speech(Reminder, 10);
				}
			break;
			case Siren:
				{
				Send_speech(Siren, 20);
				}
			break;
			case Battery_can_hold:
				{
				Send_speech(Battery_can_hold, 20);
				}
			break;
			case Open_lock:
				{
				Send_speech(Open_lock, 10);
				}
			break;
			case Close_lock:
				{
				Send_speech(Close_lock, 15);
				}
			break;
			case Kilometer:
				{
				Send_speech(Kilometer, 5);
				}
			break;
			case One:
				{
				Send_speech(One, 5);
				}
			break;
			case Two:
				{
				Send_speech(Two, 5);
				}
			break;
			case Three:
				{
				Send_speech(Three, 5);
				}
			break;
			case Four:
				{
				Send_speech(Four, 5);
				}
			break;
			case Five:
				{
				Send_speech(Five, 5);
				}
			break;
			case Six:
				{
				Send_speech(Six, 5);
				}
			break;
			case Seven:
				{
				Send_speech(Seven, 5);
				}
			break;
			case Eight:
				{
				Send_speech(Eight, 5);
				}
			break;
			case Nine:
				{
				Send_speech(Nine, 5);
				}
			break;
			case Ten:
				{
				Send_speech(Ten, 5);
				}
			break;
			case Second_touch:
				{
				Send_speech(Second_touch, 35);
				}
			break;
			case System_closed:
				{
				Send_speech(System_closed, 20);
				}
			break;
			case Tailing_brand:
				{
				Send_speech(Tailing_brand, 5);
				}
			break;
			case Xinri_brand:
				{
				Send_speech(Xinri_brand, 5);
				}
			break;
			case Tick:
				{
				Send_speech(Tick, 10);
				}
			break;			
			case Ticktack:
				{
				Send_speech(Ticktack, 18);
				}
			break;		
			case Aima_brand:
				{
				Send_speech(Aima_brand, 10);
				}
			break;
			case System_open:
				{
				Send_speech(System_open, 30);
				}
			break;
			case Hundred:
				{
				Send_speech(Hundred, 5);
				}
			break;
			case Zero:
				{
				Send_speech(Zero, 5);
				}
			break;
			case Fengyang_brand:
				{
				Send_speech(Fengyang_brand, 5);
				}
			break;
			case Kaiqi_brand:
				{
				Send_speech(Kaiqi_brand, 5);
				}
			break;
			case Kangjing_brand:
				{
				Send_speech(Kangjing_brand, 5);
				}
			break;
			case Xiangniu_brand:
				{
				Send_speech(Xiangniu_brand, 5);
				}
			break;
			case Lvyuan_brand:
				{
				Send_speech(Lvyuan_brand, 5);
				}
			break;
			case Yunjian_brand:
				{
				Send_speech(Yunjian_brand, 5);
				}
			break;
			case Wuxingzuanbao_brand:
				{
				Send_speech(Wuxingzuanbao_brand, 5);
				}
			break;
			case Battery_insufficient:
				{
				Send_speech(Battery_insufficient, 3);
				}
			break;
			case Catch_thief:
				{
				Send_speech(Catch_thief, 25);
				}
			break;
			}		
		}	
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
