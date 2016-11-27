#include <stdint.h>
#include <stm32f10x_gpio.h>
#include "callbacks_services.h"
#include "motor_rear.h"
#include "scheduler_timer_init.h"
#include "manage_motors.h"
#include "SPI_services.h"

#define IS_TASK(task) (scheduler_counter % task == 0)

static uint64_t scheduler_counter = 0;

void hall_callback(Hall_Position pos){
	if(pos == HALL_ARG || pos == HALL_ARD){
		receivedFrame.wheelMotor.distance = calculate_distance(pos);
	}
	if(pos == HALL_AVG || pos == HALL_AVD)
		motor_front_stop(pos);
}

void scheduler_IT_callback(){
	if(IS_TASK(TASK_SPI)){
		read_spiFrame((uint8_t *)receiveBuffer, (Communication_Typedef *)&receivedFrame); // Read the Frame 
		write_spiFrame((uint8_t *)sendBuffer, receivedFrame); // Write the Frame 
	}
	
	if (IS_TASK(TASK_MOTOR)){
		//distance_to_travel();
		control_angle_front_motor(receivedFrame.directionMotor.angle);
		rear_motors_control(receivedFrame.wheelMotor);
	}
	
	if (IS_TASK(TASK_ULTRASONIC_TRIGGER)) {
    // do shits here idk...
	}
	
	scheduler_counter++;
}
