#ifndef _MOTOR_CONTROL_H_
#define _MOTOR_CONTROL_H_

#include "PWM_Output.h"

#define MOTOR_PWM_PERIOD_US           500
#define MOTOR_PWM_DEFAULT_DUTY_CYCLE  50
#define MOTOR_SPEED_MAX               100
#define MOTOR_SPEED_MIN               (-MOTOR_SPEED_MAX)
#define MOTOR_SPEED_RANGE 				  (MOTOR_SPEED_MAX - MOTOR_SPEED_MIN)

typedef enum {
  MOTOR_OFF = 0,
  MOTOR_ON = 1
} Motor_Enable;

typedef struct {
  PWM_TypeDef pwm1;
  PWM_TypeDef pwm2;
  GPIO_TypeDef* enablePort;
  uint16_t enablePin;
} Motor_TypeDef;

void motorInit(Motor_TypeDef* init_struct);
void motorCmd(Motor_TypeDef* motor_struct, int speed);
void motorEnable(Motor_TypeDef* motor_struct, Motor_Enable enable);

#endif // _MOTOR_CONTROL_H_
