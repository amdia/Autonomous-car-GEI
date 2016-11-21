#include <stdint.h>
#include <stdlib.h>
#include "hall_sensor.h"
#include "drivers_car_config.h"
#include "motor_front.h"
#include "motor_rear.h"

__IO Direction front = STOP;
__IO int rear = 0;

__IO float distance = 0;

static int front_hall[HALL_NB/2]={0};
static int rear_hall[HALL_NB/2]={0};
float rear_distance[HALL_NB/2] = {0};

void travelled_distance(Hall_Position pos);

int main(void) {
	services_init();
  
	while(1){
		// control rear motors
		if ((rear == 1)||(distance > 0.0)) {
			enableRearMotor();
			commandRearMotor(30);
		} else if ((rear == 2)||(distance < 0.0)) {
			enableRearMotor();
			commandRearMotor(-30);
		} else {
			disableRearMotor();
		}
		
		// control front motor
		if ((front == 1) && (getFrontDirection() != LEFT)) {
			enableFrontMotor();
			commandFrontMotor(LEFT);
		} else if ((front == 2) && (getFrontDirection() != RIGHT)) {
			enableFrontMotor();
			commandFrontMotor(RIGHT);
		}
		else {
			disableFrontMotor();
		}
	}
  return 0;
}

void travelled_distance(Hall_Position pos){
	if(pos == HALL_AVG || pos == HALL_AVD){
		front_hall[(int)pos]++;
	} else {
		rear_hall[(int)pos-2]++;	// -2 pour ARG et ARD
		rear_distance[(int)pos-2] = WHEEL_PERIMETER * ((float)rear_hall[(int)pos-2]) / WHEEL_PULSES_NB;
		if(rear_distance[(int)pos-2] > abs(distance)){
			rear = STOP;
			distance = 0;
			rear_distance[(int)pos-2] = 0;
			rear_hall[(int)pos-2] = 0;
		}
	}
}

// ------------------------------------------ //
// ------------- Callbacks-------- ---------- //
// ------------------------------------------ //

void hall_callback(Hall_Position pos){
	travelled_distance(pos);
	if(pos == HALL_AVG || pos == HALL_AVD){
		disableFrontMotor();
		setFrontDirection((Direction)front);
		front = STOP;
	}
}

void scheduler_IT_callback(){
}
