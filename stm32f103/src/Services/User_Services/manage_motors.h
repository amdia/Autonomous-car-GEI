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

#define ANGLE_INIT										ANGLE_RIGHT_MAX

// I/O variables for controlling purposes
extern __IO Direction front;
extern __IO int rear;
extern __IO float distance;

void rear_motors_control(void);
void distance_to_travel(void);
void calculate_distance(Hall_Position pos);
uint64_t get_rear_motor_speed(Hall_Position pos);
void motor_front_stop(Hall_Position pos);
void motor_rear_right_slaving(void);
//void control_angle_front_motor(int command_angle);
void control_angle_front_motor(void);

void count_pulse(Hall_Position pos);

#endif // __MANAGE_MOTORS_H
