#include "motor_rear.h"
#include "motor_control.h"
#include "hall_sensor.h"
#include "time_systick.h"

static Motor_TypeDef motor_ARD;
static Motor_TypeDef motor_ARG;

void motors_rear_init(void) {
  PWM_TypeDef pwm11;
  PWM_TypeDef pwm12;
	
  PWM_TypeDef pwm21;
  PWM_TypeDef pwm22;
  
//init motor 1
  pwm11.outputPin = REAR_MOTOR1_IN1_PIN;
  pwm11.outputPinPort = REAR_MOTOR1_IN1_PORT;
  pwm11.speed = GPIO_SPEED;
  pwm11.timer = REAR_MOTOR1_TIMER;
  pwm11.timerChannel = REAR_MOTOR1_IN1_CHANNEL;
  
  pwm12.outputPin = REAR_MOTOR1_IN2_PIN;
  pwm12.outputPinPort = REAR_MOTOR1_IN2_PORT;
  pwm12.speed = GPIO_SPEED;
  pwm12.timer = REAR_MOTOR1_TIMER;
  pwm12.timerChannel = REAR_MOTOR1_IN2_CHANNEL;
  
  motor_ARD.pwm1 = pwm11;
  motor_ARD.pwm2 = pwm12;
  motor_ARD.enablePin = REAR_MOTOR_EN_PIN;
  motor_ARD.enablePort = REAR_MOTOR_EN_PORT;
  
  motorInit(&motor_ARD);

//init motor 2
  pwm21.outputPin = REAR_MOTOR1_IN1_PIN;
  pwm21.outputPinPort = REAR_MOTOR2_IN1_PORT;
  pwm21.speed = GPIO_SPEED;
  pwm21.timer = REAR_MOTOR2_TIMER;
  pwm21.timerChannel = REAR_MOTOR2_IN1_CHANNEL;
  
  pwm22.outputPin = REAR_MOTOR2_IN2_PIN;
  pwm22.outputPinPort = REAR_MOTOR2_IN2_PORT;
  pwm22.speed = GPIO_SPEED;
  pwm22.timer = REAR_MOTOR2_TIMER;
  pwm22.timerChannel = REAR_MOTOR2_IN2_CHANNEL;
  
  motor_ARG.pwm1 = pwm21;
  motor_ARG.pwm2 = pwm22;
  motor_ARG.enablePin = REAR_MOTOR_EN_PIN;
  motor_ARG.enablePort = REAR_MOTOR_EN_PORT;
 
  motorInit(&motor_ARG);
}

int motor_rear_command(Motor_Rear_Position motor, int speed) {
	switch (motor){
		case MOTOR_ARD:
			motorCmd(&motor_ARD, speed);
			break;
		case MOTOR_ARG:
			motorCmd(&motor_ARG, speed);
			break;
		default:
			return -1;
	}
	return 0;
}

int motor_rear_set_state(Motor_Rear_Position motor, Motor_State motor_state) {
	switch (motor){
		case MOTOR_ARD:
			motorEnable(&motor_ARD, (Motor_Enable)motor_state);
			break;
		case MOTOR_ARG:
			motorEnable(&motor_ARG, (Motor_Enable)motor_state);
			break;
		default:
			return -1;
	}
	return 0;
}

