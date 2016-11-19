#ifndef __MANAGE_MOTORS_H
#define __MANAGE_MOTORS_H

#include "motor_front.h"
#include "motor_rear.h"
#include "hall_sensor.h"

extern volatile Direction front;
extern volatile int rear;

extern volatile float distance;

void motors_control(void);
void travelled_distance(Hall_Position pos);

#endif // __MANAGE_MOTORS_H
