/*------------------------------------------------------------------*-
   Elecmotor.C (v1.00)
  ------------------------------------------------------------------
   Control Electrical motor in password protected lock.

   COPYRIGHT
   ---------
   This code is copyright (c) 2015 by Richard Zhang.
-*------------------------------------------------------------------*/

#include "Main.h"
#include "Port.h"

#include "Elecmotor.h"
#include "Communication.h"
#include "Speech.h"
#include "UART.h"
#include "Function.h"
#include "Delay.h"

// ------ Public variable definitions ------------------------------
bit Rotate_CW_G;		// Elecmotor CW rotated flag

// ------ Public variable declarations -----------------------------
extern bit Key_switch_on_G;
extern bit Program_blocked_G;
extern tWord u16ADC;
extern tWord Battery_ADC_result;
extern bit ID_certificated_G;
extern bit Sensor_delay_EN;
extern bit Silent_mode_G;
extern tByte ID_certificated_count;
extern bit Vehicle_poweron_EN;
extern bit Auto_close_G;
extern tByte Auto_close_time;

// ------ Private variables ----------------------------------------
tWord Rotate_time;		// Elapsed time for CW or ACW rotating.
tByte Magnet_code[3];	// Password code for electronical motor board.
tByte Code_time;			// Code time 10ms represents "1", 4ms for "0".
bit Coding_G;				// Flag for transmitting code to electronical motor.
tByte Byte_Index;			// Byte index of code, there is 3 bytes now.
tByte Bit_Index;			// Bit index of every byte, there is 8 bits per byte now.
 
// ------ Private constants ----------------------------------------

/*------------------------------------------------------------------*-
  Elecmotor_Init()
  Initialisation function for Electronic motor's lock.
-*------------------------------------------------------------------*/
void Elecmotor_Init(void)
   {	
	// Stop elecmotor.
	MagnetCon1 = 1;
	MagnetCon2 = 1;
	
	Bit_Index = 0;
	Byte_Index = 0;
	Rotate_time = 0;
	
	// Set OCP input mode 
	P1M1 |= 0x04;
	P1M2 &= 0xfb;
	// Stop hall control when power up.
	Hall_control = 1;
	
	// Initialize the password code.
	Magnet_code[0] = Elecmotor_code_head;
	Magnet_code[1] = Elecmotor_code_address;
	Magnet_code[2] = Elecmotor_code_open;
	Coding_G = 1;
	
	// Close the 12V power of Electronic motor's controller
   Controller_lock = 1;
	}

/*------------------------------------------------------------------*-
  Elecmotor_update()
  1ms/tick, excute the electronical motor lock.
-*------------------------------------------------------------------*/
void Elecmotor_update(void)
   {	
	// Detecting open lock condictions.
	if((Key_switch_on_G == 1)&&(Rotate_CW_G == 0)&&(ID_certificated_G))
		{
		Program_blocked_G = 1;				// Block button detection
		
		// Send code to lock.
		if(Coding_G == 1)
			{
			Elecmotor_coding();
			}
		else
			{
			MagnetCon1 = 1;
			MagnetCon2 = 0;

			Rotate_time += 1;
			// First 2s, don't detect OCP.
			if(Rotate_time > 2000)	
				{
				// If time > 5s or OCP is triggered, stop opening lock operation.
				if((Rotate_time >= 5000)||(OCP_detect == 1))
					{
					Rotate_time = 0;
					Rotate_CW_G = 1;				
					Program_blocked_G = 0;		// Detect button again.	

					// Reset ID certification
					ID_reset();
					
					// Stop CW rotation.
					MagnetCon1 = 1;
					MagnetCon2 = 1;

					// Whether in silient mode?
					if(Silent_mode_G == 0)
						Goto_speech(Open_lock);

					// Turn on vehicle's power.
					Vehicle_poweron_EN = 1;

					Auto_close_time = 0;
					Auto_close_G = 0;
					
					// Set the code again.
					Magnet_code[0] = Elecmotor_code_head;
					Magnet_code[1] = Elecmotor_code_address;
					Magnet_code[2] = Elecmotor_code_open;
					Coding_G = 1;
					return;
					}
				}
			}
		}
		
	if(((Key_switch_on_G == 0)||(Auto_close_G))&&(Rotate_CW_G == 1))
		{
		Program_blocked_G = 1;
		
		// stop hall power before closing lock.
		Hall_control = 1;		
		Controller_lock = 1;
		// Closing our lock.
		MagnetCon1 = 0;
		MagnetCon2 = 1;

		Rotate_time += 1;
		if(Rotate_time > 2000)		// First 2s, not detect OCP.
			{
			// if time > 5s or OCP is triggered, stop closing lock operation.
			if((Rotate_time >= 5000)||(OCP_detect == 1))
				{
				Rotate_time = 0;
				Rotate_CW_G = 0;
				Program_blocked_G = 0;

				MagnetCon1 = 1;
				MagnetCon2 = 1;
				
				// Reset ID certification and enable sensor detecting.
				ID_reset();
				Sensor_delay_EN = 1;
				
				// Take the battery sample after lock closed.
				Battery_ADC_result = u16ADC;		
				
				// If in silent mode, don't broadcast close lock speech.
				if(Silent_mode_G == 0)
					Goto_speech(Close_lock);
				
				// Reset silent mode.
				Silent_mode_G = 0;
				
				ID_certificated_count = 0;
				
				Auto_close_time = 0;
				Auto_close_G = 0;
				return;
				}		
			}
		}
	}

/*------------------------------------------------------------------*-
  Elecmotor_coding()
  Initialisation function for Electronic motor's lock.
-*------------------------------------------------------------------*/
void Elecmotor_coding(void)
	{
	if(MagnetCon2 == 0)
		{
		// whether msb is 1, if yes, maintain 10ms, if not maintain 4ms.
		if((Magnet_code[Byte_Index] & 0x80) == 0x80)
			{
			Code_time += 1;
			if(Code_time >= 10)	// 10 tickets, about 10ms.
				{
				Code_time = 0;
				Bit_Index += 1;
				MagnetCon2 = 1;
				// move 1 bit to left.
				Magnet_code[Byte_Index] <<= 1;
				}
			}
		else
			{
			Code_time += 1;
			if(Code_time >= 4)	// 2 tickets, about 4ms.
				{
				Code_time = 0;
				Bit_Index += 1;
				MagnetCon2 = 1;
				Magnet_code[Byte_Index] <<= 1;
				}		
			}
		
		if(Bit_Index >= 8)
			{
			Bit_Index = 0;
			Byte_Index += 1;
			if(Byte_Index > 2)
				{
				Byte_Index = 0;
				MagnetCon2 = 1;
				Coding_G = 0;
				}
			}
		}
	else
		{
		Code_time += 1;
		if(Code_time >= 4)
			{
			Code_time = 0;
			MagnetCon2 = 0;
			}
		}			
	}
/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
