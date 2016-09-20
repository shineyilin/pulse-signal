#include <AT89X52.h>
#include <intrins.h>
#include <digital.c>



sbit key = P3^5;
sbit key_ = P3^4;
int i = 0;
int num;

void setup()
{	

	num = 500;
	TMOD = 0X01;
	TH0 = (65536 - num)/256;
	TH0 = (65536 - num)%256;
	EA  = 1;
	ET0  = 1;
}

void loop()
{
	while(1)			 
	{	
		show(i);

		if (key == 0 )
		{		
			i++;
			key = 1;
			Delay(2);
			while( key == 0 )
			{
				show(i);
			}
			
		}
		
		if (key_ == 0 )
		{	
			key_ = 1;
			i++;	
		}
			
	}
}




void receive_data()	interrupt 1
{
	TH0 = (65536 - num)/256;
	TH0 = (65536 - num)%256;
}




