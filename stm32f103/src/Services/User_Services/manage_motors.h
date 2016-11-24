#ifndef __MANAGE_MOTORS_H
#define __MANAGE_MOTORS_H

#include "motor_front.h"
#include "motor_rear.h"
#include "hall_sensor.h"

// I/O variables for controlling purposes
extern __IO Direction front;
extern __IO int rear;
extern __IO float distance;

void motors_control(void);
void distance_to_travel(Hall_Position pos);
uint64_t get_rear_motor_speed(Hall_Position pos);
void motor_front_stop(Hall_Position pos);
void motor_rear_right_slaving(void);

#endif // __MANAGE_MOTORS_H
