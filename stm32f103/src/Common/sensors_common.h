#ifndef __SENSOR_COMMON_H
#define __SENSOR_COMMON_H

// ------------------------------------------- //
// ------------- Ultrasonic sensors ---------- //
// ------------------------------------------- //

/** Number of ultra sonic sensors */
#define ULTRASONIC_NB 6

/** All ultrasonic sensors share the same trigger pin */
#define ULTRASONIC_TRIG_PIN	    GPIO_Pin_12
/** All ultrasonic sensors share the same trigger port */
#define ULTRASONIC_TRIG_PORT	  	 GPIOC

/** Front center ultrasonic sensor pin */
#define ULTRASONIC_FRONT_CENTER_ECHO_PIN	  GPIO_Pin_0
/** Front center ultrasonic sensor port */
#define ULTRASONIC_FRONT_CENTER_ECHO_PORT   GPIOC

/** Front left ultrasonic sensor pin */
#define ULTRASONIC_FRONT_LEFT_ECHO_PIN	  GPIO_Pin_9
/** Front left ultrasonic sensor port */
#define ULTRASONIC_FRONT_LEFT_ECHO_PORT	GPIOA

/** Front right ultrasonic sensor pin */
#define ULTRASONIC_FRONT_RIGHT_ECHO_PIN	  GPIO_Pin_12
/** Front right ultrasonic sensor port */
#define ULTRASONIC_FRONT_RIGHT_ECHO_PORT	GPIOA

/** Rear center ultrasonic sensor pin */
#define ULTRASONIC_REAR_CENTER_ECHO_PIN	  GPIO_Pin_2
/** Rear center ultrasonic sensor port */
#define ULTRASONIC_REAR_CENTER_ECHO_PORT	GPIOB

/** Rear left ultrasonic sensor pin */
#define ULTRASONIC_REAR_LEFT_ECHO_PIN	  GPIO_Pin_1
/** Rear left ultrasonic sensor port */
#define ULTRASONIC_REAR_LEFT_ECHO_PORT	GPIOC

/** Rear right ultrasonic sensor pin */
#define ULTRASONIC_REAR_RIGHT_ECHO_PIN	  GPIO_Pin_8
/** Rear right ultrasonic sensor port */
#define ULTRASONIC_REAR_RIGHT_ECHO_PORT	GPIOC

/** Time during which the trig pin is high, in microseconds */
#define ULTRASONIC_TRIGGER_DELAY 15 

/**
* @brief Values corresponding to an ultrasonic sensor position
*/
typedef enum {
	/** GPIO pin does not match any known ultrasonic sensor position */
	ULTRASONIC_POSITION_ERROR  = -1,
	/** Value corresponding to the ultrasonic sensor placed at the front center */
	ULTRASONIC_FRONT_CENTER = 0,
	/** Value corresponding to the ultrasonic sensor placed at the front left */
	ULTRASONIC_FRONT_LEFT = 1,
	/** Value corresponding to the ultrasonic sensor placed at the front right */
	ULTRASONIC_FRONT_RIGHT = 2,
	/** Value corresponding to the ultrasonic sensor placed at the rear center */
	ULTRASONIC_REAR_CENTER = 3,
	/** Value corresponding to the ultrasonic sensor placed at the rear left */
	ULTRASONIC_REAR_LEFT = 4,
	/** Value corresponding to the ultrasonic sensor placed at the rear right */
	ULTRASONIC_REAR_RIGHT = 5
} Ultrasonic_Position;

// ------------------------------------------- //
// ---------------- Hall sensors-------------- //
// ------------------------------------------- //

/** Number of hall sensors */
#define HALL_NB 4
/** Number of front hall sensors */
#define HALL_FRONT_NB 2
/** Number of rear hall sensors */
#define HALL_REAR_NB 2

/** Front left hall sensor pin */
#define HALL_FRONT_LEFT_PIN  GPIO_Pin_5
/** Front left hall sensor port */
#define HALL_FRONT_LEFT_PORT GPIOB

/** Front right hall sensor pin */
#define HALL_FRONT_RIGHT_PIN  GPIO_Pin_6
/** Front right hall sensor port */
#define HALL_FRONT_RIGHT_PORT GPIOB

/** Rear left hall sensor pin */
#define HALL_REAR_LEFT_PIN  GPIO_Pin_10
/** Rear left hall sensor port */
#define HALL_REAR_LEFT_PORT GPIOB

/** Rear right hall sensor pin */
#define HALL_REAR_RIGHT_PIN  GPIO_Pin_11
/** Rear right hall sensor port */
#define HALL_REAR_RIGHT_PORT GPIOB

/**
* @brief Values corresponding to a hall sensor position
*/
typedef enum {
	/** GPIO pin does not match any known hall sensor position */
	HALL_POSITION_ERROR  = -1,
	/** Value corresponding to the hall sensor placed at the front left */
	HALL_FRONT_LEFT = 0,
	/** Value corresponding to the hall sensor placed at the front right */
	HALL_FRONT_RIGHT = 1,
	/** Value corresponding to the hall sensor placed at the rear left */
	HALL_REAR_LEFT = 2,
	/** Value corresponding to the hall sensor placed at the rear right */
	HALL_REAR_RIGHT = 3
} Hall_Position;

#endif // __SENSOR_COMMON_H
