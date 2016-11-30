#include <stdint.h>
#include <stdlib.h>
#include "motor_front.h"
#include "motor_rear.h"
#include "SPI_functions.h"
#include "drivers_car_config.h"
#include "manage_motors.h"

// /!\ Commenter la ligne scheduler_timer_init(); du fichier drivers_car_config.c
volatile uint8_t sendBuffer[BUFFER_SIZE] = {0}; 
volatile uint8_t receiveBuffer[BUFFER_SIZE] = {0};
volatile Communication_Typedef receivedFrame;
Communication_Typedef * p_receivedFrame = (Communication_Typedef *)&receivedFrame;
void manage_motor_test(Communication_Typedef receivedFrame);
int main()
{
//	unsigned char sendBuffer[BUFFER_SIZE] = {0}; 
//	unsigned char receiveBuffer[BUFFER_SIZE] = {0};
//	Communication_Typedef receivedFrame;
	
	// Init SPI communication
	//InitializeSPI2(receiveBuffer, sendBuffer);
	InitializeSPI2((uint8_t *)receiveBuffer, (uint8_t *)sendBuffer);
	init_spiFrame(p_receivedFrame);
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
		read_spiFrame((uint8_t *)receiveBuffer, p_receivedFrame); // Read the Frame 
		write_spiFrame((uint8_t *)sendBuffer, receivedFrame); // Write the Frame 
		//manage_motor_test(receivedFrame);
	}
}

void manage_motor_test(Communication_Typedef receivedFrame)
{
	// Left wheel
	if(receivedFrame.wheelMotor.direction == MOTOR_REAR_FORWARD)
	{
		motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_ON);
		motor_rear_command(MOTOR_ARG, receivedFrame.wheelMotor.speed);
	}
	else if(receivedFrame.wheelMotor.direction == MOTOR_REAR_BACKWARD)
	{
		motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_ON);
		motor_rear_command(MOTOR_ARG, -receivedFrame.wheelMotor.speed);
	}
	else
	{
		motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_OFF);
	}
	
	
}



