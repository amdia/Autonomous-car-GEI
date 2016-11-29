#include "SPI_services.h"

#include "motor_rear.h"
#include "us_sensor.h"

__IO uint8_t sendBuffer[BUFFER_SIZE] = {0}; 
__IO uint8_t receiveBuffer[BUFFER_SIZE] = {0};
__IO Communication_Typedef receivedFrame;

void init_spiFrame(Communication_Typedef *comStruct)
{
	// Initialization of the motors
	comStruct->directionMotor.direction = STOP;
	comStruct->directionMotor.angle = 0;
	
	comStruct->rear_motors[MOTOR_ARG].direction = MOTOR_REAR_STOP;
	comStruct->rear_motors[MOTOR_ARG].speed = 0;
	comStruct->rear_motors[MOTOR_ARG].distance = 0;
	
	comStruct->rear_motors[MOTOR_ARD].direction = MOTOR_REAR_STOP;
	comStruct->rear_motors[MOTOR_ARD].speed = 0;
	comStruct->rear_motors[MOTOR_ARD].distance = 0;

	// Initialization of the sensors
	comStruct->ultrasounds[ULTRASONIC_AVG].distance = 0;
	comStruct->ultrasounds[ULTRASONIC_AVD].distance = 0;
	comStruct->ultrasounds[ULTRASONIC_AVC].distance = 0;
	comStruct->ultrasounds[ULTRASONIC_ARG].distance = 0;
	comStruct->ultrasounds[ULTRASONIC_ARD].distance = 0;
	comStruct->ultrasounds[ULTRASONIC_ARC].distance = 0;

	// Initialization of the battery 
	comStruct->battery.state = 0;

}

void read_spiFrame(uint8_t* spiFrame, Communication_Typedef* comStruct)
{
		
		int dir, angle, speed;
		// ---------------------------------------------------------------------------- //
		//  																Direction motor															//
		//																																							//
		//  	Format of the octets : 																										//
		// 		| Direction | Angle | Angle | Angle | Angle | Angle | Angle | Angle |  		//
		// ---------------------------------------------------------------------------- //
			
		dir = (spiFrame[DIRECTION_MOTOR] & DIRECTION_MASK) >> DIRECTION_OFFSET;
	  angle = (spiFrame[DIRECTION_MOTOR] & ANGLE_MASK) >> ANGLE_OFFSET;
	
		switch (dir) {
			case 0: // left
				comStruct->directionMotor.direction = LEFT;
				comStruct->directionMotor.angle = angle;
			break;
			case 1: // right
				comStruct->directionMotor.direction = RIGHT;
				comStruct->directionMotor.angle = -angle;	
			break;
			default:
					comStruct->directionMotor.direction = STOP;
					comStruct->directionMotor.angle = 0;	
		}
		
		// -------------------------------------------------------------------------------------------------------- //
		//  																				leftwheel motor 		 																						//
		//																																																					//
		//  	Format of the octet : 																																								//
		// 		| Direction | Direction | Speed     | Speed     | Speed     | Speed     | Speed     | Speed    |  		//
		// -------------------------------------------------------------------------------------------------------- //	
			
		dir = (spiFrame[LEFT_WHEEL_MOTOR] & DIRECTION_MASK) >> DIRECTION_OFFSET;
		speed = (spiFrame[LEFT_WHEEL_MOTOR] & SPEED_MASK) >> SPEED_OFFSET;
		
		if(speed == 0)
		{
			comStruct->rear_motors[MOTOR_ARG].direction = MOTOR_REAR_STOP;
			comStruct->rear_motors[MOTOR_ARG].speed = speed;
		}
		else
		{
			switch (dir) {
				case 0: // forward
					comStruct->rear_motors[MOTOR_ARG].direction = MOTOR_REAR_FORWARD;
					comStruct->rear_motors[MOTOR_ARG].speed = speed;
				break;
				case 1: // backward
					comStruct->rear_motors[MOTOR_ARG].direction = MOTOR_REAR_BACKWARD;
					comStruct->rear_motors[MOTOR_ARG].speed = speed;
				break;
				default:
					comStruct->rear_motors[MOTOR_ARG].direction = MOTOR_REAR_STOP;
					comStruct->rear_motors[MOTOR_ARG].speed = 0;
			}
		}
		
		// -------------------------------------------------------------------------------------------------------- //
		//  																					rightwheel motor 		 																					//
		//																																																					//
		//  	Format of the octet : 																																								//
		// 		| Direction | Direction | Speed     | Speed     | Speed     | Speed     | Speed     | Speed    |  		//
		// -------------------------------------------------------------------------------------------------------- //	
			
		dir = (spiFrame[RIGHT_WHEEL_MOTOR] & DIRECTION_MASK) >> DIRECTION_OFFSET;
		speed = (spiFrame[RIGHT_WHEEL_MOTOR] & SPEED_MASK) >> SPEED_OFFSET;
		
		if(speed == 0)
		{
			comStruct->rear_motors[MOTOR_ARG].direction = MOTOR_REAR_STOP;
			comStruct->rear_motors[MOTOR_ARG].speed = speed;
		}
		else
		{
			switch (dir) {
				case 0: //forward 
					comStruct->rear_motors[MOTOR_ARD].direction = MOTOR_REAR_FORWARD;
					comStruct->rear_motors[MOTOR_ARD].speed = speed;
				break;
				case 1: // backward
					comStruct->rear_motors[MOTOR_ARD].direction = MOTOR_REAR_BACKWARD;
					comStruct->rear_motors[MOTOR_ARD].speed = speed;
				break;
				default:
					comStruct->rear_motors[MOTOR_ARD].direction = MOTOR_REAR_STOP;
					comStruct->rear_motors[MOTOR_ARD].speed = 0;
			}
		}
}

void write_spiFrame(uint8_t* spiFrame, Communication_Typedef comStruct)
{
	
	// Motor values equals 0
	spiFrame[DIRECTION_MOTOR] = 0;
	spiFrame[RIGHT_WHEEL_MOTOR] = 0;
	spiFrame[LEFT_WHEEL_MOTOR] = 0;
	spiFrame[LEFT_WHEEL_MOTOR_DISTANCE] = (int8_t)comStruct.rear_motors[MOTOR_ARD].distance;
	spiFrame[RIGHT_WHEEL_MOTOR_DISTANCE] = (int8_t)comStruct.rear_motors[MOTOR_ARG].distance;

	// Sensors values 
	spiFrame[FRONT_LEFT_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_AVG].distance;
	spiFrame[FRONT_RIGHT_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_AVD].distance;
	spiFrame[FRONT_CENTER_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_AVC].distance;
	spiFrame[REAR_LEFT_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_ARG].distance;
	spiFrame[REAR_RIGHT_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_ARD].distance;
	spiFrame[REAR_CENTER_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_ARC].distance;

	// Battery
	spiFrame[BATTERY] = (int8_t)comStruct.battery.state;
	
}





