#include<AT89X51.H>
#include<math.h>
#include<intrins.h>	  //_crol_
#define uchar unsigned char
#define uint unsigned int
	   sbit bell=P1^0;
	   sbit l1=P0^1;
	   sbit bells=P0^0;
	   sbit k1=P3^5;
	   sbit k2=P3^4;
	   sbit k3=P3^3;
	   sbit k4=P3^2;


	   int num;
	   int num1;

void delay(int t);
void show(char a[8]);
void t0_time() interrupt 1
void t1_time() interrupt 3

void delay(int t)		                     //延时，
{	int i;
	for(t;t>0;t--)
		for(i=123;i>0;i--)
	    	;
}


void show(char a[8])
{
	int i;
		uchar code duan[]=					//数字0~9，
		       {0x3f,0x06,0x5b,0x4f,
			    0x66,0x6d,0x7d,0x07,
				0x7f,0x6f,0x77,0x7c,
				0x39,0x5e,0x79,0x71,0x40};
	    uchar code wei[]=					   //数码管0~7，
		       {0x07,0x06,0x05,0x04,
			    0x03,0x02,0x01,0x00};
	  	 
		for(i=0;i<=7;i++)
		{	 						    
			P2=wei[i];
			delay(1);
			P0=duan[a[i]];
			delay(1);
			P0=0x00;
		 }
	  
}
	char a[8];	
void main()
{	  
	int i,j;
	int n=0,n1=0,n2;

	int t1;
		  
		  
		  TMOD=0x01;
		  TH0=(65536-45872)/256;
		  TL0=(65536-45872)%256;

	      TH1=(65536-45872)/256;
		  TL1=(65536-45872)%256;

		  EA=1;				  // 开启总中断

		  ET1=1;
		  TR1=1;

		  ET0=1;				//开启t0中断
		  TR0=1;				  //打开定时器

	k4=0;

	while(1)	
	{
	

		   	 if(num>=21)
			 {
			 	num=0;
				n++;
			 }

			 if(num1>=1)
			 {
			 
			 	num1=0;
		        t1++;
			    if(t1>=3)
			    t1=0;
			 }
		
			 
			  
		
			a[0]=(n1-n1%10)/10;
			a[1]=n1%10;
			a[2]=16;
			a[3]=(n-n%10)/10;							  //十位
			a[4]=n%10;					        	      //个位
			a[5]=16;
			a[6]=16;
			a[7]=n2;





			
			if(n>=60)
		   {
			   n=0;
			   ++n1;
		   }
		   
		   if(n1>=60)
			{
			  n1=0;
			}	
	
			if(n%2==1)
			k2=1;
			if(n%2==0)
			k2=0;
	
			 
		 if(k1==0)
		 
			{if(k1==1)
			 k1=1;
			 n2++;
			}

		 if(n2==9)
			n2=0;


	}			 
}
	  void t0_time() interrupt 1
	  {
	  
	     TH0=(65536-45872)/256;
		 TL0=(65536-45872)%256;
		 show(a);
		 num++;

	  }


	  void t1_time() interrupt 3
	  {
	  	TH1=(65536-45872)/256;
		TH1=(65536-45872)%256;
		num1++;
	  
	  }