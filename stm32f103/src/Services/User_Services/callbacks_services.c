/**
* @file callbacks_services.c
* @brief Sercice layer for the callback handling
*/
#include "callbacks_services.h"
#include <stdint.h>
#include "scheduler_timer_init.h"
#include "manage_motors.h"
#include "SPI_services.h"
#include "us_sensor.h"

/* Private macro -------------------------------------------------------------*/

/**
* @brief Task = x. The scheduler_counter is incremented every microseconds. A given task is done every x microseconds.
*/
#define IS_TASK(task) (scheduler_counter % task == 0)

/* Private variables ---------------------------------------------------------*/

/**
* @brief Count the timer interruptions.
*/
static uint64_t scheduler_counter = 0;

/********************************/
/*       Public Functions       */
/********************************/

/**
* @brief Called every hall sensor interruptions. Handle the front stop hall sensors and the rear hall sensors (odometry)
*/
void hall_callback(Hall_Position pos){
	if(pos == HALL_REAR_LEFT || pos == HALL_REAR_RIGHT)
		// The travelled distance is written is the frame, to be sent via the SPI.
		// rear_motors[] is a 2 elements array but the Hall_Position type has 4 values, so we do pos-2
		communicationFrame.rear_motors[pos-2].distance = calculate_distance(pos);
	if(pos == HALL_FRONT_LEFT || pos == HALL_FRONT_RIGHT)
		// When one of the front stop hall sensor detect one of the magnet, the front motor is stopped.
		motor_front_stop(pos);
}

/**
* @brief Called every ultrasonic interruptions. The distance returned by the ultrasonic sensor is written is the communication frame to be sent via the SPI
*/
void ultrasonic_callback(Ultrasonic_Position pos) {
	communicationFrame.ultrasounds[pos].distance = ultrasonic_get_distance(pos);
}

/**
* @brief Called every timer interruptions
*/
void scheduler_IT_callback(){
	// If it is time for the TASK_SPI to express itself
	if(IS_TASK(TASK_SPI)){
		// Read the spi frame in the buffer and write the values in the communicationFrame 
		read_spiFrame();
		
		if(communicationFrame.ack_byte.reset_distance==1){
			reset_distance();
			communicationFrame.ack_byte.ack_distance = 1;
		}
		else{
			communicationFrame.ack_byte.ack_distance = 0;
		}
		// Read the values in the communicationFrame and write it in the spi buffer 
		write_spiFrame(); 
	}
	
	// If it is time for the TASK_MOTOR to express itself
	if (IS_TASK(TASK_MOTOR)){
		control_angle_front_motor(communicationFrame.directionMotor.angle);
		rear_motors_control((MotorRear_Typedef *)&communicationFrame.rear_motors);
	}
	
	// If it is time for the TASK_ULTRASONIC_TRIGGER to express itself
	if (IS_TASK(TASK_ULTRASONIC_TRIGGER)) {
     ultrasonic_trig_all();
	}
	
	scheduler_counter++;
}
