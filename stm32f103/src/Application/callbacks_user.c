#include <stdint.h>
#include <stm32f10x_gpio.h>
#include "hall_sensor.h"
#include "scheduler_timer_init.h"
#include "motor_front.h"
#include "motor_rear.h"
#include "manage_motors.h"

#define IS_TASK(task) (scheduler_counter % task == 0)

static uint64_t scheduler_counter = 0;

void hall_callback(Hall_Position pos){
	update_traveled_distance(pos);
	if(pos == HALL_AVG || pos == HALL_AVD){
		disableFrontMotor();
		setFrontDirection((Direction)front);
		front = STOP;
	}
}

void scheduler_IT_callback(){
  scheduler_counter++;
  if (IS_TASK(TASK_MOTOR_CONTROL)) {
    motors_control();
  }
  if (IS_TASK(TASK_ULTRASONIC_TRIGGER)) {
    // do shits
  }
}
