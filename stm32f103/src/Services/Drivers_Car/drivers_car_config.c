/**
* @file drivers_car_config.c
* @brief Driver car layer for the initialization of all the "car" drivers
*/

#include "drivers_car_config.h"
#include "hall_sensor.h"
#include "us_sensor.h"
#include "motor_front.h"
#include "motor_rear.h"

/**
* @brief Initialization of the hall sensors, the ultrasonic sensors, the front motors and the rear motors
*/
void drivers_car_init(void) {

	// Config Hall and Ultrasonic sensors
	hall_init();
	ultrasonic_init();
	
	// Config motors
	initFrontMotor();
	disableFrontMotor();
	motors_rear_init();
}
