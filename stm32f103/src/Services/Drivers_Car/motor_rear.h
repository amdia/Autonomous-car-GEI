#ifndef _MOTOR_REAR_H_
#define _MOTOR_REAR_H_

#include "motor_common.h"

/** Perimeter of a wheel in centimeters */
#define WHEEL_PERIMETER 								((float)63.5) 
/** Number of pulse of the rear hall sensors for one turn of wheel */
#define WHEEL_PULSES_NB 								((float)36)

void motors_rear_init(void);
int motor_rear_command(Motor_Rear_Position motor, int speed);
int motor_rear_set_state(Motor_Rear_Position motor, Motor_State motor_state);
Motor_State get_motor_rear_state(Motor_Rear_Position motor);
int get_motor_rear_speed(Motor_Rear_Position motor);

#endif // _MOTOR_REAR_H_
