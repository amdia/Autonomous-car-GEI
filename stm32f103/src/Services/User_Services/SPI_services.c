#include "SPI_services.h"
#include "SPI_common.h"
#include "sensors_common.h"

volatile Communication_Typedef receivedFrame;

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

}

void read_spiFrame(void)
{
		
	int dir, angle, speed;
	OctetsFrame_Typedef *octetsFrame =(OctetsFrame_Typedef *)receiveBuffer;
		// ---------------------------------------------------------------------------- //
		//  																Direction motor															//
		//																																							//
		//  	Format of the octets : 																										//
		// 		| Direction | Angle | Angle | Angle | Angle | Angle | Angle | Angle |  		//
		// ---------------------------------------------------------------------------- //
			
		dir = (octetsFrame->direction_motor & DIRECTION_MASK) >> DIRECTION_OFFSET;
	  angle = (octetsFrame->direction_motor & ANGLE_MASK) >> ANGLE_OFFSET;
	
		switch (dir) {
			case 0: // left
				receivedFrame.directionMotor.angle = angle;
			break;
			case 1: // right
				receivedFrame.directionMotor.angle = -angle;	
			break;
			default:
					receivedFrame.directionMotor.angle = 0;	
		}
		
		// -------------------------------------------------------------------------------------------------------- //
		//  																				leftwheel motor 		 																						//
		//																																																					//
		//  	Format of the octet : 																																								//
		// 		| Direction | Direction | Speed     | Speed     | Speed     | Speed     | Speed     | Speed    |  		//
		// -------------------------------------------------------------------------------------------------------- //	
			
		speed = (octetsFrame->left_wheel_motor & SPEED_MASK) >> SPEED_OFFSET;
		
		receivedFrame.rear_motors[REAR_MOTOR_LEFT].speed = speed;
		
		// -------------------------------------------------------------------------------------------------------- //
		//  																					rightwheel motor 		 																					//
		//																																																					//
		//  	Format of the octet : 																																								//
		// 		| Direction | Direction | Speed     | Speed     | Speed     | Speed     | Speed     | Speed    |  		//
		// -------------------------------------------------------------------------------------------------------- //	
			
		speed = (octetsFrame->right_wheel_motor & SPEED_MASK) >> SPEED_OFFSET;
		
		receivedFrame.rear_motors[REAR_MOTOR_RIGHT].speed = speed;
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
	
}





