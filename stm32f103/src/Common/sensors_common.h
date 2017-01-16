#ifndef __SENSOR_COMMON_H
#define __SENSOR_COMMON_H

// ------------------------------------------ //
// ------------- Ultrasonic sensors ---------- //
// ------------------------------------------- //

// Number of ultra sonic sensors
#define ULTRASONIC_NB 6

// All ultrasonic sensors share the same trigger pin
#define ULTRASONIC_TRIG_PIN	    GPIO_Pin_12
#define ULTRASONIC_TRIG_PORT	  	 GPIOC

// Front center
#define ULTRASONIC_FRONT_CENTER_ECHO_PIN	  GPIO_Pin_0
#define ULTRASONIC_FRONT_CENTER_ECHO_PORT   GPIOC

// Front left
#define ULTRASONIC_FRONT_LEFT_ECHO_PIN	  GPIO_Pin_9
#define ULTRASONIC_FRONT_LEFT_ECHO_PORT	GPIOA

// Front right
#define ULTRASONIC_FRONT_RIGHT_ECHO_PIN	  GPIO_Pin_12
#define ULTRASONIC_FRONT_RIGHT_ECHO_PORT	GPIOA

// Rear center
#define ULTRASONIC_REAR_CENTER_ECHO_PIN	  GPIO_Pin_2
#define ULTRASONIC_REAR_CENTER_ECHO_PORT	GPIOB

// Rear left
#define ULTRASONIC_REAR_LEFT_ECHO_PIN	  GPIO_Pin_1
#define ULTRASONIC_REAR_LEFT_ECHO_PORT	GPIOC

// Rear right
#define ULTRASONIC_REAR_RIGHT_ECHO_PIN	  GPIO_Pin_8
#define ULTRASONIC_REAR_RIGHT_ECHO_PORT	GPIOC

#define TEMPS_TRIG  250e3
#define ULTRASONIC_TRIGGER_DELAY 15 //in microseconds

typedef enum Ultrasonic_Position {
	ULTRASONIC_POSITION_ERROR  = -1,
	ULTRASONIC_FRONT_CENTER = 0,
	ULTRASONIC_FRONT_LEFT = 1,
	ULTRASONIC_FRONT_RIGHT = 2,
	ULTRASONIC_REAR_CENTER = 3,
	ULTRASONIC_REAR_LEFT = 4,
	ULTRASONIC_REAR_RIGHT = 5
} Ultrasonic_Position;

typedef enum {
  DOWN,
  UP
} Ultrasonic_State;

// ------------------------------------------- //
// ---------------- Hall sensors-------------- //
// ------------------------------------------- //

// Number of hall sensors
#define HALL_NB 4
#define HALL_FRONT_NB 2
#define HALL_REAR_NB 2

// Front left
#define HALL_FRONT_LEFT_PIN  GPIO_Pin_5
#define HALL_FRONT_LEFT_PORT GPIOB

// Front right
#define HALL_FRONT_RIGHT_PIN  GPIO_Pin_6
#define HALL_FRONT_RIGHT_PORT GPIOB

// Rear left
#define HALL_REAR_LEFT_PIN  GPIO_Pin_10
#define HALL_REAR_LEFT_PORT GPIOB

// Rear right
#define HALL_REAR_RIGHT_PIN  GPIO_Pin_11
#define HALL_REAR_RIGHT_PORT GPIOB

typedef enum {
	HALL_POSITION_ERROR  = -1,
	HALL_FRONT_LEFT = 0,
	HALL_FRONT_RIGHT = 1,
	HALL_REAR_LEFT = 2,
	HALL_REAR_RIGHT = 3
} Hall_Position;

#endif // __SENSOR_COMMON_H
