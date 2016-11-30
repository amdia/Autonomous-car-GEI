#ifndef __HALL_SENSOR_H
#define __HALL_SENSOR_H

#include <stdint.h>
#include "sensors_common.h"

void hall_init(void);

void hall_callback(Hall_Position pos);

Hall_Position get_hall_position(uint16_t GPIO_Pin);

#endif // __HALL_SENSOR_H
