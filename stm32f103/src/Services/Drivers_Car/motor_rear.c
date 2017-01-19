#include "motor_rear.h"
#include "motor_common.h"
#include "motor_control.h"

static Motor_TypeDef rear_motor_right;
static Motor_TypeDef rear_motor_left;

Motor_State motors_state[REAR_MOTORS_NB] = {MOTOR_STATE_OFF, MOTOR_STATE_OFF};
int motors_speed[REAR_MOTORS_NB] = {0,0};

void motors_rear_init(void) {
	PWM_TypeDef pwm11;
	PWM_TypeDef pwm12;

	PWM_TypeDef pwm21;
	PWM_TypeDef pwm22;

	//init motor 1 (g)
	pwm11.outputPin = REAR_MOTOR_LEFT_IN1_PIN;
	pwm11.outputPinPort = REAR_MOTOR_LEFT_IN1_PORT;
	pwm11.timer = REAR_MOTOR_LEFT_TIMER;
	pwm11.timerChannel = REAR_MOTOR_LEFT_IN1_CHANNEL;

	pwm12.outputPin = REAR_MOTOR_LEFT_IN2_PIN;
	pwm12.outputPinPort = REAR_MOTOR_LEFT_IN2_PORT;
	pwm12.timer = REAR_MOTOR_LEFT_TIMER;
	pwm12.timerChannel = REAR_MOTOR_LEFT_IN2_CHANNEL;
	 
	rear_motor_left.pwm1 = pwm11;
	rear_motor_left.pwm2 = pwm12;
	rear_motor_left.enablePin = REAR_MOTOR_EN_PIN;
	rear_motor_left.enablePort = REAR_MOTOR_EN_PORT;
	 

	//init motor 2 (d)
	pwm21.outputPin = REAR_MOTOR_RIGHT_IN1_PIN;
	pwm21.outputPinPort = REAR_MOTOR_RIGHT_IN1_PORT;
	pwm21.timer = REAR_MOTOR_RIGHT_TIMER;
	pwm21.timerChannel = REAR_MOTOR_RIGHT_IN1_CHANNEL;

	pwm22.outputPin = REAR_MOTOR_RIGHT_IN2_PIN;
	pwm22.outputPinPort = REAR_MOTOR_RIGHT_IN2_PORT;
	pwm22.timer = REAR_MOTOR_RIGHT_TIMER;
	pwm22.timerChannel = REAR_MOTOR_RIGHT_IN2_CHANNEL;

	rear_motor_right.pwm1 = pwm21;
	rear_motor_right.pwm2 = pwm22;
	rear_motor_right.enablePin = REAR_MOTOR_EN_PIN;
	rear_motor_right.enablePort = REAR_MOTOR_EN_PORT;

	motorInit(&rear_motor_right);
	motorInit(&rear_motor_left);
}

int motor_rear_command(Motor_Rear_Position motor, int speed) {
	switch (motor){
		case REAR_MOTOR_RIGHT:
			motorCmd(&rear_motor_right, speed);
			motors_speed[REAR_MOTOR_RIGHT] = speed;
			break;
		case REAR_MOTOR_LEFT:
			motorCmd(&rear_motor_left, speed);
			motors_speed[REAR_MOTOR_LEFT] = speed;
			break;
		default:
			return -1;
	}
	return 0;
}


int motor_rear_set_state(Motor_Rear_Position motor, Motor_State motor_state) {
	switch (motor){
		case REAR_MOTOR_RIGHT:
			motorEnable(&rear_motor_right, (Motor_State)motor_state);
			motors_state[motor] = motor_state;
			break;
		case REAR_MOTOR_LEFT:
			motorEnable(&rear_motor_left, (Motor_State)motor_state);
			motors_state[motor] = motor_state;
			break;
		default:
			return -1;
	}
	return 0;
}

Motor_State get_motor_rear_state(Motor_Rear_Position motor){
	return motors_state[motor];
}

int get_motor_rear_speed(Motor_Rear_Position motor){
	return motors_speed[motor];
}

