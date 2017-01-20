#ifndef __US_SENSOR_H
#define __US_SENSOR_H

#include <stdint.h>
#include "sensors_common.h"

/** Constant conversion to calculate the distance between the ultrasonic sensor and an object 
* according to the passed time between the trig of the pulse and the detection of the return of the pulse */
#define ULTRASONIC_CONVERSION_CONSTANT  58.2
/** Time to wait the reset of the echo pin and the reinitialization of the pin */
#define ULTRASONIC_DELAY_RESET_ECHO_PIN 100

int ultrasonic_get_distance(Ultrasonic_Position pos);

void ultrasonic_trig_all(void);

void ultrasonic_init(void);

void ultrasonic_callback(Ultrasonic_Position pos);

Ultrasonic_Position get_ultrasonic_position(uint16_t GPIO_Pin);


#endif // __US_SENSOR_H
