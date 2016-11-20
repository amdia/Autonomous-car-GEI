#include <stdint.h>
#include <stm32f10x_gpio.h>
#include "hall_sensor.h"
#include "scheduler_timer_init.h"
#include "motor_front.h"
#include "motor_rear.h"
#include "manage_motors.h"

int c = 0;

void hall_callback(Hall_Position pos){
	travelled_distance(pos);
	if(pos == HALL_AVG || pos == HALL_AVD){
		disableFrontMotor();
		setFrontDirection((Direction)front);
		front = STOP;
	}
}

void scheduler_IT_callback(){
	motors_control();
	if(c % 3 == 0)
		GPIO_WriteBit(GPIOD, GPIO_Pin_5, Bit_SET);        // WTF is this!?
	else if(c % 3 == 1)
		GPIO_WriteBit(GPIOD, GPIO_Pin_5, Bit_RESET);      // WTF is that!?
	else {}
	c++;
}
