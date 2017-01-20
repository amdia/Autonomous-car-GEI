/**
* @file test_motors.c
* @brief Application layer to test if the motors are functionnal.
*/
#include <stdint.h>
#include <stdlib.h>
#include "services_config.h"
#include "manage_motors.h"
#include "SPI_services.h"
#include "time_systick.h"

/* Private define ------------------------------------------------------------*/
#define SPEED 40
#define SECONDS 1e6

/**
* @brief Initialize the services and execute the choosen test function(s)
*/
int main()
{	
	// Init services
	services_init();
	
	//test_go_forward();
	//test_go_backward();
	//test_turn();
	//ninety_degrees_bend();
}

/**
* @brief Test if the rear motors are functionnal to go forward
*/
void test_go_forward(void){
	motor_rear_set_state(REAR_MOTOR_LEFT, MOTOR_STATE_ON);
	motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_ON);
	
	motor_rear_command(REAR_MOTOR_LEFT, SPEED);
	motor_rear_command(REAR_MOTOR_RIGHT, SPEED);
	
	delay_micros(6*SECONDS);
	
	motor_rear_set_state(REAR_MOTOR_LEFT, MOTOR_STATE_OFF);
	motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_OFF);	
}

/**
* @brief Test if the rear motors are functionnal to go backward
*/
void test_go_backward(void){
	motor_rear_set_state(REAR_MOTOR_LEFT, MOTOR_STATE_ON);
	motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_ON);
	
	motor_rear_command(REAR_MOTOR_LEFT, -SPEED);
	motor_rear_command(REAR_MOTOR_RIGHT, -SPEED);
	
	delay_micros(6*SECONDS);
	
	motor_rear_set_state(REAR_MOTOR_LEFT, MOTOR_STATE_OFF);
	motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_OFF);	
}

/**
* @brief Test if the front motors are functionnal
*
* The if(micros() > t_temp || on_stop) block in @ref manage_motors.c has to be commented 
* and the while(micros() <=  t_temp) has to be uncommented
*/
void test_turn(void){
	// Value can be changed in the debugger when it's running
	int angle = 0; 
	while(1){
		control_angle_front_motor(-angle);
		delay_micros(5*SECONDS);
	}
}

/**
* @brief Test the calibration of a 90 degrees bend
*/
void ninety_degrees_bend(void){
	motor_rear_set_state(REAR_MOTOR_LEFT, MOTOR_STATE_ON);
	motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_ON);
	
	motor_rear_command(REAR_MOTOR_LEFT, SPEED);
	motor_rear_command(REAR_MOTOR_RIGHT, SPEED);
	
	while(communicationFrame.rear_motors[0].distance < 20){}
	
	control_angle_front_motor(-45);
		
	delay_micros(13*SECONDS);
		
	control_angle_front_motor(0);
		
	delay_micros(2*SECONDS);
		
	motor_rear_set_state(REAR_MOTOR_LEFT, MOTOR_STATE_OFF);
	motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_OFF);	
}

