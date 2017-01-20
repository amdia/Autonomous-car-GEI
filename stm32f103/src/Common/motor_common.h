#ifndef __MOTOR_COMMON_H
#define __MOTOR_COMMON_H

/** Number of motors */
#define MOTORS_NB 4
// ------------------------------------------- //
// ---------------- Rear motors--------------- //
// ------------------------------------------- //

/** Number of rear motors */
#define REAR_MOTORS_NB 2

// ------------------------------------------- //
// ---------------- Rear motor left----------- //
// ------------------------------------------- //

/** Pin IN1 for the rear left motor */
#define REAR_MOTOR_LEFT_IN1_PIN        GPIO_Pin_0
/** Port IN1 for the rear left motor */
#define REAR_MOTOR_LEFT_IN1_PORT       GPIOB
/** Channel IN1 for the rear left motor */
#define REAR_MOTOR_LEFT_IN1_CHANNEL    TIM_Channel_3

/** Pin IN2 for the rear left motor */
#define REAR_MOTOR_LEFT_IN2_PIN        GPIO_Pin_1
/** Port IN2 for the rear left motor */
#define REAR_MOTOR_LEFT_IN2_PORT       GPIOB
/** Channel IN2 for the rear left motor */
#define REAR_MOTOR_LEFT_IN2_CHANNEL    TIM_Channel_4

/** Timer for the rear left motor */
#define REAR_MOTOR_LEFT_TIMER          TIM3

// ------------------------------------------- //
// ---------------- Rear motor right---------- //
// ------------------------------------------- //

/** Pin IN1 for the rear right motor */
#define REAR_MOTOR_RIGHT_IN1_PIN        GPIO_Pin_6
/** Port IN1 for the rear right motor */
#define REAR_MOTOR_RIGHT_IN1_PORT       GPIOA
/** Channel IN1 for the rear right motor */
#define REAR_MOTOR_RIGHT_IN1_CHANNEL    TIM_Channel_1

/** Pin IN2 for the rear right motor */
#define REAR_MOTOR_RIGHT_IN2_PIN        GPIO_Pin_7
/** Port IN2 for the rear right motor */
#define REAR_MOTOR_RIGHT_IN2_PORT       GPIOA
/** Channel IN2 for the rear right motor */
#define REAR_MOTOR_RIGHT_IN2_CHANNEL    TIM_Channel_2

/** Timer for the rear right motor */
#define REAR_MOTOR_RIGHT_TIMER          TIM3

// ------------------------------------------- //
// --------- Rear motor enable pins----------- //
// ------------------------------------------- //

/** Pin for rear motor enable */
#define REAR_MOTOR_EN_PIN         GPIO_Pin_6
/** Port for rear motor enable */
#define REAR_MOTOR_EN_PORT        GPIOC


// ------------------------------------------- //
// ---------------- Front motor -------------- //
// ------------------------------------------- //

/** Pin IN1 for the front motor */
#define FRONT_MOTOR_IN1_PIN       GPIO_Pin_7
/** Port IN1 for the front motor */
#define FRONT_MOTOR_IN1_PORT      GPIOB
/** Channel IN1 for the front motor */
#define FRONT_MOTOR_IN1_CHANNEL   TIM_Channel_2

/** Pin IN2 for the front motor */
#define FRONT_MOTOR_IN2_PIN       GPIO_Pin_8
/** Port IN2 for the front motor */
#define FRONT_MOTOR_IN2_PORT      GPIOB
/** Channel IN2 for the front motor */
#define FRONT_MOTOR_IN2_CHANNEL   TIM_Channel_3

/** Pin for front motor enable */
#define FRONT_MOTOR_EN_PIN        GPIO_Pin_9
/** Port for front motor enable */
#define FRONT_MOTOR_EN_PORT       GPIOC

/** Timer for front motor */
#define FRONT_MOTOR_TIMER         TIM4


/**
* @brief Values for the rear motors position (right or left)
*/
typedef enum {
	/** Motor position unknown */
	MOTOR_POSITION_ERROR  = -1,
	/** Left rear motor */
	REAR_MOTOR_LEFT = 0,
	/** Right rear motor */
	REAR_MOTOR_RIGHT = 1
} Motor_Rear_Position;

/**
 * @brief State of the motor
*/
typedef enum {
	/** Motor disabled (0) */
	MOTOR_STATE_OFF = 0,
	/** Motor enabled (1) */
	MOTOR_STATE_ON = 1
} Motor_State;

/**
* @brief Structure that contains informations for the rear motors
*/
typedef struct
{
	/** Speed of the motor in % */
	int speed; 
	/** Distance travelled */
	int distance; 
}MotorRear_Typedef;

/**
* @brief Structure that contains informations for the front motor
*/
typedef struct
{
	/** Angle to turn */
	int angle; 
}MotorFront_Typedef;

#endif //__MOTOR_COMMON_H
