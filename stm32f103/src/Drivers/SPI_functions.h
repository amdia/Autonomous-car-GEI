#ifndef __SPI_FUNCTIONS_H
#define __SPI_FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "motor_front.h"

#define BUFFER_SIZE 10

/* 
	Format of the frame :
	
	|| DIRECTION_MOTOR | DIRECTION_MOTOR_ANGLE | WHEEL_MOTOR | WHEEL_MOTOR_DISTANCE | ...
	... | FRONT_LEFT_ULTRASOUND | FRONT_RIGHT_ULTRASOUND | FRONT_CENTER_ULTRASOUND | ...
	... | REAR_LEFT_ULTRASOUND | REAR_RIGHT_ULTRASOUND | REAR_CENTER_ULTRASOUND | ...
	... | BATTERY | ACTION_NUMBER ||

*/

// 	Number of the octet 
#define DIRECTION_MOTOR 0
#define DIRECTION_MOTOR_ANGLE 1
#define WHEEL_MOTOR 2
#define WHEEL_MOTOR_DISTANCE 3
#define FRONT_LEFT_ULTRASOUND 4
#define FRONT_RIGHT_ULTRASOUND 5 
#define FRONT_CENTER_ULTRASOUND 6
#define REAR_LEFT_ULTRASOUND 7
#define REAR_RIGHT_ULTRASOUND 8 
#define REAR_CENTER_ULTRASOUND 9
#define BATTERY 10
#define ACTION_NUMBER 11

// Mask and offset for the motors
#define DIRECTION_MASK 192 // 1100 000
#define DIRECTION_OFFSET 6
#define SPEED_MASK 63 // 0011 1111
#define SPEED_OFFSET 0
	

typedef enum {
	MOTOR_REAR_STOP,
  MOTOR_REAR_FORWARD,
  MOTOR_REAR_BACKWARD
} MotorRearDirection;

/**
 * \struct MotorRear_Typedef
 * \brief Structure that contains informations for the rear motors
 */
typedef struct
{
	MotorRearDirection direction; /*!< Direction of the motor */
	int speed; /*!< Speed of the motor in % */
	int distance; /*!< Distance to travel */
}MotorRear_Typedef;

/**
 * \struct MotorFront_Typedef
 * \brief Structure that contains informations for the front motor
 */
typedef struct
{
	Direction direction; /*!< Direction of the motor */
	int speed; /*!< Speed of the motor in % */
	int angle; /*!< Angle to turn */
}MotorFront_Typedef;


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
	int actionNumber; 
	
	MotorFront_Typedef directionMotor;
	MotorRear_Typedef wheelMotor;
	
	Ultrasound_Typedef frontLeftUltrasound;
	Ultrasound_Typedef frontRightUltrasound;
	Ultrasound_Typedef frontCenterUltrasound;
	Ultrasound_Typedef rearLeftUltrasound;
	Ultrasound_Typedef rearRightUltrasound;
	Ultrasound_Typedef rearCenterUltrasound;

	Battery_Typedef battery;	
}Communication_Typedef;

typedef struct motorAction
{
    Communication_Typedef action;
    struct motorAction *nxt;
}motorAction;


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
void read_spiFrame(unsigned char* spiFrame);

/** 
 *	\brief Write the frame to send according to the communication structure
 *	\param spiFrame : The frame to send	
 * 	\param comStruct: The communication structure
 *	\return None
*/
void write_spiFrame(unsigned char* spiFrame);

/** 
 *	\brief Initialize the SPI communication
 *	\param receiveBuffer : The Buffer that contains the receive frame 
 * 	\param sendBuffer : The Buffer that contains the send frame 
 *	\return None
*/
void InitializeSPI2(unsigned char * receiveBuffer, unsigned char * sendBuffer);


void add_action(Communication_Typedef action);
void del_action(void);

extern __IO motorAction* actionList;

#endif

