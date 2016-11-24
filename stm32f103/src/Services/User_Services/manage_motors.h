#ifndef __MANAGE_MOTORS_H
#define __MANAGE_MOTORS_H

#include "motor_front.h"
#include "motor_rear.h"
#include "hall_sensor.h"

#define ANGLE_LEFT_MAX 										30
#define ANGLE_RIGHT_MAX 									0
#define ANGLE_RANGE      									(ANGLE_LEFT_MAX-ANGLE_RIGHT_MAX)
#define SPEED_RIGHT_2_LEFT_FRONT_MOTOR_DEGREE_PER_MILLIS 			ANGLE_RANGE/1400000
#define SPEED_LEFT_2_RIGHT_FRONT_MOTOR_DEGREE_PER_MILLIS 			ANGLE_RANGE/1100000

// I/O variables for controlling purposes
extern __IO Direction front;
extern __IO int rear;
extern __IO float distance;

void motors_control(void);
void distance_to_travel(Hall_Position pos);
uint64_t get_rear_motor_speed(Hall_Position pos);
void motor_front_stop(Hall_Position pos);
void motor_rear_right_slaving(void);
void control_angle_front_motor(void);

#endif // __MANAGE_MOTORS_H
