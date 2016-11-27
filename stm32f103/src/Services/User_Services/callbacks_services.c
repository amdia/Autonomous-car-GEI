#include <stdint.h>
#include <stm32f10x_gpio.h>
#include "callbacks_services.h"
#include "motor_rear.h"
#include "scheduler_timer_init.h"
#include "manage_motors.h"
#include "us_sensor.h"

#define IS_TASK(task) (scheduler_counter % task == 0)

// shared global variable to stock distances measured by the ultrasonic sensors 
float distances_cm[ULTRASONIC_NB]={0};

static uint64_t scheduler_counter = 0;

void hall_callback(Hall_Position pos){
	//count_pulse(pos);
	if(pos == HALL_ARG || pos == HALL_ARD){
		calculate_distance(pos);
		measure_rear_motor_speed(pos);
	}
	if(pos == HALL_AVG || pos == HALL_AVD)
		motor_front_stop(pos);
}

void ultrasonic_callback(Ultrasonic_Position pos) {
  distances_cm[pos] = ultrasonic_get_distance(pos);
}

void scheduler_IT_callback(){
	distance_to_travel();
	control_angle_front_motor();
	if (IS_TASK(TASK_MOTOR)){
		rear_motors_control();
		//motor_rear_right_slaving();
  }
  if (IS_TASK(TASK_ULTRASONIC_TRIGGER)) {
    ultrasonic_trig_all();
  }
	scheduler_counter++;
}
