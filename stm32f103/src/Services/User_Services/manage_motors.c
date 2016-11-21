#include <stdint.h>
#include <stdlib.h>
#include "motor_front.h"
#include "motor_rear.h"
#include "manage_motors.h"
#include "time_systick.h"

__IO Direction front = STOP;
__IO int rear = 0;
__IO float distance = 0;

static int motor_speed = 30;

static int front_hall[HALL_FRONT_NB]={0};
static int rear_hall[HALL_REAR_NB]={0};
float rear_distance[HALL_REAR_NB] = {0};

static uint16_t speed[HALL_REAR_NB] ={0};

static int proportional_controller(uint16_t eps);
static int PI_controller(uint16_t eps);

void motors_control(void){
		if ((rear == 1)||(distance > 0.0)) {
			motor_rear_set_state(MOTOR_ARD, MOTOR_STATE_ON);
			motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_ON);
			motor_rear_command(MOTOR_ARG, motor_speed);
			//motor_rear_command(MOTOR_ARD, motor_speed);
		} else if ((rear == 2)||(distance < 0.0)) {
			motor_rear_set_state(MOTOR_ARD, MOTOR_STATE_ON);
			motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_ON);
			motor_rear_command(MOTOR_ARG, -motor_speed);
			//motor_rear_command(MOTOR_ARD, -motor_speed);
		} else {
			motor_rear_set_state(MOTOR_ARD, MOTOR_STATE_OFF);
			motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_OFF);
		}
		
		// control front motor
		if ((front == 1) && (getFrontDirection() != LEFT)) {
			enableFrontMotor();
			commandFrontMotor(LEFT);
		} else if ((front == 2) && (getFrontDirection() != RIGHT)) {
			enableFrontMotor();
			commandFrontMotor(RIGHT);
		} else {
			disableFrontMotor();
		}
}


void distance_to_travel(Hall_Position pos){
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

void motor_front_stop(Hall_Position pos){
	if(pos == HALL_AVG || pos == HALL_AVD){
		disableFrontMotor();
		setFrontDirection((Direction)front);
		front = STOP;
	}
}

int get_rear_motor_speed(Hall_Position pos){
	static uint64_t t_last_pulse[HALL_REAR_NB] = {0};
	if(pos == HALL_ARG || pos == HALL_ARD){
		speed[pos] = micros() - t_last_pulse[pos];
		t_last_pulse[pos] = micros();
	}
	return speed[pos];
}

void motor_rear_right_slaving(void){
	static uint16_t eps = 0;
	int motor_corrected_speed = 0;
	eps = speed[MOTOR_ARG] - speed[MOTOR_ARD];
	motor_corrected_speed = proportional_controller(eps);
	motor_rear_command(MOTOR_ARD, motor_corrected_speed);
}

int proportional_controller(uint16_t eps){
	static const int K = 200; //à tester
	int cmd = 0;
	cmd = K * eps;
	return cmd;
}

int PI_controller(uint16_t eps){
	static const int K = 0;
	static const int Ki = 0;
	static int sum_eps = 0;
	int cmd = 0;
	sum_eps = sum_eps + eps;
	cmd = Ki * sum_eps +  K * eps;
	return cmd;
}

