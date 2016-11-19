#ifndef _MOTOR_REAR_H_
#define _MOTOR_REAR_H_

#include "motor_control.h"
#include "services_config.h"

void initRearMotor(void);
void commandRearMotor(int speed);
void enableRearMotor(void);
void disableRearMotor(void);

#endif // _MOTOR_REAR_H_
