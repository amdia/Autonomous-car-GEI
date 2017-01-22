#ifndef _MOTOR_CONTROL_H_
#define _MOTOR_CONTROL_H_

#include "PWM_Output.h"
#include "motor_common.h"

/** Period of the motors PWM */
#define MOTOR_PWM_PERIOD_US           100
/** Default duty cycle of the motors PWM */
#define MOTOR_PWM_DEFAULT_DUTY_CYCLE  50
/** Maximal speed for the motor, without unit */
#define MOTOR_SPEED_MAX               100
/** Minimal speed for the motor, without unit */
#define MOTOR_SPEED_MIN               (-MOTOR_SPEED_MAX)
/** Speed range for the motor */
#define MOTOR_SPEED_RANGE 				  (MOTOR_SPEED_MAX - MOTOR_SPEED_MIN)

/**
* @brief Structure that contains information about the configuration of a motor
*/
typedef struct { 
	/** Contain information about the configuration of the pwm 1 */
	PWM_TypeDef pwm1;
	/** Contain information about the configuration of the pwm 2 */
	PWM_TypeDef pwm2;
	/** Port to which the motor is connected */
	GPIO_TypeDef* enablePort;
	/** Pin to which the motor is connected */
	uint16_t enablePin;
} Motor_TypeDef;

void motorInit(Motor_TypeDef* init_struct);
void motorCmd(Motor_TypeDef* motor_struct, int speed);
void motorEnable(Motor_TypeDef* motor_struct, Motor_State enable);

#endif // _MOTOR_CONTROL_H_
