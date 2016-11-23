#ifndef __SPI_FUNCTIONS_H
#define __SPI_FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

/* 
	Format of the frame :
	
	|| DIRECTION_MOTOR | LEFT_WHEEL_MOTOR | RIGHT_WHEEL_MOTOR | ...
	... | FRONT_LEFT_ULTRASOUND | FRONT_RIGHT_ULTRASOUND | FRONT_CENTER_ULTRASOUND | ...
	... | REAR_LEFT_ULTRASOUND | REAR_RIGHT_ULTRASOUND | REAR_CENTER_ULTRASOUND | ...
	... | BATTERY ||

*/

// 	Number of the octet 
#define DIRECTION_MOTOR 0
#define LEFT_WHEEL_MOTOR 1
#define RIGHT_WHEEL_MOTOR 2
#define FRONT_LEFT_ULTRASOUND 3
#define FRONT_RIGHT_ULTRASOUND 4 
#define FRONT_CENTER_ULTRASOUND 5
#define REAR_LEFT_ULTRASOUND 6
#define REAR_RIGHT_ULTRASOUND 7 
#define REAR_CENTER_ULTRASOUND 8
#define BATTERY 9

// Mask and offset for the motors
#define DIRECTION_MASK 192 // 1100 000
#define DIRECTION_OFFSET 6
#define SPEED_MASK 63 // 0011 1111
#define SPEED_OFFSET 0
	
/**
 * \struct Motor_Typedef
 * \brief Structure that contains informations for the motors
 */
typedef struct
{
	int direction; /*!< Direction of the motor */
	int speed; /*!< Speed of the motor in % */
}Motor_Typedef;

/**
 * \struct Ultrasound_Typedef
 * \brief Structure that contains informations about the ultrasounds
 */
typedef struct
{
	int distance; /*!< Distance of the closest obstacle in cm */
}Ultrasound_Typedef;

/**
 * \struct Battery_Typedef
 * \brief Structure that contains informations about the battery
 */
typedef struct 
{
	int state; /*!< State of the battery in %*/
}Battery_Typedef;

/**
 * \struct Communication_Typedef
 * \brief Structure that contains all the informations of the car
 */
typedef struct 
{
	Motor_Typedef directionMotor;
	Motor_Typedef leftWheelMotor;
	Motor_Typedef rightWheelMotor;
	
	Ultrasound_Typedef frontLeftUltrasound;
	Ultrasound_Typedef frontRightUltrasound;
	Ultrasound_Typedef frontCenterUltrasound;
	Ultrasound_Typedef rearLeftUltrasound;
	Ultrasound_Typedef rearRightUltrasound;
	Ultrasound_Typedef rearCenterUltrasound;

	Battery_Typedef battery;	
}Communication_Typedef;

/** 
 *	\brief Initialize the communication structure
 *	\param comStruct: The structure to initialize
 *	\return None
 */
void init_spiFrame(Communication_Typedef *comStruct);

/** 
 *	\brief Read the frame received and update the communication structure
 *	\param spiFrame : The frame received	
 * 	\param comStruct: The structure to update
 *	\return None
*/
void read_spiFrame(unsigned char* spiFrame, Communication_Typedef* comStruct);

/** 
 *	\brief Write the frame to send according to the communication structure
 *	\param spiFrame : The frame to send	
 * 	\param comStruct: The communication structure
 *	\return None
*/
void write_spiFrame(unsigned char* spiFrame, Communication_Typedef comStruct);

void InitializeSPI2(unsigned char * receiveBuffer, unsigned char * sendBuffer);


#endif
