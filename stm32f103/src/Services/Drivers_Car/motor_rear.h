#ifndef _MOTOR_REAR_H_
#define _MOTOR_REAR_H_

#include "drivers_car_config.h"
#include "hall_sensor.h"

#define WHEEL_PERIMETER ((float)63.5) // cm
#define WHEEL_PULSES_NB ((float)36)
#define WHEEL_DISTANCE_BETWEEN_2_PULSES WHEEL_PERIMETER / WHEEL_PULSES_NB

typedef enum {
	MOTOR_POSITION_ERROR  = -1,
	MOTOR_ARG = 0,
	MOTOR_ARD = 1
} Motor_Rear_Position;

typedef enum {
  MOTOR_STATE_OFF = 0,
  MOTOR_STATE_ON = 1
} Motor_State;

void motors_rear_init(void);
int motor_rear_command(Motor_Rear_Position motor, int speed);
int motor_rear_set_state(Motor_Rear_Position motor, Motor_State motor_state);

#endif // _MOTOR_REAR_H_
