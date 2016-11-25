#include <stdint.h>
#include <stdlib.h>
#include "motor_front.h"
#include "motor_rear.h"
#include "SPI_functions.h"
#include "drivers_car_config.h"
#include "manage_motors.h"

// /!\ Commenter la ligne scheduler_timer_init(); du fichier drivers_car_config.c

void manage_motor_test(Communication_Typedef receivedFrame);
int main()
{
	unsigned char sendBuffer[BUFFER_SIZE] = {0}; 
	unsigned char receiveBuffer[BUFFER_SIZE] = {0};
	Communication_Typedef receivedFrame;
	
	// Init SPI communication
	InitializeSPI2(receiveBuffer, sendBuffer);
	init_spiFrame(&receivedFrame);
	// Init all the rest
	services_init();
	
	// Set random value to the structure
			// Sensors values 
	receivedFrame.frontLeftUltrasound.distance = 80;
	receivedFrame.frontRightUltrasound.distance = 81;
	receivedFrame.frontCenterUltrasound.distance = 82;
	receivedFrame.rearLeftUltrasound.distance = 83;
	receivedFrame.rearRightUltrasound.distance = 84;
	receivedFrame.rearCenterUltrasound.distance = 85;
			// Battery value
	receivedFrame.battery.state = 86;

	while(1)
	{
		read_spiFrame(receiveBuffer, &receivedFrame); // Read the Frame 
		write_spiFrame(sendBuffer, receivedFrame); // Write the Frame 
		manage_motor_test(receivedFrame);
	}
}

void manage_motor_test(Communication_Typedef receivedFrame)
{
	// Left wheel
	if(receivedFrame.leftWheelMotor.direction == MOTOR_REAR_FORWARD)
	{
		motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_ON);
		motor_rear_command(MOTOR_ARG, receivedFrame.leftWheelMotor.speed);
	}
	else if(receivedFrame.leftWheelMotor.direction == MOTOR_REAR_BACKWARD)
	{
		motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_ON);
		motor_rear_command(MOTOR_ARG, -receivedFrame.leftWheelMotor.speed);
	}
	else
	{
		motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_OFF);
	}
	
	// Right wheel
	if(receivedFrame.rightWheelMotor.direction == MOTOR_REAR_FORWARD)
	{
		motor_rear_set_state(MOTOR_ARD, MOTOR_STATE_ON);
		motor_rear_command(MOTOR_ARD, receivedFrame.rightWheelMotor.speed);
	}
	else if(receivedFrame.leftWheelMotor.direction == MOTOR_REAR_BACKWARD)
	{
		motor_rear_set_state(MOTOR_ARD, MOTOR_STATE_ON);
		motor_rear_command(MOTOR_ARD, -receivedFrame.rightWheelMotor.speed);
	}
	else
	{
		motor_rear_set_state(MOTOR_ARD, MOTOR_STATE_OFF);
	}
	
}



