
#include "digital_show.h"
#include <AT89X52.h>
#include <intrins.h>

/******
* #pragma ASM
* nop:
* #pragma ENDASM,
*******/


uchar code duan[]=					//Êý×Ö0~9£¬
		       {0x3f,0x06,0x5b,
			    0x4f,0x66,0x6d,
				0x7d,0x07,0x7f,
				0x6f,0x77,0x7c,0x39,0x5e,0x79,
				0x71,0x40};

uchar code wei[]=					   //ÊýÂë¹Ü0~7£¬
		       {0x08,0x09,0x0a,0x0b,
			    0x0c,0x0d,0x0e,0x0f};



void DelayMicroseconds(uint us)
{
	;
	while( --us );
}

void Delay_ms(uint ms)
{
	ms = ms + 1;
	while( --ms )
	DelayMicroseconds(1000);
}

void Delay(int us)
{
	while( us>0 )
	{
		us--;
	}
}


void Show( uint num )
{
	char i;	  						  g
	char a;
	for ( i = 0; i<8; i++ )
	{
		a = num%10;
		num = num/10;
  		P2=(P2&0xf8)|wei[i];	
		P0=duan[a];
		Delay(100);
		P0 = 0x00;
		if (num == 0) break;
	}
	P2 = P2|0x07;
}