#include "stepmotor.h"
#include <AT89X52.h>
#include "digital_show.h"
sbit IN_1 = P3^7;
sbit IN_2 = P3^6;
sbit IN_3 = P3^5;
sbit IN_4 = P3^4;

void StepForward(int step)
{
	int i;
	int us = 1000;
	for(i = 0; i<step; i++)
	{
		IN_1 = 1;
		IN_2 = 1;
		IN_3 = 0;
		IN_4 = 0;
		Delay(us);
		IN_1 = 0;
		IN_2 = 1;
		IN_3 = 1;
		IN_4 = 0;
		Delay(us);
		IN_1 = 0;
		IN_2 = 0;
		IN_3 = 1;
		IN_4 = 1;
		Delay(us);
		IN_1 = 1;
		IN_2 = 0;
		IN_3 = 0;
		IN_4 = 1;
		Delay(us);
	}
}


void Speed(int speed);
