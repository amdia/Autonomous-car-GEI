#ifndef _MOTOR_REAR_H_
#define _MOTOR_REAR_H_

#include "motor_control.h"
#include "services_config.h"

#define WHEEL_PERIMETER ((float)63.5) // cm
#define WHEEL_PULSES_NB ((float)36)

void initRearMotor(void);
void commandRearMotor(int speed);
void enableRearMotor(void);
void disableRearMotor(void);

#endif // _MOTOR_REAR_H_
