/**
* @file motor_front.c
* @brief Driver car layer for the front motor
*/

#include "motor_front.h"
#include "motor_common.h"

/* Private variables ---------------------------------------------------------*/
static Motor_TypeDef motor_front;

/********************************/
/*       Public Functions       */
/********************************/

/**
* @brief Front motor initialization
*
* There are two PWM for the motor. They are complementary.
*/
void initFrontMotor(void) {
	PWM_TypeDef pwm1;
	PWM_TypeDef pwm2;

	// Definition of the pwm1 of the front motor
	pwm1.outputPin = FRONT_MOTOR_IN1_PIN;
	pwm1.outputPinPort = FRONT_MOTOR_IN1_PORT;
	pwm1.timer = FRONT_MOTOR_TIMER;
	pwm1.timerChannel = FRONT_MOTOR_IN1_CHANNEL;
	motor_front.pwm1 = pwm1;

	// Definition of the pwm2 of the front motor
	pwm2.outputPin = FRONT_MOTOR_IN2_PIN;
	pwm2.outputPinPort = FRONT_MOTOR_IN2_PORT;
	pwm2.timer = FRONT_MOTOR_TIMER;
	pwm2.timerChannel = FRONT_MOTOR_IN2_CHANNEL;
	motor_front.pwm2 = pwm2;
	
	// Enable port and pin of the front motor
	motor_front.enablePin = FRONT_MOTOR_EN_PIN;
	motor_front.enablePort = FRONT_MOTOR_EN_PORT;

	// Initialization of the motor
	motorInit(&motor_front);
}

/**
* @brief Command the given motor with the given speed
* @param speed Wanted speed (<0 to go right, >0 to go left)
*/
void commandFrontMotor(int speed) {
	motorCmd(&motor_front, speed);
}

/**
* @brief Enable the motor
*/
void enableFrontMotor(void) {
  motorEnable(&motor_front, MOTOR_STATE_ON);
}

/**
* @brief Disable the motor
*/
void disableFrontMotor(void) {
  motorEnable(&motor_front, MOTOR_STATE_OFF);
}

