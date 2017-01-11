#include <stdint.h>
#include <stdlib.h>

#include "services_config.h"
#include "manage_motors.h"
#include "SPI_services.h"
#include "time_systick.h"

#define SPEED 40

int test = 0;
int counter = 0;

int main()
{	
	// Init services
	services_init();

	motor_rear_set_state(REAR_MOTOR_LEFT, MOTOR_STATE_ON);
	motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_ON);
	
	motor_rear_command(REAR_MOTOR_LEFT, SPEED);
	motor_rear_command(REAR_MOTOR_RIGHT, SPEED);
	
	while(receivedFrame.rear_motors[0].distance < 20){}
	
	control_angle_front_motor(-45);
		
	delay_micros(13000000);
		
	control_angle_front_motor(0);
		
	delay_micros(2000000);
		
	motor_rear_set_state(REAR_MOTOR_LEFT, MOTOR_STATE_OFF);
	motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_OFF);		
	
}
