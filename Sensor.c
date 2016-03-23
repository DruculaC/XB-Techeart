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

#include "Sensor.h"
#include "Speech.h"
#include "Alarm.h"

// ------ Public variable definitions ------------------------------
bit Sensor_blocked_G;		// Block sensor detection.
bit Sensor_EN;					// Sensor detection switch, 1 for open, 0 for close.
bit Sensor_delay_EN;			// Delay some time to enable Sensor_EN.
tByte Sensor_delay_time;	// The delay time to really enable Sensor_EN.

// ------ Public variable declarations -----------------------------
extern bit Sensor_to_alarm;
extern bit Program_blocked_G;
extern bit Disable_alarm_mode_G;
extern tByte Speech_time;

// ------ Private variables ----------------------------------------
tByte Sensor_time;				// Sensor input signal low voltage time
tWord Sensor_none_time;			// Sensor input signal high voltage time
tByte Sensor_trigger_level;	// Trigger leven for sensor, 1 means first time touch, 
										// 2 means second time touch continuously, 
										// 3 means really stolen touch, then alarm.
tWord Sensor_blocked_time;		// Using block time for trigger leven 1 delay, 1.5s.
bit Wire_cut_G;		// Flag for wire cut out.

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  Sensor_update()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Sensor_update(void)
   {
	if((Sensor_blocked_G)||(Program_blocked_G)||(!Sensor_EN))
		{
		// detect sensor level 2 after 3s.
		if(Sensor_trigger_level == 2)
			{
			Sensor_blocked_time += 1;
			if(Sensor_blocked_time > 1500)
				{
				Sensor_blocked_G = 0;
				Sensor_blocked_time = 0;
				return;
				}
			return;
			}
		else
			return;
		}
	
	Sensor_vibration_detect();
	}

/*------------------------------------------------------------------*-
  Sensor_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Sensor_Init(void)
   {
	// Set PIN3, PIN19 and PIN26 to input mode(high-res mode).
	P0M1 |= 0x83;
	P0M2 &= 0x7c;
	
   Sensor_time = 0;
	Sensor_trigger_level = 0;
	Sensor_blocked_G = 0;
	Sensor_EN = 0;	
	Sensor_delay_EN = 0;
	Sensor_delay_time = 0;
	}

/*------------------------------------------------------------------*-
  Sensor_reset()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Sensor_reset(void)
   {
   Sensor_time = 0;
	Sensor_trigger_level = 0;
	Sensor_blocked_G = 0;
	Sensor_EN = 0;	
	}

/*------------------------------------------------------------------*-
  Sensor_enable()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Sensor_enable(void)
   {
	Sensor_EN = 1;	
	}

/*------------------------------------------------------------------*-
  Sensor_postpone()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Sensor_postpone(void)
   {
	// Enabling sensor detection 20s after ID expiring or closing lock.
	if(Sensor_delay_EN)
		{
		Sensor_delay_time += 1;
		if(Sensor_delay_time > 10)
			{
			Sensor_delay_EN = 0;
			Sensor_delay_time = 0;
			Sensor_enable();
			}
		}
	}

/*------------------------------------------------------------------*-
  Sensor_vibration_detect()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Sensor_vibration_detect(void)
   {
	switch(Sensor_trigger_level)
		{
		case 0:
			{
			if((!Vertical_sensor)||(!Horizontal_sensor)||(!Micromotion_sensor))
				{
				Sensor_time += 1;
				if(Sensor_time >= 1)
					{
					Sensor_time = 0;
					Sensor_trigger_level = 2;
					Sensor_blocked_G = 1;
					}
				}
			else
				Sensor_time = 0;
			}
		break;
		case 2:
			{
			if((!Vertical_sensor)||(!Horizontal_sensor)||(!Micromotion_sensor))
				{
				Sensor_time += 1;
				Sensor_none_time = 0;
				if(Sensor_time >= 2)
					{
					Sensor_time = 0;
					Sensor_trigger_level = 3;
					Sensor_blocked_G = 1;
					Goto_speech(First_touch);
					}			
				}
			else
				{
				Sensor_time = 0;
				
				Sensor_none_time += 1;
				if(Sensor_none_time > 6000)
					{
					Sensor_none_time = 0;
					Sensor_trigger_level = 0;
					}
				}			
			}
		break;
		case 3:
			{
			if((!Vertical_sensor)||(!Horizontal_sensor)||(!Micromotion_sensor))
				{
				Sensor_time += 1;
				Sensor_none_time = 0;
				if(Sensor_time >= 2)
					{
					Sensor_time = 0;
					Sensor_trigger_level = 0;
					Sensor_blocked_G = 1;
					Sensor_to_alarm = 1;
					}			
				}
			else
				{
				Sensor_time = 0;
				
				Sensor_none_time += 1;
				if(Sensor_none_time > 6000)
					{
					Sensor_none_time = 0;
					Sensor_trigger_level = 0;
					}
				}			
			}
		break;
		}
	}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
