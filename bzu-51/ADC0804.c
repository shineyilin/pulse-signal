#include <AT89X52.h>
#include "ADC0804.h"

sbit cs = P3^6;
sbit rd = P3^5;
sbit wr = P3^4;

uchar adc_value_temp;

uchar gat_adcValue()
{
	P0 = 0xff;
	cs = 0;
	Delay(5);
	wr = 0;
	Delay(5);
	wr = 1;
	//cs = 1;
	Delay(100);
	rd = 0;
	Delay(50);
	adc_value_temp = P0;
	rd = 1;
	cs = 1;
	return adc_value_temp;
}

