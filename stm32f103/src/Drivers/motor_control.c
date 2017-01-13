/**
* @file motor_control.c
* @brief driver layer for the motor control functions
*/
#include "motor_control.h"
#include "motor_common.h"
#include "gpio.h"

/********************************/
/*      Public Functions        */
/********************************/

/**
* @brief initialization of a motor
* @param init_struct motor structure is initialized by this function
* @retval None
*/
void motorInit(Motor_TypeDef* init_struct) {
  GPIO_InitTypeDef enablePin;
  
  // bind pwm1 - mode 1
  init_struct->pwm1.mode = PWM_MODE_1;
  init_struct->pwm1.dutyCyclePercent = MOTOR_PWM_DEFAULT_DUTY_CYCLE;
  init_struct->pwm1.periodUs = MOTOR_PWM_PERIOD_US;
  // bind pwm1 - mode 2
  init_struct->pwm2.mode = PWM_MODE_2;
  init_struct->pwm2.dutyCyclePercent = MOTOR_PWM_DEFAULT_DUTY_CYCLE;
  init_struct->pwm2.periodUs = MOTOR_PWM_PERIOD_US;
  // check wheather 2 pwms have different config
  if (init_struct->pwm1.timer != init_struct->pwm2.timer)
    init_struct->pwm2.timer = init_struct->pwm1.timer;
  else {}
  // initialize pwm
  PWM_initialize(&(init_struct->pwm1));
  PWM_initialize(&(init_struct->pwm2));
  
  // initialize enable pin
  enablePin.GPIO_Mode = GPIO_Mode_Out_PP;
  enablePin.GPIO_Speed = GPIO_Speed_50MHz;
  enablePin.GPIO_Pin = init_struct->enablePin;
  GPIO_Init(init_struct->enablePort, &enablePin);
}

/**
* @brief command the motor speed
* @param motor_struct motor structure is read by this function
* @param speed wanted speed (<0 to go backward, >0 to go forward)
* @retval None
*/
void motorCmd(Motor_TypeDef* motor_struct, int speed) {
  uint16_t dutyCycle = 0;
  int speedAux;
  if (speed > MOTOR_SPEED_MAX) speedAux = MOTOR_SPEED_MAX;
  else if (speed < MOTOR_SPEED_MIN) speedAux = MOTOR_SPEED_MIN;
  else speedAux = speed;
  dutyCycle = (uint16_t)((speedAux - MOTOR_SPEED_MIN) * DUTY_CYCLE_RANGE / MOTOR_SPEED_RANGE + DUTY_CYCLE_MIN);
  PWM_CmdDutyCycle(&(motor_struct->pwm1), dutyCycle);
  PWM_CmdDutyCycle(&(motor_struct->pwm2), dutyCycle);
}

/**
* @brief enable or disable the motor given
* @param enable ON or OFF
* @retval None
*/
void motorEnable(Motor_TypeDef* motor_struct, Motor_State enable) {
  if (enable == MOTOR_STATE_ON) {
    GPIO_set(motor_struct->enablePort, motor_struct->enablePin);
  } else {
    GPIO_reset(motor_struct->enablePort, motor_struct->enablePin);
  }
}
