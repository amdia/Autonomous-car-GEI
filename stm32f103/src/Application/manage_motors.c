#include <stdint.h>
#include <stdlib.h>
#include "motor_front.h"
#include "motor_rear.h"
#include "manage_motors.h"

volatile Direction front = STOP;
volatile int rear = 0;

volatile float distance = 0;

static int vitesse = 30;

static int front_hall[HALL_NB/2]={0};
static int rear_hall[HALL_NB/2]={0};
float rear_distance[HALL_NB/2] = {0};

void motors_control(void){
		if ((rear == 1)||(distance > 0.0)) {
			enableRearMotor();
			commandRearMotor(vitesse);
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
