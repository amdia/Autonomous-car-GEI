#include "SPI_functions.h"
#include <string.h>

		// Motors variables
int direction_direction_motor = 0;
int speed_direction_motor = 0;
int direction_left_motor = 0;
int speed_left_motor = 0;
int direction_right_motor = 0;
int speed_right_motor = 0;

int main()
{
	unsigned char sendBuffer[BUFFER_SIZE] = {0}; 
	unsigned char receiveBuffer[BUFFER_SIZE] = {0};
	Communication_Typedef receivedFrame;
	
	// Init SPI communication
	InitializeSPI2(receiveBuffer, sendBuffer);
	init_spiFrame(&receivedFrame);
	
	// Initialization for the test 
			// Sensors values 
	receivedFrame.frontLeftUltrasound.distance = 80;
	receivedFrame.frontRightUltrasound.distance = 81;
	receivedFrame.frontCenterUltrasound.distance = 82;
	receivedFrame.rearLeftUltrasound.distance = 83;
	receivedFrame.rearRightUltrasound.distance = 84;
	receivedFrame.rearCenterUltrasound.distance = 85;
			// Battery value
	receivedFrame.battery.state = 86;

	
	while(1){

		read_spiFrame(receiveBuffer, &receivedFrame); // Read the Frame 
		write_spiFrame(sendBuffer, receivedFrame); // Write the Frame 
	  direction_direction_motor = receivedFrame.directionMotor.direction;
		speed_direction_motor = receivedFrame.directionMotor.speed;
		direction_right_motor = receivedFrame.rightWheelMotor.direction;
		speed_right_motor = receivedFrame.rightWheelMotor.speed;
		direction_left_motor = receivedFrame.leftWheelMotor.direction;
		speed_left_motor = receivedFrame.leftWheelMotor.speed;
		
		
		// variation of the value to test the programm
		for(int i=0; i<5000; i++){}
		receivedFrame.frontLeftUltrasound.distance++;
		receivedFrame.frontRightUltrasound.distance++;
		
		read_spiFrame(receiveBuffer, &receivedFrame); // Read the Frame 
		write_spiFrame(sendBuffer, receivedFrame); // Write the Frame 
		direction_direction_motor = receivedFrame.directionMotor.direction;
		speed_direction_motor = receivedFrame.directionMotor.speed;
		direction_left_motor = receivedFrame.leftWheelMotor.direction;
		speed_left_motor = receivedFrame.leftWheelMotor.speed;
		direction_right_motor = receivedFrame.rightWheelMotor.direction;
		speed_right_motor = receivedFrame.rightWheelMotor.speed;

		for(int i=0; i<5000; i++){}
		receivedFrame.frontLeftUltrasound.distance--;
		receivedFrame.frontRightUltrasound.distance--;
	
	}

}

