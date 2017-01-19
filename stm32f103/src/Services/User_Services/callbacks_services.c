#include "callbacks_services.h"
#include <stdint.h>
#include "scheduler_timer_init.h"
#include "manage_motors.h"
#include "SPI_services.h"
#include "us_sensor.h"

#define IS_TASK(task) (scheduler_counter % task == 0)
int test_angle = 0;
static uint64_t scheduler_counter = 0;

void hall_callback(Hall_Position pos){
	if(pos == HALL_REAR_LEFT || pos == HALL_REAR_RIGHT)
		receivedFrame.rear_motors[pos-2].distance = calculate_distance(pos)[pos-2];
	if(pos == HALL_FRONT_LEFT || pos == HALL_FRONT_RIGHT)
		motor_front_stop(pos);
}

void ultrasonic_callback(Ultrasonic_Position pos) {
	receivedFrame.ultrasounds[pos].distance = ultrasonic_get_distance(pos);
}

void scheduler_IT_callback(){
	if(IS_TASK(TASK_SPI)){
		read_spiFrame(); // Read the Frame 
		
		if(receivedFrame.ack_byte.reset_distance==1){
			reset_distance();
			receivedFrame.ack_byte.ack_distance = 1;
		}
		else{
			receivedFrame.ack_byte.ack_distance = 0;
		}
		
		write_spiFrame(); // Write the Frame 
	}
	
	if (IS_TASK(TASK_MOTOR)){
		test_angle = receivedFrame.directionMotor.angle;
		control_angle_front_motor(receivedFrame.directionMotor.angle);
		rear_motors_control((MotorRear_Typedef *)&receivedFrame.rear_motors);
	}
	
	if (IS_TASK(TASK_ULTRASONIC_TRIGGER)) {
     ultrasonic_trig_all();
	}
	
	scheduler_counter++;
}
