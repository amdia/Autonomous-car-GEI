#ifndef _MOTOR_FRONT_H_
#define _MOTOR_FRONT_H_

#include "motor_control.h"
#include "motor_common.h"

void initFrontMotor(void);
void commandFrontMotor(int speed);
void enableFrontMotor(void);
void disableFrontMotor(void);

#endif // _MOTOR_FRONT_H_
