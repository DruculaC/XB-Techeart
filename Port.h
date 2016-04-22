/*------------------------------------------------------------------*-
   Port.H (v1.00)
  ------------------------------------------------------------------
   'Port Header'

   COPYRIGHT
   ---------
   This code is copyright (c) 2001 by Richard.
-*------------------------------------------------------------------*/

// ------ Sch51.C ----------------------------------------

// Comment this line out if error reporting is NOT required
// #define SCH_REPORT_ERRORS

// #ifdef SCH_REPORT_ERRORS
// The port on which error codes will be displayed
// ONLY USED IF ERRORS ARE REPORTED
// #define Error_port P2
// #endif

// ------ Button.c -------------------------------------------------
sbit XB_reed_switch_port = P0^1;	// P0.1, PIN26, reed switch in XB, 0 for XB closed, 1 for XB open.

// ------ UART.c Selflearn.c ---------------------------------------
sbit Passwd_reed_switch_port = P2^5;	// P2.5, PIN16, reed switch in board,  
													// 0 for open passwd matching, 1 for shut down matching.
// ------ Speech.c -------------------------------------------------
sbit Speech_RST = P2^0;		// P2.0, PIN1, reset 4031C
sbit Speech_data = P2^1;	// P2.1, PIN2, 4031C data
sbit Speech_EN = P1^4;		// P1.4, PIN10, EN for power ampilfier.
sbit Speech_busy = P0^7;	// P0.7, PIN19, 4031C Flag for speeching busy, 1 for speeching, 0 for no speech.

// ------ IIC.c ----------------------------------------------------
// Define in N78E81x.h.
// sbit SCL=P1^2;      		// P1.2, PIN12, IIC clock pin.
// sbit SDA=P1^3;      		// P1.3, PIN11, IIC data pin.

// ------ KBI.c  --------------------------------------
// No need to define.
// sbit Sensor_INT1 = P0^4;	// P0.4, PIN23, Sensor interrupt pin INT1.
// sbit Sensor_INT1 = P0^3;	// P0.3, PIN24, Sensor interrupt pin INT2.

// ------ Battery.c -------------------------------------------
// No need to define.
// P0.6, PIN20, ADC5, battery input pin.

// ------ Receiver.c ----------------------------------------------
sbit RXD_power_EN = P0^5;	// P0.5, PIN22, Enable pin for RXD and ID receiver.

sbit test_port = P2^4;		// P2.4, PIN15

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*-------------------------------------------------------- ----------*/