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

// ------ Elecmotor.c -------------------------------------------------
// P2.2, P2.3: PIN13, PIN14, control the electronic motor to locking and unlocking the motor bike.
sbit MagnetCon1 = P2^2;
sbit MagnetCon2 = P2^3;

sbit OCP_detect = P1^2;			// P1.2, PIN12, detect the over current protection.
sbit Hall_control = P0^5;		// P0.5, PIN22, External Hall switch, controlling external motor.

sbit Controller_lock = P1^6;	// P1.6, PIN5, External controller's 12V power lock.
sbit Elecdoor_lock = P2^4;		// P2.4, PIN15, External elec door lock.

// ------ Button.c -------------------------------------------------
sbit Key_switch = P2^5;		// P2.5, PIN16, read the motor key's status.

// ------ Speech.c -------------------------------------------------
sbit Speech_RST = P2^0;		// P2.0, PIN1, reset 4031C
sbit Speech_data = P2^1;	// P2.1, PIN2, 4031C data
sbit Speech_EN = P1^4;		// P1.4, PIN10, EN for power ampilfier.

// ------ Sensor.c, Protection.c --------------------------------------
sbit Horizontal_sensor = P0^0;		// P0.0, PIN3, horizontal sensor input.
sbit Vertical_sensor = P0^7; 			// P0.7, PIN19, vertical sensor input.
sbit Micromotion_sensor = P2^6;		// P2.6, PIN27, micromotion sensor input.
sbit Wire_cut = P0^1;					// P0.1, PIN26, cut wire detection.

// ------ Protection.c --------------------------------------
sbit wheeled_rotate = P0^2;			// P0.2, PIN25, detect the wheels rotating.

// ------ Selflearn.c -------------------------------------------------
sbit Self_learn_port = P0^1;			// P0.1, PIN26, Self-learn input.

// ---------------------------------------------------------------------
sbit Receiver_EN = P1^3;		// P1.3, PIN11, enable port for Receiver.
sbit transmitter_EN = P2^7;			// P2.7£¬PIN28£¬enable port for transmitter.
sbit raised_sensor_detect = P0^4;	// P0.4, PIN23, raised sensor detection.
sbit fell_sensor_detect = P0^3;		// P0.3, PIN24, fell sensor detection.


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*-------------------------------------------------------- ----------*/