
#include "std_io.h"

void delayMs(uint_16 time)
{
	uint_16 index;
	for (index = 0; index < time; index++);
}


void initLed()
{
	pin_led_1 = 1;
	pin_led_2 = 1;
	pin_led_3 = 1;
	pin_led_4 = 1;
	pin_led_5 = 1;
	pin_led_6 = 1;
	pin_led_7 = 1;
	pin_led_8 = 1;
}

void alarmSystem()
{
	TR0 = 0;
	delayMs(10000);
	//delayMs(60000);
	pin_led_8 = ~pin_led_8;
	pin_beep  = ~pin_beep;
}

void sendPing()
{
	static uint_16 counter = 0;
	if (counter == 0) put_buf(0x88);
	counter ++;
}

void sucessBeep()
{
	pin_beep = 0;
	delayMs(30000);
	pin_beep = 1;
	delayMs(30000);

}
