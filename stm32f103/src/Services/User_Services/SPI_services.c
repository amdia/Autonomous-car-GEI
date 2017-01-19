*/
#include "SPI_services.h"
#include "SPI_common.h"
#include "sensors_common.h"

volatile Communication_Typedef receivedFrame;

static int convert_2_int(uint8_t octet);

void init_spiFrame(void)
{
	// Initialization of the motors
	receivedFrame.directionMotor.angle = 0;
	
	receivedFrame.rear_motors[REAR_MOTOR_LEFT].speed = 0;
	receivedFrame.rear_motors[REAR_MOTOR_LEFT].distance = 0;
	
	receivedFrame.rear_motors[REAR_MOTOR_RIGHT].speed = 0;
	receivedFrame.rear_motors[REAR_MOTOR_RIGHT].distance = 0;

	// Initialization of the sensors
	receivedFrame.ultrasounds[ULTRASONIC_FRONT_CENTER].distance = 0;
	receivedFrame.ultrasounds[ULTRASONIC_FRONT_LEFT].distance = 0;
	receivedFrame.ultrasounds[ULTRASONIC_FRONT_RIGHT].distance = 0;
	receivedFrame.ultrasounds[ULTRASONIC_REAR_CENTER].distance = 0;
	receivedFrame.ultrasounds[ULTRASONIC_REAR_LEFT].distance = 0;
	receivedFrame.ultrasounds[ULTRASONIC_REAR_RIGHT].distance = 0;

	// Initialization of the battery 
	receivedFrame.battery.state = 0;
	
	// Initialization of the ack byte 
	receivedFrame.ack_byte.reset_distance = 0;
	receivedFrame.ack_byte.ack_distance = 0;

}

void read_spiFrame(void)
{
	int angle, speed, reset;
	
	// Load the buffer in an OctetsFrame
	OctetsFrame_Typedef *octetsFrame =(OctetsFrame_Typedef *)receiveBuffer;
	
	// Direction motor
	angle = octetsFrame->direction_motor;
	receivedFrame.directionMotor.angle = convert_2_int(angle);	

	// leftwheel motor
	speed = octetsFrame->left_wheel_motor;
	receivedFrame.rear_motors[REAR_MOTOR_LEFT].speed = convert_2_int(speed);

	// rightwheel motor
	speed = octetsFrame->right_wheel_motor;
	receivedFrame.rear_motors[REAR_MOTOR_RIGHT].speed = convert_2_int(speed);
	
	// -------------------------------------------------------------------------------------------------------- //
	//  																							Ack byte 		 							//
	//																																				//
	//  	Format of the octet : 																											//
	// 		|   00   |   00   |   00   |   00   |   00   |   00   |   00   |  reset distance |  ack distance | //
	// -------------------------------------------------------------------------------------------------------- //	
	reset = octetsFrame->ack_byte;
	receivedFrame.ack_byte.reset_distance = (reset >> 1) & 0x1;
	
}

void write_spiFrame(void)
{
	OctetsFrame_Typedef *octetsFrame =(OctetsFrame_Typedef *)sendBuffer;
	
	// Motor values equals 0
	octetsFrame->direction_motor = 0;
	octetsFrame->left_wheel_motor = 0;
	octetsFrame->right_wheel_motor = 0;
	
	//distance both wheels
	octetsFrame->left_wheel_motor_distance = (int8_t)receivedFrame.rear_motors[REAR_MOTOR_LEFT].distance;
	octetsFrame->right_wheel_motor_distance = (int8_t)receivedFrame.rear_motors[REAR_MOTOR_RIGHT].distance;

	// Sensors values 
	octetsFrame->front_left_ultrasonic = (int8_t)receivedFrame.ultrasounds[ULTRASONIC_FRONT_LEFT].distance;
	octetsFrame->front_right_ultrasonic = (int8_t)receivedFrame.ultrasounds[ULTRASONIC_FRONT_RIGHT].distance;
	octetsFrame->front_center_ultrasonic = (int8_t)receivedFrame.ultrasounds[ULTRASONIC_FRONT_CENTER].distance;
	octetsFrame->rear_left_ultrasonic = (int8_t)receivedFrame.ultrasounds[ULTRASONIC_REAR_LEFT].distance;
	octetsFrame->rear_right_ultrasonic= (int8_t)receivedFrame.ultrasounds[ULTRASONIC_REAR_RIGHT].distance;
	octetsFrame->rear_center_ultrasonic = (int8_t)receivedFrame.ultrasounds[ULTRASONIC_REAR_CENTER].distance;

	// Battery
	octetsFrame->battery = (int8_t)receivedFrame.battery.state;
	
	// Ack byte
	octetsFrame->ack_byte = (int8_t) receivedFrame.ack_byte.ack_distance;
	
}

int convert_2_int(uint8_t octet){
	if(octet > 127)
		return (256 - octet) * (-1);
	else
		return octet;
}





