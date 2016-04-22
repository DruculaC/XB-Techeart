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
extern tByte Speech_time;

// ------ Public variable declarations -----------------------------

// ------ Private variables ----------------------------------------
tWord u16ADCL;
tWord u16ADC;
tWord Battery_ADC_result;
tByte Battery_level;

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
	// Open ADC function
	ADCCON1 |= 0x80;
   }

/*------------------------------------------------------------------*-
  Battery_detection()
  Initialisation function for the switch library.
  1 minute/ticket.
-*------------------------------------------------------------------*/
void Battery_detection(void)
   {
	// Get the battery voltage every minute.
	ADCI = 0;		// Clear ADC flag (ADCI = 0)
   ADCS = 1;		// ADC run (ADCS = 1)

// Test battery 0x320, 3.28/4.15.
//	if(Battery_ADC_result >= 0x320)
	// PIN20 is 3.3V.
	// PIN21 voltage is 4.2V battery, it will change as time.
	// Set low voltage is 3.3V/3.6V = 0.92, 0.92*1024=938(0x3aa)
	if(Battery_ADC_result >= 0x3aa)
//	if(Battery_ADC_result >= 0x34c)
		{
		// clear speech time for tick voice, broadcast tich speech in 100ms.
		Speech_time = 0;		
		Goto_speech(Tick);
		}
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
	
	// Get the battery voltage every minute.
	Battery_ADC_result = u16ADC;
	}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
