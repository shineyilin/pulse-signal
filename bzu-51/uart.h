#ifndef __UART_H__
#ifndef __UART_H__


#define XTAL     12000000
#define BAUDRATE 2400

#include <AT89X52.h>
#include <stdio.h>
//#include "digital_show.h"

void Uart_Init();
char _getkey(void);
char putchar(char temp);

#endif