#ifndef __SPI_SERVICES_H
#define __SPI_SERVICES_H

#include <stdint.h>
#include "motor_common.h"
#include "sensors_common.h"

/* 
	Format of the frame :
	
	|| DIRECTION_MOTOR | LEFT_WHEEL_MOTOR | RIGHT_WHEEL_MOTOR | ...
	... | LEFT_WHEEL_MOTOR_DISTANCE | RIGHT_WHEEL_MOTOR_DISTANCE | ...
	... | FRONT_LEFT_ULTRASOUND | FRONT_RIGHT_ULTRASOUND | FRONT_CENTER_ULTRASOUND | ...
	... | REAR_LEFT_ULTRASOUND | REAR_RIGHT_ULTRASOUND | REAR_CENTER_ULTRASOUND | ...
	... | BATTERY | ACK_BYTE ||

*/


/**
* @brief Structure that contains the frame sent and received from the SPI buffer. Every element is a char (uint8_t).
*/
typedef struct
{
	uint8_t direction_motor;
	uint8_t left_wheel_motor;
	uint8_t right_wheel_motor; 
	uint8_t average_wheel_motor_distance0; 
	uint8_t average_wheel_motor_distance1;
	uint8_t average_wheel_motor_distance2;
	uint8_t average_wheel_motor_distance3;
	uint8_t front_left_ultrasonic;
	uint8_t front_right_ultrasonic;
	uint8_t front_center_ultrasonic;
	uint8_t rear_left_ultrasonic;
	uint8_t rear_right_ultrasonic;
	uint8_t rear_center_ultrasonic;
	uint8_t battery;
	uint8_t ack_byte;
}OctetsFrame_Typedef;


/**
* @brief Structure that contains informations about the ultrasounds
*/
typedef struct
{
	/** Distance of the closest obstacle in cm */
	int distance; 
}Ultrasound_Typedef;

/**
* @brief Structure that contains informations about the battery
*/
typedef struct 
{
	/** State of the battery in % */
	int state; 
}Battery_Typedef;


/**
* @brief Structure that contains informations about the ack byte 
*/
typedef struct
{
	/** Distance reset demand of the raspi */
	int reset_distance; 
	/** Ack response for the distance */
	int ack_distance; 
}Ack_Typedef;


/**
* @brief Structure that contains all the informations of the car
*/
typedef struct 
{
	/** Contains the information about the front motor (angle) */
	MotorFront_Typedef directionMotor;
	/** Contains the information about the rear motors (speed and travelled distance) */
	MotorRear_Typedef rear_motors[REAR_MOTORS_NB];
	/** Contains the information about the ultrasonic sensors (distance) */
	Ultrasound_Typedef ultrasounds[ULTRASONIC_NB];
	/** Contains the information about the battery (state) */
	Battery_Typedef battery;	
	/** Contains the information about the ack_byte (reset_distance and ack_distance) */
	Ack_Typedef ack_byte;
	
}Communication_Typedef;

extern volatile Communication_Typedef communicationFrame;

void init_spiFrame(void);

void read_spiFrame(void);

void write_spiFrame(void);

#endif //SPIC_SERVICES_H
