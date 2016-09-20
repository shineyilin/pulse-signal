#include "DAC0832.h"

#include "AT89X52.h"
sbit dac_cs = P3^0;
sbit dac_wr1 = P3^1;
 

void dac_write(uchar value)
{
	dac_cs = 0;
	P1 = value;
	dac_wr1 = 0;
	Delay(10);
	dac_cs = 1;
	dac_wr1 = 1;
}