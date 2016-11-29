#include <stdint.h>
#include <stm32f10x_gpio.h>
#include "callbacks_services.h"
#include "motor_rear.h"
#include "scheduler_timer_init.h"
#include "manage_motors.h"
#include "SPI_services.h"
#include "us_sensor.h"
#include "time_systick.h"

#define IS_TASK(task) (scheduler_counter % task == 0)

static uint64_t scheduler_counter = 0;

void hall_callback(Hall_Position pos){
	if(pos == HALL_ARG || pos == HALL_ARD)
		receivedFrame.rear_motors[pos].distance = calculate_distance(pos)[pos];
	if(pos == HALL_AVG || pos == HALL_AVD)
		motor_front_stop(pos);
}
int i[6] = {0};
//ordre du tableau dans receivedFrame ARG, ARC, AVC, AVD, AVG
void ultrasonic_callback(Ultrasonic_Position pos) {
	i[pos]++;
	receivedFrame.ultrasounds[pos].distance = i[pos];
	receivedFrame.ultrasounds[pos].distance = ultrasonic_get_distance(pos);
}

int first = 1;
void scheduler_IT_callback(){
	/*MotorRear_Typedef test[2];
	test[0].distance = 0;
	test[0].direction = MOTOR_REAR_FORWARD;
	test[0].speed = 50;
	test[1].distance = 0;
	test[1].direction = MOTOR_REAR_FORWARD;
	test[1].speed = 50;*/

	if(IS_TASK(TASK_SPI)){
		read_spiFrame((uint8_t *)receiveBuffer, (Communication_Typedef *)&receivedFrame); // Read the Frame 
		write_spiFrame((uint8_t *)sendBuffer, receivedFrame); // Write the Frame 
	}
	
	if (IS_TASK(TASK_MOTOR)){
		control_angle_front_motor(receivedFrame.directionMotor.angle);
		rear_motors_control((MotorRear_Typedef *)&receivedFrame.rear_motors);
	/*if(first == 1)
		rear_motors_control((MotorRear_Typedef *)&test);
	first = 0;
		delay_micros(4e6);
		test[1].direction = MOTOR_REAR_BACKWARD;
	test[0].direction = MOTOR_REAR_BACKWARD;
	rear_motors_control((MotorRear_Typedef *)&test);*/
	}
	
	if (IS_TASK(TASK_ULTRASONIC_TRIGGER)) {
     ultrasonic_trig_all();
	}
	
	scheduler_counter++;
}
