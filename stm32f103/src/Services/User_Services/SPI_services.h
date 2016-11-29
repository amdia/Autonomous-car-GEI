#ifndef __SPI_SERVICES_H
#define __SPI_SERVICES_H

#include "motor_front.h"

#define BUFFER_SIZE 12

/* 
	Format of the frame :
	
	|| DIRECTION_MOTOR | LEFT_WHEEL_MOTOR | RIGHT_WHEEL_MOTOR | ...
	... | LEFT_WHEEL_MOTOR_DISTANCE | RIGHT_WHEEL_MOTOR_DISTANCE | ...
	... | FRONT_LEFT_ULTRASOUND | FRONT_RIGHT_ULTRASOUND | FRONT_CENTER_ULTRASOUND | ...
	... | REAR_LEFT_ULTRASOUND | REAR_RIGHT_ULTRASOUND | REAR_CENTER_ULTRASOUND | ...
	... | BATTERY ||

*/

// 	Number of the octet 
#define DIRECTION_MOTOR 0
#define LEFT_WHEEL_MOTOR 1
#define RIGHT_WHEEL_MOTOR 2
#define LEFT_WHEEL_MOTOR_DISTANCE 3
#define RIGHT_WHEEL_MOTOR_DISTANCE 4
#define FRONT_LEFT_ULTRASOUND 5
#define FRONT_RIGHT_ULTRASOUND 6 
#define FRONT_CENTER_ULTRASOUND 7
#define REAR_LEFT_ULTRASOUND 8
#define REAR_RIGHT_ULTRASOUND 9 
#define REAR_CENTER_ULTRASOUND 10
#define BATTERY 11

// Mask and offset for the motors
#define DIRECTION_MASK 128 // 1000 000
#define DIRECTION_OFFSET 7
#define SPEED_MASK 127 // 0111 1111
#define SPEED_OFFSET 0
#define ANGLE_MASK 127 // 0111 1111
#define ANGLE_OFFSET 0	

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
	int distance; /*!< Distance travelled */
}MotorRear_Typedef;

/**
 * \struct MotorFront_Typedef
 * \brief Structure that contains informations for the front motor
 */
typedef struct
{
	Direction direction; /*!< Direction of the motor */
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
	MotorFront_Typedef directionMotor;
	MotorRear_Typedef rear_motors[REAR_MOTORS_NB];
	
	Ultrasound_Typedef ultrasounds[ULTRASONIC_NB];

	Battery_Typedef battery;	
}Communication_Typedef;

typedef struct motorAction
{
    Communication_Typedef action;
    struct motorAction *nxt;
}motorAction;




extern __IO uint8_t sendBuffer[BUFFER_SIZE]; 
extern __IO uint8_t receiveBuffer[BUFFER_SIZE];
extern __IO Communication_Typedef receivedFrame;



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
void read_spiFrame(uint8_t* spiFrame, Communication_Typedef* comStruct);

/** 
 *	\brief Write the frame to send according to the communication structure
 *	\param spiFrame : The frame to send	
 * 	\param comStruct: The communication structure
 *	\return None
*/
void write_spiFrame(uint8_t* spiFrame, Communication_Typedef comStruct);


#endif
