#ifndef __UART_H__

#define XTAL     27000000
#define BAUDRATE 9600

#include <reg52.h>
#include <stdio.h>
//#include "digital_show.h"
#include "com_define.h"
bool Uart_Init();
char _getkey(void);
char putchar(char temp);
void put_buf(char temp);
bool isdata();

#endif