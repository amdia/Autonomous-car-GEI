#ifndef _SERVICE_CONFIG_H_
#define _SERVICE_CONFIG_H_

#include "stm32f10x_gpio.h"

// Global definitions
#define GPIO_SPEED  GPIO_Speed_50MHz
#define TIMER_NUMBER			4

// ------------------------------------------ //
// ------------- Interruption Priorities------ //
// ------------------------------------------- //
// All ultrasonic sensor interrupts share the same priority
#define ULTRASONIC_PRIO 8

// All hall sensor interrupts share the same priority
#define HALL_PRIO 7

#define SCHEDULER_IT_PRIORITY		10

// ------------------------------------------ //
// ------------- Ultrasonic sensors ---------- //
// ------------------------------------------- //

// Number of ultra sonic sensors
#define ULTRASONIC_NB 6

// All ultrasonic sensors share the same trigger pin
#define ULTRASONIC_TRIG_PIN	    GPIO_Pin_12
#define ULTRASONIC_TRIG_PORT	  	 GPIOC

// Front center
#define ULTRASONIC_AVC_ECHO_PIN	  GPIO_Pin_0
#define ULTRASONIC_AVC_ECHO_PORT   GPIOC

// Front left
#define ULTRASONIC_AVG_ECHO_PIN	  GPIO_Pin_9
#define ULTRASONIC_AVG_ECHO_PORT	GPIOA

// Front right
#define ULTRASONIC_AVD_ECHO_PIN	  GPIO_Pin_12
#define ULTRASONIC_AVD_ECHO_PORT	GPIOA

// Rear center
#define ULTRASONIC_ARC_ECHO_PIN	  GPIO_Pin_2
#define ULTRASONIC_ARC_ECHO_PORT	GPIOB

// Rear left
#define ULTRASONIC_ARG_ECHO_PIN	  GPIO_Pin_1
#define ULTRASONIC_ARG_ECHO_PORT	GPIOC

// Rear right
#define ULTRASONIC_ARD_ECHO_PIN	  GPIO_Pin_8
#define ULTRASONIC_ARD_ECHO_PORT	GPIOC

#define TEMPS_TRIG  250e3
#define ULTRASONIC_TRIGGER_DELAY 30

// ------------------------------------------- //
// ---------------- Hall sensors-------------- //
// ------------------------------------------- //

// Number of hall sensors
#define HALL_NB 4
#define HALL_FRONT_NB 2
#define HALL_REAR_NB 2

// Front left
#define HALL_AVG_PIN  GPIO_Pin_5
#define HALL_AVG_PORT GPIOB

// Front right
#define HALL_AVD_PIN  GPIO_Pin_6
#define HALL_AVD_PORT GPIOB

// Rear left
#define HALL_ARG_PIN  GPIO_Pin_10
#define HALL_ARG_PORT GPIOB

// Rear right
#define HALL_ARD_PIN  GPIO_Pin_11
#define HALL_ARD_PORT GPIOB

// ------------------------------------------- //
// ---------------- Rear motors--------------- //
// ------------------------------------------- //

#define REAR_MOTORS_NB 2

// ------------------------------------------- //
// ---------------- Rear motor 1--------------- //
// ------------------------------------------- //

// IN1 pin
#define REAR_MOTOR1_IN1_PIN        GPIO_Pin_0
#define REAR_MOTOR1_IN1_PORT       GPIOB
#define REAR_MOTOR1_IN1_CHANNEL    TIM_Channel_3

// IN2 pin
#define REAR_MOTOR1_IN2_PIN        GPIO_Pin_1
#define REAR_MOTOR1_IN2_PORT       GPIOB
#define REAR_MOTOR1_IN2_CHANNEL    TIM_Channel_4

// Timer
#define REAR_MOTOR1_TIMER          TIM3

// ------------------------------------------- //
// ---------------- Rear motor 2--------------- //
// ------------------------------------------- //

// IN1 pin
#define REAR_MOTOR2_IN1_PIN        GPIO_Pin_6
#define REAR_MOTOR2_IN1_PORT       GPIOA
#define REAR_MOTOR2_IN1_CHANNEL    TIM_Channel_1

// IN2 pin
#define REAR_MOTOR2_IN2_PIN        GPIO_Pin_7
#define REAR_MOTOR2_IN2_PORT       GPIOA
#define REAR_MOTOR2_IN2_CHANNEL    TIM_Channel_2

// Timer
#define REAR_MOTOR2_TIMER          TIM3

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

// ------------------------------------------- //
// -------------- Init function -------------- //
// ------------------------------------------- //
void services_init(void);

// ------------------------------------------- //
// -------------- Scheduler------------------- //
// ------------------------------------------- //

#define SCHEDULER_TIMER         	TIM2

#endif // _SERVICE_CONFIG_H_
