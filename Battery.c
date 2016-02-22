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

#include "Battery.h"
#include "Speech.h"

// ------ Public variable definitions ------------------------------
tWord u16ADCL;
tWord u16ADC;
tWord Battery_ADC_result;
tByte Battery_level;

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------

// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  Battery_Init()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Battery_Init(void)
   {
	// Disable digital function for P0.6
	P0DIDS |= 0x40;
	// ADC0(P0.6) is input-only mode
	P0M1 |= 0x40;
	P0M2 &= 0xbf;
	// Select channel 6 for conversion.
	AADR2 = 1;
	AADR1 = 0;
	AADR0 = 1;
	// Open interruption
	EADC = 1;
	EA = 1;
	// Open ADC function
	ADCCON1 |= 0x80;
   }

/*------------------------------------------------------------------*-
  Battery_detection()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Battery_detection(void)
   {
   // Detect battery every 2s
	ADCI = 0;		// Clear ADC flag (ADCI = 0)
   ADCS = 1;		// ADC run (ADCS = 1)	
	}
/*------------------------------------------------------------------*-
  Battery_broadcast()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void Battery_broadcast(void)
   {
	#ifdef Z2
	if(Battery_ADC_result < 0x21f)
		Battery_level = 48;
	else if(Battery_ADC_result > 0x224)
		Battery_level = 60;
		
	switch(Battery_level)
		{
		case 48:
			{
			// battery is sufficient, battery > 50.5V, 3.14V/4.93V
			if((Battery_ADC_result >= 0x1ff))
				{
				Goto_speech(Battery_sufficient);
				}
			// 20km, 49.5V < battery < 50.5V, 3.08V/4.93V
			else if((Battery_ADC_result < 0x1ff)&&(Battery_ADC_result >= 0x1f7))		
				{
				Goto_speech(Battery_20km);
				}
			// 15km, 48.8V < battery < 49.5V, 3.03V/4.93V 
			else if((Battery_ADC_result < 0x1f7)&&(Battery_ADC_result >= 0x1ef))		
				{
				Goto_speech(Battery_15km);
				}
			// 10km, 48V < battery <48.8V, 2.99V/4.9V
			else if((Battery_ADC_result < 0x1ef)&&(Battery_ADC_result >= 0x1e6))		
				{
				Goto_speech(Battery_10km);
				}
			// 5km, 46.8V < battery < 48V, 2.91V/4.9V
			else if((Battery_ADC_result < 0x1e6)&&(Battery_ADC_result >= 0x1df))		
				{
				Goto_speech(Battery_5km);
				}                     
			// battery is low, battery < 46.8V, 
			else if(Battery_ADC_result < 0x1df)
				{
				Goto_speech(Battery_insufficient);
				}			
			}
		break;
		
		case 60:
			{
			// battery is sufficient, battery > 63.5V, 3.95V/4.93V
			if((Battery_ADC_result >= 0x27e))
				{
				Goto_speech(Battery_sufficient);
				}
			// 35km, 62V < battery < 63.5V, 3.86V/4.93V
			else if((Battery_ADC_result < 0x27e)&&(Battery_ADC_result >= 0x26e))		
				{
				Goto_speech(Battery_35km);
				}
			// 20km, 60V < battery < 62V, 3.74V/4.93V
			else if((Battery_ADC_result < 0x26e)&&(Battery_ADC_result >= 0x25b))		
				{
				Goto_speech(Battery_20km);
				}
			// 15km, 59.3V < battery < 60V, 3.7V/4.93V 
			else if((Battery_ADC_result < 0x25b)&&(Battery_ADC_result >= 0x255))		
				{
				Goto_speech(Battery_15km);
				}
			// 10km, 58.3V < battery <59.3V, 3.64V/4.93V
			else if((Battery_ADC_result < 0x255)&&(Battery_ADC_result >= 0x24c))		
				{
				Goto_speech(Battery_10km);
				}
			// 5km, 57.6V < battery < 58.3V, 3.6V/4.93V
			else if((Battery_ADC_result < 0x24c)&&(Battery_ADC_result >= 0x244))		
				{
				Goto_speech(Battery_5km);
				}                     
			// battery is low, battery < 57.6V, 
			else if(Battery_ADC_result < 0x244)
				{
				Goto_speech(Battery_insufficient);
				}
			}
		}
	#endif
	
	//------------ Withbattery_48V & 60V ------------------------	
	#ifdef Z3
	if(Battery_ADC_result < 0x2a0)
		Battery_level = 48;
	else if(Battery_ADC_result > 0x2a1)
		Battery_level = 60;
		
	switch(Battery_level)
		{
		case 48:
			{
			// battery is sufficient, battery > 50.5V, 3.14V/4.93V
			if((Battery_ADC_result >= 0x261))
				{
				Goto_speech(Battery_sufficient);
				}
			// 20km, 49.5V < battery < 50.5V, 3.08V/4.93V
			else if((Battery_ADC_result < 0x261)&&(Battery_ADC_result >= 0x257))		
				{
				Goto_speech(Battery_20km);
				}
			// 15km, 48.8V < battery < 49.5V, 3.03V/4.93V 
			else if((Battery_ADC_result < 0x257)&&(Battery_ADC_result >= 0x24d))		
				{
				Goto_speech(Battery_15km);
				}
			// 10km, 48V < battery <48.8V, 2.99V/4.9V
			else if((Battery_ADC_result < 0x24d)&&(Battery_ADC_result >= 0x243))		
				{
				Goto_speech(Battery_10km);
				}
			// 5km, 46.8V < battery < 48V, 2.91V/4.9V
			else if((Battery_ADC_result < 0x243)&&(Battery_ADC_result >= 0x236))		
				{
				Goto_speech(Battery_5km);
				}                     
			// battery is low, battery < 46.8V, 
			else if(Battery_ADC_result < 0x236)
				{
				Goto_speech(Battery_insufficient);
				}			
			}
		break;
		
		case 60:
			{
			// battery is sufficient, battery > 63.5V, 3.95V/4.93V
			if((Battery_ADC_result >= 0x2f9))
				{
				Goto_speech(Battery_sufficient);	
				}
			// 35km, 62V < battery < 63.5V, 3.86V/4.93V
			else if((Battery_ADC_result < 0x2f9)&&(Battery_ADC_result >= 0x2e5))		
				{
				Goto_speech(Battery_35km);	
				}
			// 20km, 60V < battery < 62V, 3.74V/4.93V
			else if((Battery_ADC_result < 0x2e5)&&(Battery_ADC_result >= 0x2cf))		
				{
				Goto_speech(Battery_20km);	
				}
			// 15km, 59.3V < battery < 60V, 3.7V/4.93V 
			else if((Battery_ADC_result < 0x2cf)&&(Battery_ADC_result >= 0x2c7))		
				{
				Goto_speech(Battery_15km);	
				}
			// 10km, 58.3V < battery <59.3V, 3.64V/4.93V
			else if((Battery_ADC_result < 0x2c7)&&(Battery_ADC_result >= 0x2bd))		
				{
				Goto_speech(Battery_10km);	
				}
			// 5km, 57.6V < battery < 58.3V, 3.6V/4.93V
			else if((Battery_ADC_result < 0x2bd)&&(Battery_ADC_result >= 0x2b3))		
				{
				Goto_speech(Battery_5km);	
				}                     
			// battery is low, battery < 57.6V, 
			else if(Battery_ADC_result < 0x2b3)
				{
				Goto_speech(Battery_insufficient);	
				}
			}
		}
	#endif
	}

/*------------------------------------------------------------------*-
  ADC_ISR()
  Initialisation function for the switch library.
-*------------------------------------------------------------------*/
void ADC_ISR(void) interrupt 11
	{
   ADCI = 0;		// Clear ADC flag (ADCI = 0)
   ADCS = 0;		// ADC stop (ADCS = 0)
	u16ADCL = ADCCON0;
	u16ADCL = u16ADCL >> 6;                // ADC[1:0]

	u16ADC = ADCH;
	u16ADC = (u16ADC << 2 ) + u16ADCL;		// ADC[9:2] + ADC[1:0]
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
