#ifndef __COME_DEFINE__
#define __COME_DEFINE__
#include <reg52.h>
#define mhz 27

sbit pin_m1_pulse  = P0^0;
sbit pin_m1_sign   = P0^1;
sbit pin_m1_error  = P0^2;
sbit pin_m1_range_0= P2^5;
sbit pin_m1_range_1= P2^4;

sbit pin_m2_pulse  = P0^3;
sbit pin_m2_sign   = P0^4;
sbit pin_m2_error  = P0^5;
sbit pin_m2_range_0= P2^3;
sbit pin_m2_range_1= P2^2;

sbit pin_m3_pulse  = P0^6;
sbit pin_m3_sign   = P0^7;
sbit pin_m3_error  = P2^6;
sbit pin_m3_range_0= P2^1;
sbit pin_m3_range_1= P2^0;

sbit pin_led_1 = P1^0;
sbit pin_led_2 = P1^1;
sbit pin_led_3 = P1^2;
sbit pin_led_4 = P1^3;
sbit pin_led_5 = P1^4;
sbit pin_led_6 = P1^5;
sbit pin_led_7 = P1^6;
sbit pin_led_8 = P1^7;

sbit pin_beep  = P2^7;

#define uint_8 	unsigned char
#define uint_16 unsigned int

#define int_8 	char
#define int_16  int

#define bool bit
#define true  1
#define false 0

#define high  1
#define low   0

#endif