#ifndef __US_SENSOR_H
#define __US_SENSOR_H

#include <stdint.h>

#define ULTRASONIC_CONVERSION_CONSTANT  58.2
#define MAX_TIME_PULSE 						      22600.0
#define ULTRASONIC_DELAY_RESET_ECHO_PIN 100

typedef enum Ultrasonic_Position {
	ULTRASONIC_POSITION_ERROR  = -1,
	ULTRASONIC_AVC = 0,
	ULTRASONIC_AVG = 1,
	ULTRASONIC_AVD = 2,
	ULTRASONIC_ARC = 3,
	ULTRASONIC_ARG = 4,
	ULTRASONIC_ARD = 5
} Ultrasonic_Position;

typedef enum {
  DOWN,
  UP
} Ultrasonic_State;

float ultrasonic_get_distance(Ultrasonic_Position pos);

void ultrasonic_trig_all(void);

void init_ultrasonic_sensors(void);

void ultrasonic_callback(Ultrasonic_Position pos);


#endif // __US_SENSOR_H
