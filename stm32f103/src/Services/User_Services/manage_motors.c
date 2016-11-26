#include <stdint.h>
#include <stdlib.h>
#include "motor_front.h"
#include "motor_rear.h"
#include "manage_motors.h"
#include "time_systick.h"

//__IO Direction front = STOP;
//__IO int rear = 0;
__IO float distance = 0;
__IO int motor_speed = 50;
__IO int command_angle = ANGLE_INIT;

int on_stop = 0;
int start_motor = 0;
int stop_motor = 0;
int travelling = 0;

int speeds[4]={40,38,35,30};
float thresholds[4]={0.25,0.5,0.75,1};
float time_to_turn = 0;

int64_t eps = 0;
int K = 3000; 

float rear_distance[HALL_NB] = {0};
uint64_t speed_rear_motors[HALL_NB] ={0};

static int64_t proportional_controller(int64_t eps);
//int64_t int PI_controller(int64_t eps);

void rear_motors_control(void){
		if ((start_motor == 1)&&(distance > 0.0)) {
			motor_rear_set_state(MOTOR_ARD, MOTOR_STATE_ON);
			motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_ON);
			motor_rear_command(MOTOR_ARG, motor_speed);
			motor_rear_command(MOTOR_ARD, motor_speed);
			start_motor = 0;
		} else if ((start_motor == 1)&&(distance < 0.0)) {
			motor_rear_set_state(MOTOR_ARD, MOTOR_STATE_ON);
			motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_ON);
			motor_rear_command(MOTOR_ARG, -motor_speed);
			start_motor = 0;
		} else if(stop_motor == 1){
			motor_rear_command(MOTOR_ARG, 0);
			motor_rear_command(MOTOR_ARD, 0);
			motor_rear_set_state(MOTOR_ARD, MOTOR_STATE_OFF);
			motor_rear_set_state(MOTOR_ARG, MOTOR_STATE_OFF);
			stop_motor = 0;
		}
}

//void control_angle_front_motor(int command_angle){
void control_angle_front_motor(){
	static int actual_angle = ANGLE_INIT;
	static uint64_t t_temp = 0;
	int diff_angle = 0;
	Direction dir = STOP;
	int speed = 0;
	float speed_motor = 0.0;
	int threshold = 0;
	if(command_angle > ANGLE_LEFT_MAX)
		command_angle = ANGLE_LEFT_MAX;
	if(command_angle < ANGLE_RIGHT_MAX)
		command_angle = ANGLE_RIGHT_MAX;
	if(command_angle != actual_angle){
		if(command_angle == ANGLE_LEFT_MAX && !on_stop){ //turn to the maximum angle on the left
			enableFrontMotor();
			commandFrontMotor(LEFT, FRONT_MOTOR_SPEED);
			actual_angle = ANGLE_LEFT_MAX;
		}else if(command_angle == ANGLE_RIGHT_MAX && !on_stop){ //turn to the maximum angle on the right
			enableFrontMotor();
			commandFrontMotor(RIGHT, FRONT_MOTOR_SPEED);
			actual_angle = ANGLE_RIGHT_MAX;
		}else { //turn during a certain time to the left, to reach the command_angle
			on_stop = 0;
			diff_angle = command_angle - actual_angle;
			
			// look for threshold where the diff_angle belongs
			int found = 0;
			int i = 0;
			while(!found){
				if(abs(diff_angle)<=thresholds[i]*(float)ANGLE_RANGE){
					found = 1;
					threshold = i;
					speed = speeds[i];
				}
				i++;					
			}
			
			//set direction to turn
			dir = (diff_angle > 0) ? LEFT : RIGHT;
			//set speed to turn
			speed_motor = (diff_angle > 0) ? FRONT_MOTOR_SPEED_R2L : FRONT_MOTOR_SPEED_L2R;
			
			// set the time to turn
			if(threshold == 0)
				time_to_turn = (uint64_t)(abs((float)diff_angle) / speed_motor);
			else
				time_to_turn = (uint64_t) ( (abs((float)diff_angle) / speed_motor) + ((float)speeds[threshold-1]/(float)speeds[threshold] - 1.0) * thresholds[threshold] * (float)ANGLE_RANGE / speed_motor); 
			
			//set motor parameters
			enableFrontMotor();
			commandFrontMotor(dir, speed);
			
			t_temp = micros();
			while(micros() - t_temp <=  time_to_turn){}
			disableFrontMotor();
			actual_angle = command_angle;
			}
		command_angle = actual_angle;
	}	
	
}

void distance_to_travel(/*int dist*/){
	if(travelling == 0){
		start_motor = 1;
		//distance = dist;
		travelling = 1;
	}
}

void calculate_distance(Hall_Position pos){
	static int rear_hall[HALL_NB]={0};
//	float rear_distance[HALL_NB] = {0};
	if(pos == HALL_ARG || pos == HALL_ARD){
		rear_hall[pos]++;
		rear_distance[pos] = WHEEL_PERIMETER * ((float)rear_hall[pos]) / WHEEL_PULSES_NB;
		if(rear_distance[HALL_ARG] > abs(distance)){
			stop_motor = 1;
			distance = 0;
			travelling = 0;
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
		//setFrontDirection((Direction)front);
		on_stop = 1;
		//front = STOP;
	}
}

void measure_rear_motor_speed(Hall_Position pos){
	static uint64_t t_last_pulse[HALL_NB] = {0};
	
	if(pos == HALL_ARG || pos == HALL_ARD){
		speed_rear_motors[pos] = micros() - t_last_pulse[pos];
		t_last_pulse[pos] = micros();
			/*
		if(pos == HALL_ARG){
			toto1 = speed[pos];
		} else if (pos == HALL_ARD){
			toto2 = speed[pos];
		}*/
	}
	//return speed[pos];
}

void motor_rear_right_slaving(void){
	//int64_t eps = 0;
	int motor_corrected_speed = 0; 
	eps = speed_rear_motors[HALL_ARG] - speed_rear_motors[HALL_ARD];
	motor_corrected_speed = proportional_controller(eps);
	if(distance > 0){
		motor_rear_command(MOTOR_ARD, motor_corrected_speed);
	} else if(distance < 0){
		motor_rear_command(MOTOR_ARD, -motor_corrected_speed);
	}
	
}

int64_t proportional_controller(int64_t eps){
	//static const int K = 3000; // 50 OK
	int64_t cmd = 0;
	cmd = K * eps; // test cmd en valeur absolue
	return cmd;
}

//int PI_controller(uint64_t eps){
//	static const int K = 3000;
//	static const int Ki = 5;
//	static int sum_eps = 0;
//	int cmd = 0;
//	sum_eps = sum_eps + eps;
//	cmd = Ki * sum_eps +  K * eps;
//	return cmd;
//}
