#include "motor_front.h"
#include "motor_common.h"

static Motor_TypeDef motor_front;

void initFrontMotor(void) {
  PWM_TypeDef pwm1;
  PWM_TypeDef pwm2;
  
  pwm1.outputPin = FRONT_MOTOR_IN1_PIN;
  pwm1.outputPinPort = FRONT_MOTOR_IN1_PORT;
  pwm1.timer = FRONT_MOTOR_TIMER;
  pwm1.timerChannel = FRONT_MOTOR_IN1_CHANNEL;
  
  pwm2.outputPin = FRONT_MOTOR_IN2_PIN;
  pwm2.outputPinPort = FRONT_MOTOR_IN2_PORT;
  pwm2.timer = FRONT_MOTOR_TIMER;
  pwm2.timerChannel = FRONT_MOTOR_IN2_CHANNEL;
  
  motor_front.pwm1 = pwm1;
  motor_front.pwm2 = pwm2;
  motor_front.enablePin = FRONT_MOTOR_EN_PIN;
  motor_front.enablePort = FRONT_MOTOR_EN_PORT;
  
  motorInit(&motor_front);
}

void commandFrontMotor(int speed) {
	motorCmd(&motor_front, speed);
}

void enableFrontMotor(void) {
  motorEnable(&motor_front, MOTOR_STATE_ON);
}

void disableFrontMotor(void) {
  motorEnable(&motor_front, MOTOR_STATE_OFF);
}

