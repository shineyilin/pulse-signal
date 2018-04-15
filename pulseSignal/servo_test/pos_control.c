#include "pos_control.h"


uint_16 countTimer_1 = 0;
uint_16 countTimer_2 = 0;

bool 	run_flag = true;

void unitTestAbsoluteRotationValue(uint_16 pulse_value)
{
	//initMotor();
	uint_16 index;
	for (index = 0; index < pulse_value; index ++)
	{
		pin_m1_pulse = ~pin_m1_pulse;
		pin_m2_pulse = ~pin_m2_pulse;
		pin_m3_pulse = ~pin_m3_pulse;

		pin_m1_pulse = ~pin_m1_pulse;
		pin_m2_pulse = ~pin_m2_pulse;
		pin_m3_pulse = ~pin_m3_pulse;		
	}	
}

void initAlarmSystem()
{
	pin_m1_error = 1;
	pin_m2_error = 1;
	pin_m3_error = 1;

}
uint_8 initialCheck()
{
	if (pin_m1_sign == 0) return 1;
	if (pin_m2_sign == 0) return 2;
	if (pin_m3_sign == 0) return 3;
	return 4;
}

uint_8 checkMotorError()
{		
	  initAlarmSystem();			   	 
	if (!pin_m1_error)	{ 		return 1; }
	if (!pin_m2_error)	{	 	return 2; }
	if (!pin_m3_error)	{	  	return 3; }
	return 0;
}
uint_16 getCounter()
{
	uint_16 value = 0x0000;
	uint_16 temp  = 0x0000;
	value = _getkey();
	temp  = _getkey();

	value = 0x00ff&value;
	temp  = 0x00ff&temp;

	value = (value<<8)|temp;
	//putchar(value>>8);
	put_buf(value>>8);
	put_buf(value);
	return value;
}
bool initAllMotor()
{
	if ( initMotor_1() != 0) return -1;
	if ( initMotor_2() != 0) return -1;
	return 0;
}

bool allInRange()
{
	if (inRange_1() == true && inRange_2 == true )
	return true;
	else return false; 
}

bool resetAllMotor()
{
	if(inRange_1() == false || inRange_2() == false ) return false;
	else
	{
		initMotor_1();
		initMotor_2();
		run_flag = true;
		return true;
	}
}
/***********************************************************
* motor 1 control param
***********************************************************/

bool initMotor_1()
{
	pin_m1_pulse = 1;
	pin_m1_sign  = 1;
	pin_m1_error = 1;
							 
	TMOD |= 0x01;
	TH0 = 0;
	TL0 = 0;
	EA  = 1;
	ET0 = 1;
	TR0 = 0; // 定时器关闭
	return 0;
}

bool inRange_1()
{
	if (pin_m1_range_0 == 1 && pin_m1_range_1 == 1) 
		return true;
	else
	{
		TR0	 	 = 0;
		run_flag = false;
		return false;
	}
}

void setDirection_1(uint_8 flag)
{
	if ( flag 		== 0x00 )
	pin_m1_sign 	= 1;
	else if (flag	== 0x01) 
	pin_m1_sign 	= 0;
	put_buf(flag);
}

void startMotor_1()
{
	if (run_flag == 1) TR0 		= 1;
}

void closeMotor_1()
{
	TR0 		= 0;
	pin_led_7 	= 1;
}

void updateServo_1(uint_16 ultraData)
{
	//pin_led_8 = ~pin_led_8;
	countTimer_1 = ultraData;
}

void MultiServoInterrupt_1() interrupt 1	 using 3
{
	TH0 = countTimer_1>>8;
	TL0 = (countTimer_1<<8)>>8;
	pin_m1_pulse = ~pin_m1_pulse;
	pin_led_7 = ~pin_led_7;
}


/***********************************************************
* motor 2 control param
***********************************************************/

bool initMotor_2()
{
	pin_m2_pulse = 1;
	pin_m2_sign  = 1;
	pin_m2_error = 1;
								 
	TMOD |= 0x10;
	TH1 = 0;
	TL1 = 0;
	EA  = 1;
	ET1 = 1;
	TR1 = 0; // 定时器关闭
	return 0;
}
				
bool inRange_2()
{
	if (pin_m2_range_0 == 1 && pin_m2_range_1 == 1) 
		return true;
	else
	{
		TR1 = 0;  		//shutdown motor 2
		run_flag = false;
		return false;
	}
}


void setDirection_2(uint_8 flag)
{
	if ( flag 		== 0x00 )
	pin_m2_sign 	= 1;
	else if (flag	== 0x01) 
	pin_m2_sign 	= 0;
	put_buf(flag);
}

void startMotor_2()
{
	if (run_flag == 1) TR1 		= 1;
}

void closeMotor_2()
{
	TR1 		= 0;
	pin_led_8 	= 1;
}

void updateServo_2(uint_16 ultraData)
{
	//pin_led_8 = ~pin_led_8;
	countTimer_2 = ultraData;
}

void MultiServoInterrupt_2() interrupt 3	 using 3
{
	TH1 = countTimer_2>>8;
	TL1 = (countTimer_2<<8)>>8;
	pin_m2_pulse = ~pin_m2_pulse;
	pin_led_8 = ~pin_led_8;
}
 