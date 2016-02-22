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
#include "Battery.h"

// ------ Public variable definitions ------------------------------
bit Speech_blocked_G;	// Block other speech program.

// ------ Public variable declarations -----------------------------
extern bit Rotate_CW_G;
extern bit Sensor_blocked_G;
extern bit Alarm_blocked_G;

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
	Speech_RST = 0;	
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
	Custom_speech()
	Update the speech function for every 1s
------------------------------------------------------------------*/
void Custom_speech(void)
	{
	if(Rotate_CW_G)		// Speech after open lock, not close lock.
		{
		#ifdef Taili
		Goto_speech(Taili_speech);
		#endif
		
		#ifdef Shengbaolong
		Goto_speech(Shengbaolong_brand);
		#endif
		}
	}

/*----------------------------------------------------------------
	Speech_update()
	Update the speech function, 1s/ticket.
------------------------------------------------------------------*/
void Speech_update(void)
	{
	if(Speech_EN)
		{
		Speech_time += 1;
		if(Speech_time > Speech_time_thres)
			{
			Speech_time = 0;
			Speech_EN = 0;
			Sensor_blocked_G = 0;
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
				Alarm_blocked_G = 0;
				}
			break;
			case Battery_insufficient:
				{
				Send_speech(Battery_insufficient, 4);
				Custom_speech();
				}
			break;
			case Battery_5km:
				{
				Send_speech(Battery_5km, 5);
				Custom_speech();
				}
			break;
			case Battery_10km:
				{
				Send_speech(Battery_10km, 5);
				Custom_speech();
				}
			break;
			case Battery_15km:
				{
				Send_speech(Battery_15km, 5);
				Custom_speech();
				}
			break;
			case Battery_20km:
				{
				Send_speech(Battery_20km, 5);
				Custom_speech();
				}
			break;
			case Battery_35km:
				{
				Send_speech(Battery_35km, 5);
				Custom_speech();
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
				Goto_speech(Reminder);
				}
			break;
			case Reminder:
				{
				Send_speech(Reminder, 2);
				Goto_speech(Appreciate_life);
				}
			break;
			case Stolen_battery:
				{
				Send_speech(Stolen_battery, 3);
				}
			break;
			case Siren:
				{
				Alarm_blocked_G = 1;
				Send_speech(Siren, 3);
				Goto_speech(Stolen_motor);
				}
			break;
			case Open_lock:
				{
				Send_speech(Open_lock, 3);
				
				// First power up, don't broadcast battery tips.
				if(Firsttime_power_up_G == 0)
					Battery_broadcast();
				Firsttime_power_up_G = 0;
				}
			break;
			case Close_lock:
				{
				Send_speech(Close_lock, 3);
				Battery_broadcast();
				}
			break;
			case Second_touch:
				{
				Send_speech(Second_touch, 7);
				}
			break;
			case Battery_sufficient:
				{
				Send_speech(Battery_sufficient, 3);
				Custom_speech();
				}
			break;
			case Tailing_brand:
				{
				Send_speech(Tailing_brand, 1);
				}
			break;
			case Taili_brand:
				{
				Send_speech(Taili_brand, 1);
				}
			break;
			case Xinri_brand:
				{
				Send_speech(Xinri_brand, 1);
				}
			break;
			case Huanghe_brand:
				{
				Send_speech(Huanghe_brand, 1);
				}
			break;		
//			case Tick:
//				{
//				Send_speech(Tick, 1);
//				}
//			break;		
			case Ticktack:
				{
				Send_speech(Ticktack, 2);
				}
			break;		
			case Taili_speech:
				{
				Send_speech(Taili_speech, 5);
				}
			break;		
			case Youhu_brand:
				{
				Send_speech(Youhu_brand, 1);
				}
			break;		
			case Lvneng_brand:
				{
				Send_speech(Lvneng_brand, 1);
				}
			break;
			}		
		}
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
				Sensor_blocked_G = 0;
				Speech_scenario = 0;
				}
			}
		else
			{
			switch(Speech_scenario)
				{
				case Tick:
					{
					Send_speech(Tick, 1000);
					}
				break;		
				}		
			}		
		}
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
