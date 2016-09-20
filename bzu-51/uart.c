#include "uart.h"


#define 		 I_LEN   8		    // size 
unsigned char    in_start;	// start index
unsigned char    in_end;	// rec
char    idata    in_buf[I_LEN];

#define          O_LEN	 8
unsigned char    out_start;
unsigned char    out_end;
char    idata    out_buf[O_LEN];

bit bdata sen_ready_flag;
bit bdata sen_full_flag;
bit bdata rec_flag;
sbit beep = P2^7;
static void uart_interrupt (void) interrupt 4 using 1
{
	
	//--------receve data ----------
	char temp;
	if (RI)
	{
		temp = SBUF;
		RI = 0;
		beep = 1;
		if ( in_start + I_LEN != in_end )  //接收缓冲区
		{
			in_buf[in_end++ &(I_LEN-1) ] = temp;
			//if (In_End == 8) In_End == 0;
			rec_flag = 1;
		}

	}

	//----------send data -------------------
	if (TI)
	{
		TI = 0;
		if ( out_start != out_end )
		{
			SBUF = out_buf[out_start++ & (O_LEN-1)];
			//if (out_start == O_LEN) out_start = 0;
			sen_full_flag = 0;
		}
		else 
		{
			sen_ready_flag = 0; 
		}
	}
}

//getchar()  gets()

char _getkey(void)
{
	char temp;
	while (in_end == in_start);
	ES = 0;
	temp = in_buf[in_start++ &(I_LEN-1)];
	//if(in_start == I_LEN) in_start = 0;
	ES = 1;
	return (temp); 	
}

void put_buf(char temp)
{
	if (sen_full_flag == 0) //
	{
		if (sen_ready_flag == 0)
		{
			sen_ready_flag = 1;
	 		SBUF = temp;
		}
		else 
		{
			ES = 0;
			out_buf[out_end++ & (O_LEN-1)] = temp;
			//if (out_start == O_LEN) out_start = 0;
			if (( out_end^out_start)&(O_LEN-1)==0 )
			{
				sen_full_flag = 1;
			}
			ES = 1;
		}
	}
		
} 


//redefine putchar
char putchar(char temp)
{
	if ( temp == '\n')
	{
		while(sen_full_flag == 1);
		put_buf(0x0D);
	}
	while (sen_full_flag == 1);
	put_buf(temp);

	return temp;
} 


void uart_config_init()
{
	in_start  = 0;
	in_end    = 0;

	out_start = 0;
	out_end   = 0;
	
	sen_full_flag  = 0;
	sen_ready_flag = 0;

  	TMOD |=0x20;   //设置定时器T/C1工作在方式2,
				   //定时1工作于自动重载模式
 	SCON=0x50;     //设置串行口工作方式1：
				   //SCON格式 
				   //|M0|M1|M2|REN|TB8|RB8|TI|RI
	TH1 = 0xF3;
	TL1 = 0xF3;
	EA  = 1;
	ES  = 1;
	TR1  = 1;
}	

void Uart_Init()
{
	uart_config_init();
}