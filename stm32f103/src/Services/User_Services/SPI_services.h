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
	uint8_t ack_byte;
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
 * \struct Ack_Typedef
 * \brief Structure that contains informations about the ack byte 
 */
typedef struct
{
	int reset_distance; /*!< Distance reset demand of the raspi */
	int ack_distance; /*!< Ack response for the distance */
}Ack_Typedef;


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
	
	Ack_Typedef ack_byte;
	
}Communication_Typedef;

typedef struct motorAction
{
    Communication_Typedef action;
    struct motorAction *nxt;
}motorAction;

extern volatile Communication_Typedef receivedFrame;

/** 
 *	\brief Initialize the communication structure
 *	\return None
 */
void init_spiFrame(void);

/** 
 *	\brief Read the frame received and update the communication structure
 *	\return None
*/
void read_spiFrame(void);

/** 
 *	\brief Write the frame to send according to the communication structure
 *	\return None
*/
void write_spiFrame(void);


#endif //SPIC_SERVICES_H
