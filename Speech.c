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

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------
tByte Speech_scenario;
tByte Speech_time;
tByte Speech_time_thres;
bit Firsttime_power_up_G;

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  Speech_Init()
  Initialisation function for the speech library.
-*------------------------------------------------------------------*/
void Speech_Init(void)
   {	
	Speech_EN = 0;
	Speech_RST = 1;	
	Speech_data = 0;
	Speech_time = 0;
	
	Firsttime_power_up_G = 1;
	}

/*--------------------------------------------------
	Send_speech()
---------------------------------------------------*/
void Send_speech(tByte count_a, tByte time_b)
	{
	tByte i;
	Speech_EN = 1;
	Speech_RST = 0;
	Delay(LOOP_TIMEOUT_INIT_050ms);
	Speech_RST = 1;
	Delay(LOOP_TIMEOUT_INIT_050ms);
	for(i=0; i < count_a; i++)
		{
		Speech_data = 1; 
		Delay(LOOP_TIMEOUT_INIT_001ms);
		Speech_data = 0; 
		Delay(LOOP_TIMEOUT_INIT_001ms);
		}
	Speech_time_thres = time_b;
	
	if(Speech_scenario != Tick)
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
	Speech_broadcast();
	}
	
/*----------------------------------------------------------------
	Speech_s_update_s()
	Instant speech update, 1ms/ticket, for now, only "Tich" voice.
------------------------------------------------------------------*/
void Speech_s_update(void)
	{
	if(Speech_scenario == Tick)
		{
		if(Speech_EN)
			{
			Speech_time += 1;
			if(Speech_time > Speech_time_thres)
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

/*----------------------------------------------------------------
	Speech_broadcast()
   broadcast the various speech.
------------------------------------------------------------------*/
void Speech_broadcast(void)
	{	
	if(Speech_EN)
		{
		Speech_time += 1;
		if(Speech_time > Speech_time_thres)
			{
			Speech_time = 0;
			Speech_EN = 0;
			}
		}
	else
		{
		switch(Speech_scenario)
			{
			case No_voice:
				{
				Send_speech(No_voice, 1);
				}
			break;
			case First_touch:
				{
				Send_speech(First_touch, 3);
			}
			break;
			case Stolen_motor:
				{
				Send_speech(Stolen_motor, 9);
				}
			break;
			case Appreciate_life:
				{
				Send_speech(Appreciate_life, 5);
				}
			break;
			case Shengbaolong_brand:
				{
				Send_speech(Shengbaolong_brand, 2);
				}
			break;
			case Reminder:
				{
				Send_speech(Reminder, 2);
				}
			break;
			case Siren:
				{
				Send_speech(Siren, 1);
				}
			break;
			case Battery_can_hold:
				{
				Send_speech(Battery_can_hold, 4);
				}
			break;
			case Open_lock:
				{
				Send_speech(Open_lock, 2);
				}
			break;
			case Close_lock:
				{
				Send_speech(Close_lock, 3);
				}
			break;
			case Kilometer:
				{
				Send_speech(Kilometer, 1);
				}
			break;
			case One:
				{
				Send_speech(One, 1);
				}
			break;
			case Two:
				{
				Send_speech(Two, 1);
				}
			break;
			case Three:
				{
				Send_speech(Three, 1);
				}
			break;
			case Four:
				{
				Send_speech(Four, 1);
				}
			break;
			case Five:
				{
				Send_speech(Five, 1);
				}
			break;
			case Six:
				{
				Send_speech(Six, 1);
				}
			break;
			case Seven:
				{
				Send_speech(Seven, 1);
				}
			break;
			case Eight:
				{
				Send_speech(Eight, 1);
				}
			break;
			case Nine:
				{
				Send_speech(Nine, 1);
				}
			break;
			case Ten:
				{
				Send_speech(Ten, 1);
				}
			break;
			case Second_touch:
				{
				Send_speech(Second_touch, 7);
				}
			break;
			case System_closed:
				{
				Send_speech(System_closed, 4);
				}
			break;
			case Tailing_brand:
				{
				Send_speech(Tailing_brand, 1);
				}
			break;
			case Xinri_brand:
				{
				Send_speech(Xinri_brand, 1);
				}
			break;
			case Ticktack:
				{
				Send_speech(Ticktack, 2);
				}
			break;		
			case Aima_brand:
				{
				Send_speech(Aima_brand, 2);
				}
			break;
			case System_open:
				{
				Send_speech(System_open, 4);
				}
			break;
			case Hundred:
				{
				Send_speech(Hundred, 1);
				}
			break;
			case Zero:
				{
				Send_speech(Zero, 1);
				}
			break;
			case Fengyang_brand:
				{
				Send_speech(Fengyang_brand, 1);
				}
			break;
			case Kaiqi_brand:
				{
				Send_speech(Kaiqi_brand, 1);
				}
			break;
			case Kangjing_brand:
				{
				Send_speech(Kangjing_brand, 1);
				}
			break;
			case Xiangniu_brand:
				{
				Send_speech(Xiangniu_brand, 1);
				}
			break;
			}		
		}	
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
