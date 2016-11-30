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
	... | BATTERY ||

*/

// Mask and offset for the motors
#define DIRECTION_MASK 128 // 1000 000
#define DIRECTION_OFFSET 7
#define SPEED_MASK 127 // 0111 1111
#define SPEED_OFFSET 0
#define ANGLE_MASK 127 // 0111 1111
#define ANGLE_OFFSET 0


typedef struct
{
	uint8_t direction_motor;
	uint8_t left_wheel_motor;
	uint8_t right_wheel_motor; 
	uint8_t left_wheel_motor_distance; 
	uint8_t right_wheel_motor_distance;
	uint8_t front_left_ultrasonic;
	uint8_t front_right_ultrasonic;
	uint8_t front_center_ultrasonic;
	uint8_t rear_left_ultrasonic;
	uint8_t rear_right_ultrasonic;
	uint8_t rear_center_ultrasonic;
	uint8_t battery;
}OctetsFrame_Typedef;


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

extern volatile Communication_Typedef receivedFrame;

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
void read_spiFrame(Communication_Typedef* comStruct);

/** 
 *	\brief Write the frame to send according to the communication structure
 *	\param spiFrame : The frame to send	
 * 	\param comStruct: The communication structure
 *	\return None
*/
void write_spiFrame(Communication_Typedef comStruct);


#endif //SPIC_SERVICES_H
