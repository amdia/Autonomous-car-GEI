#include <stdint.h>
#include <stdlib.h>
#include "motor_front.h"
#include "motor_rear.h"
#include "manage_motors.h"
#include "time_systick.h"

__IO Direction front = STOP;
__IO int rear = 0;
__IO float distance = 0;

static int motor_speed = 50;
int command_angle = 0;

//static uint16_t eps = 0; // test

// test capteurs hall
int all_hall[HALL_NB] = {0};

uint64_t toto1 = 0;
uint64_t toto2 = 0;

static int front_hall[HALL_FRONT_NB]={0};
static int rear_hall[HALL_NB]={0};
float rear_distance[HALL_NB] = {0};

uint64_t speed[HALL_REAR_NB] ={0};

static int proportional_controller(uint64_t eps);
static int PI_controller(uint64_t eps);

void motors_control(void){
		if ((rear == 1)||(distance > 0.0)) {
	//if (rear == 1) {
			motor_rear_set_state(MOTOR_ARD, MOTOR_STATE_ON);
			motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_ON);
			motor_rear_command(MOTOR_ARG, motor_speed); // test regulation sur ARG
			//motor_rear_command(MOTOR_ARD, motor_speed); // commente pour regulation
		} else if ((rear == 2)||(distance < 0.0)) {
		//} else if (rear == 2) {
			motor_rear_set_state(MOTOR_ARD, MOTOR_STATE_ON);
			motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_ON);
			motor_rear_command(MOTOR_ARG, -motor_speed); // test regulation sur ARG
			motor_rear_command(MOTOR_ARD, -motor_speed); // commente pour regulation
		} else {
			motor_rear_command(MOTOR_ARG, 0);
			motor_rear_command(MOTOR_ARD, 0);
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

void control_angle_front_motor(/*int command_angle*/){
	static int actual_angle = 0;
	uint64_t t_temp = 0;
	int diff_angle = 0;
	if(command_angle >= ANGLE_LEFT_MAX){ //turn to the maximum angle on the left
		enableFrontMotor();
		commandFrontMotor(LEFT);
		actual_angle = ANGLE_LEFT_MAX;
	}else if(command_angle <= ANGLE_RIGHT_MAX){ //turn to the maximum angle on the right
		enableFrontMotor();
		commandFrontMotor(RIGHT);
		actual_angle = ANGLE_RIGHT_MAX;
	}else if(command_angle > actual_angle){ //turn during a certain time to the left, to reach the command_angle
		diff_angle = command_angle - actual_angle;
		enableFrontMotor();
		commandFrontMotor(LEFT);
		t_temp = micros();
		while(micros() - t_temp <  diff_angle / SPEED_RIGHT_2_LEFT_FRONT_MOTOR_DEGREE_PER_MILLIS){}
		commandFrontMotor(STOP);
		actual_angle = command_angle;
	}else if(command_angle < actual_angle){ //turn during a certain time to the right, to reach the command_angle
		diff_angle = actual_angle - command_angle;
		enableFrontMotor();
		commandFrontMotor(RIGHT);
		t_temp = micros();
		while(micros() - t_temp <  diff_angle / SPEED_LEFT_2_RIGHT_FRONT_MOTOR_DEGREE_PER_MILLIS){}
		commandFrontMotor(STOP);
		actual_angle = command_angle;
	}
	
}


void distance_to_travel(Hall_Position pos){
	if(pos == HALL_AVG || pos == HALL_AVD){
		front_hall[(int)pos]++;
	} else {
		rear_hall[(int)pos]++;	// -2 pour ARG et ARD
		//rear_distance[(int)pos-2] = WHEEL_PERIMETER * ((float)rear_hall[(int)pos-2]) / WHEEL_PULSES_NB;
		rear_distance[(int)pos] = WHEEL_PERIMETER * ((float)rear_hall[(int)pos]) / WHEEL_PULSES_NB;
		if(rear_distance[HALL_ARG] > abs(distance)){
			/*
			if(rear != STOP){
				rear = STOP;
			}
			*/
			distance = 0;
			rear_distance[HALL_ARG] = 0;
			rear_distance[HALL_ARD] = 0;
			rear_hall[HALL_ARD] = 0;
			rear_hall[HALL_ARG] = 0;
			
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

uint64_t get_rear_motor_speed(Hall_Position pos){
	static uint64_t t_last_pulse[HALL_REAR_NB] = {0};
	if(pos == HALL_ARG || pos == HALL_ARD){
		speed[pos] = micros() - t_last_pulse[pos];
		if(pos == HALL_ARG){
			toto1 = speed[pos];
		} else if (pos == HALL_ARD){
			toto2 = speed[pos];
		}
		t_last_pulse[pos] = micros();
	}
	return speed[pos];
}

void motor_rear_right_slaving(void){
	static uint64_t eps = 0;
	int motor_corrected_speed = 0;
	//eps = speed[MOTOR_ARG] - speed[MOTOR_ARD];
	eps = toto1 - toto2;
	//eps = speed[MOTOR_ARD] - speed[MOTOR_ARG];
	motor_corrected_speed = proportional_controller(eps);
	//motor_corrected_speed = PI_controller(eps);
	//motor_rear_command(MOTOR_ARD, motor_corrected_speed);
	//motor_rear_command(MOTOR_ARD, motor_speed);
	//motor_rear_command(MOTOR_ARG, motor_corrected_speed);
}

int proportional_controller(uint64_t eps){
	static const int K = 3000; //à tester
	int cmd = 0;
	cmd = K * eps;
	return cmd;
}

int PI_controller(uint64_t eps){
	static const int K = 3000;
	static const int Ki = 5;
	static int sum_eps = 0;
	int cmd = 0;
	sum_eps = sum_eps + eps;
	cmd = Ki * sum_eps +  K * eps;
	return cmd;
}

// test count pulse hall
void count_pulse(Hall_Position pos){
	all_hall[(int)pos]++;
}
