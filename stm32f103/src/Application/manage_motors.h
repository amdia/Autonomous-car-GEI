#ifndef __MANAGE_MOTORS_H
#define __MANAGE_MOTORS_H

#include "motor_front.h"
#include "motor_rear.h"
#include "hall_sensor.h"

#define REAR_MOTOR_SPEED  30

// control I/O variables
extern __IO Direction front;
extern __IO int rear;
extern __IO float distance;


void motors_control(void);
void update_traveled_distance(Hall_Position pos);

#endif // __MANAGE_MOTORS_H
