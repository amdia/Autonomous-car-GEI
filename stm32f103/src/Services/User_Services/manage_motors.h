#ifndef __MANAGE_MOTORS_H
#define __MANAGE_MOTORS_H

#include "motor_front.h"
#include "motor_rear.h"
#include "hall_sensor.h"

#define ANGLE_LEFT_MAX 										(45)
#define ANGLE_RIGHT_MAX 									(-45)
#define ANGLE_RANGE      									(ANGLE_LEFT_MAX-ANGLE_RIGHT_MAX)
#define FRONT_MOTOR_SPEED_R2L 			((float)ANGLE_RANGE/1.4e6) // deg/us
#define FRONT_MOTOR_SPEED_L2R 			((float)ANGLE_RANGE/1.1e6)	// deg/us		

#define ANGLE_INIT										0

void rear_motors_control(MotorRear_Typedef motor_rear_control[]);
float* calculate_distance(Hall_Position pos);
void motor_front_stop(Hall_Position pos);
void control_angle_front_motor(int angle);


#endif // __MANAGE_MOTORS_H
