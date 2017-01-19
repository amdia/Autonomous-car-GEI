#ifndef __US_SENSOR_H
#define __US_SENSOR_H

#include <stdint.h>
#include "sensors_common.h"

#define ULTRASONIC_CONVERSION_CONSTANT  58.2
#define MAX_TIME_PULSE 						      22600.0
#define ULTRASONIC_DELAY_RESET_ECHO_PIN 100

int ultrasonic_get_distance(Ultrasonic_Position pos);

void ultrasonic_trig_all(void);

void ultrasonic_init(void);

void ultrasonic_callback(Ultrasonic_Position pos);

Ultrasonic_Position get_ultrasonic_position(uint16_t GPIO_Pin);


#endif // __US_SENSOR_H
