#include <AT89X52.h>
#include <intrins.h>
#include "digital_show.h"
//#include "stepmotor.h"
//#include "servo.h"
#include "ADC0804.h"
#include "DAC0832.h"
#include "uart.h"

void setup(){

	//SCON = 0x50;	
//	TMOD = 0x02;
//	TH0  = 256-13;
//	TL0  = 256-13;
	//EA   = 1;
//	ET0  = 1;
	//TR0 = 1;
	 
}
sbit f = P2^7;
uchar adc_value;

void loop()
{
		   
	adc_value = gat_adcValue();
	dac_write(adc_value);
	Show( adc_value );


}

/*************************************************************/
void main()
{
	//setup();
	Uart_Init();
	while(1)
	{
		loop();
	}	
}

 