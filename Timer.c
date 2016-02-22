/*---------------------------------------------------
	Timer.c (v1.00)
  ------------------------------------------------------------------
	Timer definations for DDC-Z, DDC-F, DDC-S etc.
   
	COPYRIGHT
  ---------
   This code is copyright (c) 2015 by Richard Zhang.
---------------------------------------------------*/	

#include "Main.h"
#include "Port.h"

#include "Timer.h"
#include "hSch51.h"

// ------ Public variable declarations -----------------------------
extern sTaskH hSCH_tasks_G[hSCH_MAX_TASKS];

// ------ Private variable definitions -----------------------------
// Register value of Timer0 and Timer1, calculated from InitTimer()
tByte timer0_8H, timer0_8L, timer1_8H, timer1_8L;		

/*-----------------------------------------------------------------
	Timer0_Init()
	Initializate Timer0.
-----------------------------------------------------------------*/
void Timer0_Init(const tWord Tick_us_T0)
	{
	tLong Inc_T0;
	tWord timer0_16;
   tByte i;
	
	// Delete all tasks when power up.
	for (i = 0; i < hSCH_MAX_TASKS; i++) 
      {
      hSCH_Delete_Task(i);
      }
	
	// Calculate Timer0 register value
	Inc_T0 = (tLong)Tick_us_T0 * (OSC_FREQ/1000000) / (tLong)OSC_PER_INST;
	timer0_16 = (tWord) (65536UL - Inc_T0);
	timer0_8H = (tByte) (timer0_16 / 256);
	timer0_8L = (tByte) (timer0_16 % 256);
		
   TMOD &= 0xF0; 	// Clear all T0 bits (T1 left unchanged)
   TMOD |= 0x01; 	// Set required T0 bits (T1 left unchanged) 
	
	// Load the Timer0 value to TL0 and TH0
	hSCH_Manual_Timer0_Reload();
   
	// Interrupt Timer 0 enabled
   ET0  = 1;
	}

/*------------------------------------------------------------------*-

  hSCH_Start()

  Starts the scheduler, by enabling interrupts.

  NOTE: Usually called after all regular tasks are added,
  to keep the tasks synchronised.

  NOTE: ONLY THE SCHEDULER INTERRUPT SHOULD BE ENABLED!!! 
 
-*------------------------------------------------------------------*/
void hSCH_Start(void) 
   {
   EA = 1;
   }

/*------------------------------------------------------------------*-

  hSCH_Manual_Timer0_Reload()

  This scheduler uses a (manually reloaded) 16-bit timer.
  The manual reload means that all timings are approximate. 
  THIS SCHEDULER IS NOT SUITABLE FOR APPLICATIONS WHERE
  ACCURATE TIMING IS REQUIRED!!!
  Timer reload is carried out in this function. 
 
-*------------------------------------------------------------------*/
void hSCH_Manual_Timer0_Reload()
   {
   // Stop Timer 0
   TR0 = 0;

   // 8051, 12 MHz
   // The Timer 0 resolution is 1.000 s
   // We set the timer at 64336 to generate interrupt after 1 ms
   // -> we are generating timer ticks at ~1 ms intervals
   TL0  = timer0_8L;
   TH0  = timer0_8H;	

   //  Start Timer 0
   TR0  = 1;
   }	

/*------------------------------------------------------------------*-

  SCH_Update

  This is the scheduler ISR.  It is called at a rate 
  determined by the timer settings in SCH_Init_T0().
  This version is triggered by Timer 0 interrupts.
 
-*------------------------------------------------------------------*/
void SCH_Update(void) interrupt interrupt_timer_0_overflow 
   {
   tByte Index;
   // Reload the Timer0 value
   hSCH_Manual_Timer0_Reload();

   // NOTE: calculations are in *TICKS* (not milliseconds)
   for (Index = 0; Index < hSCH_MAX_TASKS; Index++)
      {
      // Check if there is a task at this location
      if (hSCH_tasks_G[Index].pTask)
         {
         if (hSCH_tasks_G[Index].Delay == 0)
            {
            // The task is due to run
            hSCH_tasks_G[Index].RunMe += 1;  // Inc. the 'Run Me' flag

            if (hSCH_tasks_G[Index].Period)
               {
               // Schedule periodic tasks to run again
               hSCH_tasks_G[Index].Delay = hSCH_tasks_G[Index].Period;
               }
            }
         else
            {
            // Not yet ready to run: just decrement the delay 
            hSCH_tasks_G[Index].Delay -= 1;
            }
         }         
      }
   } 

/*---------------------------------------------------
	end of file
----------------------------------------------------*/