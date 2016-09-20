#include "servo.h"
#include "digital_show.h"
#include <AT89X52.h>
sbit control_pin = P3^7;

void ServoMove(int angle)
{
	control_pin = 1;
	DelayMicroseconds(angle);
	control_pin = 0;
	DelayMicroseconds(10000-angle);
} 