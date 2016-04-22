/*------------------------------------------------------------------*-
   DDC-Z.c (v1.00)
  ------------------------------------------------------------------
   COPYRIGHT
  ---------
   This code is copyright (c) 2015 by Richard Zhang.
-*------------------------------------------------------------------*/

#include "Main.h"
#include "Port.h"

#include "hSch51.h"
#include "Timer.h"
#include "Button.h"
#include "UART.h"
#include "Selflearn.h"
#include "Speech.h"
#include "IIC.h"
#include "KBI.h"
#include "Alarm.h"
#include "Clock.h"
#include "Battery.h"
#include "Sensor.h"
#include "Receiver.h"

/* ............................................................... */

void main(void)
   {	
	// Initialization
	Timer0_Init(500);
	UART_Init(9600);
	Button_Init();
	Selflearn_Init();
	Speech_Init();
   Sensor_Init();
	KBI_Init();
	Alarm_Init();
	Clock_Init();
	Sensor_Init();
	Receiver_init();
	Battery_Init();
	
   // Add Tasks
	hSCH_Add_Task(Button_update, 1550, 200, 1);		// 100ms/ticket
   hSCH_Add_Task(Speech_update, 1600, 200, 1);		// 100ms/ticket
   hSCH_Add_Task(Alarm_update, 1720, 1000, 1);		// 0.5s/ticket
	hSCH_Add_Task(Clock_update, 1880, 2000, 1);		// 1s/ticket
	
	// Start the program.
	hSCH_Start();
	
	while(1)
      {
		// Excute the program.
		hSCH_Dispatch_Tasks();
		}
   }
/*------------------------------------------------------------------*-
  ---- END OF FILE ---------------------------------------------------
-*------------------------------------------------------------------*/