#include "com_define.h"
#include "pos_control.h"
#include "uart.h"
#include "std_io.h"


void init()
{
	if ( !Uart_Init() ) 	{ pin_led_2 = 0; sucessBeep(); }
	if ( !initAllMotor() ) 	{ pin_led_1 = 0; sucessBeep(); }
	initLed();
	initAlarmSystem();
	if ( !initialCheck() )while(1){ alarmSystem(); }
}

void getMessage()
{
	uint_8 rec_data;
	if ( isdata() )
	{
		rec_data = _getkey();
		put_buf(rec_data);
		switch(rec_data)
		{
		/***************************************************************
		* 		  motor 1 control param
		***************************************************************/
			case 0x00: 	startMotor_1();	    //star motor  by send 0x00
						break;
			case 0xff:	closeMotor_1();		//close motor  by send ff
						break;
			case 0x01:	updateServo_1( getCounter() );	// set 1 speed 
						break;
			case 0x02:	setDirection_1(_getkey());		// set 1 direction									
						break;					
		/***************************************************************
		* 		  motor 2 control param
		***************************************************************/
			case 0x03: 	startMotor_2();	    //star motor  by send 0x00
						break;
			case 0x04:	closeMotor_2();		//close motor  by send ff
						break;
			case 0x05:	updateServo_2( getCounter() );	// set 1 speed 
						break;
			case 0x06:	setDirection_2(_getkey());		// set 1 direction									
						break;	
			default:
						break;
		};
		return;
	}	
}



void run()
{
	uint_16 countData = 0;
	uint_8 sendData = 0;
	while(1)
	{
		pin_led_1 = ~pin_m1_error;
		pin_led_2 = ~pin_m2_error;
		pin_led_3 = ~pin_m3_error;	
		getMessage();	
		//sendPing();
		sendData ++;
		//if( checkMotorError() != 0 ) {pin_led_5 = 0; break;}
	}
	while(1)
	{
		alarmSystem();
		TR0 = 0; 
		if ( checkMotorError() == 1 ) pin_led_1 = ~pin_led_1;
		if ( checkMotorError() == 2 ) pin_led_2 = ~pin_led_2;
		if ( checkMotorError() == 3 ) pin_led_3 = ~pin_led_3;

	}
}

/********************************************************/

void main()
{
	init();
	run();
	while(1);
}