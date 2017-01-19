#include "drivers_car_config.h"
#include "hall_sensor.h"
#include "us_sensor.h"
#include "motor_front.h"
#include "motor_rear.h"

void drivers_car_init(void) {

	// Config Hall and Ultrasonic sensors
	hall_init();
	ultrasonic_init();
	
	// config motors
	initFrontMotor();
	disableFrontMotor();
	motors_rear_init();
}
