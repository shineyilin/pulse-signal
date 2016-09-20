#include <AT89X52.h>
#include "digital_show.h"

sbit Ir_InPin = P3^2;


void delay_560(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=2;b>0;b--)
            for(a=137;a>0;a--);
}
void IR_Init()
{
	 TMOD = 0x11;
	 EA = 1;
	 ET0 = 1;

	 IT0 = 1; //下降沿有效
	 EX0 = 1; //打开INT0

	 TR0 = 0;
	 Ir_InPin = 1;
}


void IR_Send()
{
		
}

void IR_Read() interrupt 0
{
	if ( Ir_InPin == 0 )
	{
		while (Ir_InPin == 0);

	}	

	if (Ir_InPin == 1)
	{
		while (Ir_InPin == 1);
	}
}