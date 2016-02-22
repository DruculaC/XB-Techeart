/*------------------------------------------------------------------*-
   A.C (v1.00)
  ------------------------------------------------------------------
   COPYRIGHT
   ---------
   This code is copyright (c) 2015 by Richard Zhang.
-*------------------------------------------------------------------*/

#include "Main.h"
#include "Port.h"

#include "UART.h"
#include "Speech.h"
#include "Alarm.h"
#include "Sensor.h"

// ------ Public variable definitions ------------------------------
bit ID_certificated_G;		// Flag for ID card certificated.
bit Received_finished_G;	// Flag for receiving 6 bytes.
bit Silent_mode_G;			// Flag for silent mode.
tByte ID_certificated_count;		// The count times of ID certificating.
bit Disable_alarm_mode_G;			// Flag for disabling alarm mode.

code tByte IDkey0 _at_ 0x003000;
code tByte IDkey1 _at_ 0x003001;
code tByte IDkey2 _at_ 0x003002;
code tByte IDkey3 _at_ 0x003003;
code tByte IDkey4 _at_ 0x003004;
code tByte IDkey5 _at_ 0x003005;

// ------ Public variable declarations -----------------------------
extern tByte Speech_time;

extern bit Self_learn_G;
extern tByte ID_certificated_time;

// ------ Private variables ----------------------------------------
tByte Received_cache[7];		// Cache of receiving bytes.
tByte Data_count;					// Counts of receiving data, multi bytes.
tByte Received_count;			// How many bytes received.

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  UART_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void UART_Init(tWord Baudrate)
   {
   // Set PCON.6 SMOD0 = 0, 
	PCON &= 0xbf;
	
	// Set P1.0 and P1.1 as UART port.
	AUXR1 &= 0xbf;
	
	// Mode 1, Start+8bytes+Stop, SM2 = 0, TI = 1.
	SCON = 0x5a;
	
	// Clear all T1 bits, and set to 8bit auto reload.
	TMOD &= 0x0f;
	TMOD |= 0x20;
	TH1 = TL1 = -(OSC_FREQ/12/32/Baudrate);
	
	TR1 = 1;
	TI = 0;
	ES = 1;
	
	Received_count = 0;
	ID_certificated_count = 0;
	Silent_mode_G = 0;
	Disable_alarm_mode_G = 0;
	}

/*-------------------------------------------------
	Sendbyte()
	Send A byte.
----------------------------------------------------*/
void Sendbyte(tByte character)
	{
	SBUF = character;
	while(!TI);
	TI = 0;
	}
/*-----------------------------------------------------
	Senddata()
	Send all data.
------------------------------------------------------*/
void Senddata(tByte *addr, tByte datalength)
	{
	while(datalength--)
		{
		Sendbyte(*addr++);
		}
	}
/*-----------------------------------------------
	UART interrupt
-----------------------------------------------*/
void uart_isr() interrupt 4 
	{
	if(RI)
		{
		RI=0;
		
		// Receive one byte, and move left.
		for(Data_count = 5; Data_count > 0; Data_count--)
			{
			Received_cache[Data_count] = Received_cache[Data_count-1];
			}
		Received_cache[0] = SBUF;
		
		// If in Self learning mode, receive 6 bytes.
		if(Self_learn_G)
			{
			Received_count += 1;
			if(Received_count >= 6)
				{
				Received_count = 0;
				// Set receiving finished.
				Received_finished_G = 1;
				}
			}
		else
			{
			if((Received_cache[5] == IDkey0)&&(Received_cache[4] == IDkey1)&&(Received_cache[3] == IDkey2))
				{
				if((Received_cache[2] == IDkey3)&&(Received_cache[1] == IDkey4)&&(Received_cache[0] == IDkey5))
					{					
					// immediately close the alarm speech and alarm detecting.
					Alarm_reset();
					Sensor_reset();
					
					// clear speech time for tick voice, broadcast tich speech in 100ms.
					Speech_time = 0;		
					Goto_speech(Tick);
					
					// Set 1 after Tick, otherwise Elecmotor will conflict to Tick voice.
					ID_certificated_G = 1;
					ID_certificated_time = 0;
					
					// Silent mode detecting.
					ID_certificated_count += 1;
					if(ID_certificated_count > 1)
						Silent_mode_G = 1;
					
					// Disabling alarm mode detecting.
					if(ID_certificated_count > 5)
						{
						Disable_alarm_mode_G = ~Disable_alarm_mode_G;
						ID_certificated_count = 0;
						Goto_speech(Ticktack);
						
						// Reset silent mode.
						Silent_mode_G = 0;
						}
					}
				}			
			}
		}
	}
/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/