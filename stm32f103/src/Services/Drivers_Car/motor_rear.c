/**
* @file motor_rear.c
* @brief driver car layer for rear motors
*/

#include "motor_rear.h"
#include "motor_common.h"
#include "motor_control.h"

/* Private variables ---------------------------------------------------------*/

// Declaration of 2 motors, one left, one right
static Motor_TypeDef rear_motor_right;
static Motor_TypeDef rear_motor_left;

/**
* @brief Store the Motor_State of all the motors
*/
Motor_State motors_state[REAR_MOTORS_NB] = {MOTOR_STATE_OFF, MOTOR_STATE_OFF};

/**
* @brief Store the speed of all the motors
*/
int motors_speed[REAR_MOTORS_NB] = {0,0};

/********************************/
/*       Public Functions       */
/********************************/

/**
* @brief Rear motors initialization
*
* There are two PWM for each motors. They are complementary.
* @param None
* @retval None
*/
void motors_rear_init(void) {
	PWM_TypeDef pwm11;
	PWM_TypeDef pwm12;

	PWM_TypeDef pwm21;
	PWM_TypeDef pwm22;

	// Definition of the pwm1 of the left motor
	pwm11.outputPin = REAR_MOTOR_LEFT_IN1_PIN;
	pwm11.outputPinPort = REAR_MOTOR_LEFT_IN1_PORT;
	pwm11.timer = REAR_MOTOR_LEFT_TIMER;
	pwm11.timerChannel = REAR_MOTOR_LEFT_IN1_CHANNEL;
	rear_motor_left.pwm1 = pwm11;

	// Definition of the pwm2 of the left motor
	pwm12.outputPin = REAR_MOTOR_LEFT_IN2_PIN;
	pwm12.outputPinPort = REAR_MOTOR_LEFT_IN2_PORT;
	pwm12.timer = REAR_MOTOR_LEFT_TIMER;
	pwm12.timerChannel = REAR_MOTOR_LEFT_IN2_CHANNEL;
	rear_motor_left.pwm2 = pwm12;
	
	// Enable port and pin of the left motor
	rear_motor_left.enablePin = REAR_MOTOR_EN_PIN;
	rear_motor_left.enablePort = REAR_MOTOR_EN_PORT;
	 
	// Definition of the pwm1 of the right motor
	pwm21.outputPin = REAR_MOTOR_RIGHT_IN1_PIN;
	pwm21.outputPinPort = REAR_MOTOR_RIGHT_IN1_PORT;
	pwm21.timer = REAR_MOTOR_RIGHT_TIMER;
	pwm21.timerChannel = REAR_MOTOR_RIGHT_IN1_CHANNEL;
	rear_motor_right.pwm1 = pwm21;

	// Definition of the pwm2 of the right motor
	pwm22.outputPin = REAR_MOTOR_RIGHT_IN2_PIN;
	pwm22.outputPinPort = REAR_MOTOR_RIGHT_IN2_PORT;
	pwm22.timer = REAR_MOTOR_RIGHT_TIMER;
	pwm22.timerChannel = REAR_MOTOR_RIGHT_IN2_CHANNEL;
	rear_motor_right.pwm2 = pwm22;
	
	// Enable port and pin of the right motor
	rear_motor_right.enablePin = REAR_MOTOR_EN_PIN;
	rear_motor_right.enablePort = REAR_MOTOR_EN_PORT;

	// Initialization of the motors
	motorInit(&rear_motor_right);
	motorInit(&rear_motor_left);
}

/**
* @brief Command the given motor with the given speed
* @param motor Motor_Rear_Position
* @param speed Wanted speed (<0 to go backward, >0 to go forward)
* @retval -1 if the given motor does not exists, else 0
*/
int motor_rear_command(Motor_Rear_Position motor, int speed) {
	switch (motor){
		case REAR_MOTOR_RIGHT:
			// Send the command to the motor driver layer
			motorCmd(&rear_motor_right, speed);
			// Store the current speed of the right motor
			motors_speed[REAR_MOTOR_RIGHT] = speed;
			break;
		case REAR_MOTOR_LEFT:
			// Send the command to the motor driver layer
			motorCmd(&rear_motor_left, speed);
			// Store the current speed of the left motor
			motors_speed[REAR_MOTOR_LEFT] = speed;
			break;
		default:
			return -1;
	}
	return 0;
}

/**
* @brief Enable or disable the motor
* @param motor Motor_Rear_Position
* @param motor_state Wanted state (MOTOR_STATE_OFF to disable the motor, MOTOR_STATE_ON to enable the motor)
* @retval -1 if the given motor does not exists, else 0
*/
int motor_rear_set_state(Motor_Rear_Position motor, Motor_State motor_state) {
	switch (motor){
		case REAR_MOTOR_RIGHT:
			// Send the command to the motor driver layer
			motorEnable(&rear_motor_right, (Motor_State)motor_state);
			// Store the current state of the right motor
			motors_state[motor] = motor_state;
			break;
		case REAR_MOTOR_LEFT:
			// Send the command to the motor driver layer
			motorEnable(&rear_motor_left, (Motor_State)motor_state);
			// Store the current state of the left motor
			motors_state[motor] = motor_state;
			break;
		default:
			return -1;
	}
	return 0;
}

/**
* @brief Return the #Motor_State (enabled or disabled)
* @param motor Position of the motor, left or right
* @retval #MOTOR_STATE_OFF if the motor is disabled and #MOTOR_STATE_ON if the motor is enabled
*/
Motor_State get_motor_rear_state(Motor_Rear_Position motor){
	return motors_state[motor];
}

/**
* @brief Return the speed of the motor
* @param motor Motor_Rear_Position
* @retval speed
*/
int get_motor_rear_speed(Motor_Rear_Position motor){
	return motors_speed[motor];
}

