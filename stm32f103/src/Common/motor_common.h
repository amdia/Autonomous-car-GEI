#ifndef __MOTOR_COMMON_H
#define __MOTOR_COMMON_H


// ------------------------------------------- //
// ---------------- Rear motors--------------- //
// ------------------------------------------- //

#define REAR_MOTORS_NB 2
#define MOTORS_NB 4

// ------------------------------------------- //
// ---------------- Rear motor left--------------- //
// ------------------------------------------- //

// IN1 pin
#define REAR_MOTOR_LEFT_IN1_PIN        GPIO_Pin_0
#define REAR_MOTOR_LEFT_IN1_PORT       GPIOB
#define REAR_MOTOR_LEFT_IN1_CHANNEL    TIM_Channel_3

// IN2 pin
#define REAR_MOTOR_LEFT_IN2_PIN        GPIO_Pin_1
#define REAR_MOTOR_LEFT_IN2_PORT       GPIOB
#define REAR_MOTOR_LEFT_IN2_CHANNEL    TIM_Channel_4

// Timer
#define REAR_MOTOR_LEFT_TIMER          TIM3

// ------------------------------------------- //
// ---------------- Rear motor right--------------- //
// ------------------------------------------- //

// IN1 pin
#define REAR_MOTOR_RIGHT_IN1_PIN        GPIO_Pin_6
#define REAR_MOTOR_RIGHT_IN1_PORT       GPIOA
#define REAR_MOTOR_RIGHT_IN1_CHANNEL    TIM_Channel_1

// IN2 pin
#define REAR_MOTOR_RIGHT_IN2_PIN        GPIO_Pin_7
#define REAR_MOTOR_RIGHT_IN2_PORT       GPIOA
#define REAR_MOTOR_RIGHT_IN2_CHANNEL    TIM_Channel_2

// Timer
#define REAR_MOTOR_RIGHT_TIMER          TIM3

// ------------------------------------------- //
// --------- Rear motor enable pins----------- //
// ------------------------------------------- //

#define REAR_MOTOR_EN_PIN         GPIO_Pin_6
#define REAR_MOTOR_EN_PORT        GPIOC


// ------------------------------------------- //
// ---------------- Front motor -------------- //
// ------------------------------------------- //

// IN1 pin
#define FRONT_MOTOR_IN1_PIN       GPIO_Pin_7
#define FRONT_MOTOR_IN1_PORT      GPIOB
#define FRONT_MOTOR_IN1_CHANNEL   TIM_Channel_2

// IN2 pin
#define FRONT_MOTOR_IN2_PIN       GPIO_Pin_8
#define FRONT_MOTOR_IN2_PORT      GPIOB
#define FRONT_MOTOR_IN2_CHANNEL   TIM_Channel_3

// EN pin
#define FRONT_MOTOR_EN_PIN        GPIO_Pin_9
#define FRONT_MOTOR_EN_PORT       GPIOC

// Timer
#define FRONT_MOTOR_TIMER         TIM4

// Speed
#define FRONT_MOTOR_SPEED         30

//Structures for rear motors
typedef enum {
	MOTOR_POSITION_ERROR  = -1,
	REAR_MOTOR_LEFT = 0,
	REAR_MOTOR_RIGHT = 1
} Motor_Rear_Position;

typedef enum {
  MOTOR_STATE_OFF = 0,
  MOTOR_STATE_ON = 1
} Motor_State;

/**
 * \struct MotorRear_Typedef
 * \brief Structure that contains informations for the rear motors
 */
typedef struct
{
	int speed; /*!< Speed of the motor in % */
	int distance; /*!< Distance travelled */
}MotorRear_Typedef;

/**
 * \struct MotorFront_Typedef
 * \brief Structure that contains informations for the front motor
 */
typedef struct
{
	int angle; /*!< Angle to turn */
}MotorFront_Typedef;

#endif //__MOTOR_COMMON_H
