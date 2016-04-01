/*-----------------------------------------------------
	Timer.h (v1.00)
	
	header file for Timer.c
-----------------------------------------------------*/

#ifndef _TIMER_H
#define _TIMER_H

//-----public constants-------------------------------

//-----public function prototype----------------------

void Timer0_Init(const tWord Tick_us_T0);
void hSCH_Manual_Timer0_Reload();
void hSCH_Start(void);

#endif
											
/*---------------------------------------------------
	end of file
----------------------------------------------------*/