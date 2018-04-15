#ifndef __POS_CONTROL__
#define __POS_CONTROL__

#include "com_define.h"
#include "uart.h"


void 	unitTestAbsoluteRotationValue(uint_16 pulse_value);
void 	initAlarmSystem	(	);
uint_8 	initialCheck	(	);
uint_8 	checkMotorError	(	);
uint_16 getCounter		(	);	 	
bool	initAllMotor	(	);
bool 	allInRange		(	);
bool 	resetAllMotor	(	);

/***********************************************************
*		   motor control 1
***********************************************************/
bool 	initMotor_1		(	);
void 	setDirection_1	( uint_8 flag );
void 	startMotor_1	(	);
void 	closeMotor_1	(	);
void 	updateServo_1	( uint_16 ultraData );
bool 	inRange_1		(	);
/***********************************************************
*		   motor control 2
***********************************************************/
bool 	initMotor_2		(	);
void 	setDirection_2	( uint_8 flag );
void 	startMotor_2	(	);
void 	closeMotor_2	(	);
void 	updateServo_2	( uint_16 ultraData );
bool 	inRange_2		(	);

#endif 