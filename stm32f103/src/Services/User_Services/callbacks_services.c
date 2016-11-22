#include <stdint.h>
#include <stm32f10x_gpio.h>
#include "callbacks_services.h"
#include "motor_rear.h"
#include "scheduler_timer_init.h"
#include "manage_motors.h"

#define IS_TASK(task) (scheduler_counter % task == 0)

static uint64_t scheduler_counter = 0;

void hall_callback(Hall_Position pos){
	if(pos == HALL_ARG || pos == HALL_ARD){
		distance_to_travel(pos);
		motor_rear_speed(pos);
	}
	if(pos == HALL_AVG || pos == HALL_AVD)
		motor_front_stop(pos);
}

void scheduler_IT_callback(){
  if (IS_TASK(TASK_MOTOR)) {
    motors_control();
    motor_rear_right_slaving();
  }
  if (IS_TASK(TASK_ULTRASONIC_TRIGGER)) {
    // do shits here idk...
  }
	scheduler_counter++;
}