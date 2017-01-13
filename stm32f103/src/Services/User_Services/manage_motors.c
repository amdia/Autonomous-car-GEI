#include "manage_motors.h"
#include <stdint.h>
#include <stdlib.h>
#include "motor_front.h"
#include "motor_rear.h"
#include "motor_common.h"
#include "time_systick.h"

int on_stop = 0;

int speeds[4]={40,38,35,30};
float thresholds[4]={0.25,0.5,0.75,1};
float rear_distance[REAR_MOTORS_NB] = {0};

void rear_motors_control(MotorRear_Typedef motor_rear_control[]){
	
	// Two wheels
	if(motor_rear_control[REAR_MOTOR_LEFT].speed != 0 && \
		get_motor_rear_state(REAR_MOTOR_LEFT) == MOTOR_STATE_OFF )
		motor_rear_set_state(REAR_MOTOR_LEFT, MOTOR_STATE_ON);
	
	if(motor_rear_control[REAR_MOTOR_RIGHT].speed != 0 && \
		get_motor_rear_state(REAR_MOTOR_RIGHT) == MOTOR_STATE_OFF )
		motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_ON);
	
	if(motor_rear_control[REAR_MOTOR_LEFT].speed != get_motor_rear_speed(REAR_MOTOR_LEFT)){
		motor_rear_command(REAR_MOTOR_LEFT, motor_rear_control[REAR_MOTOR_LEFT].speed);
		if(motor_rear_control[REAR_MOTOR_RIGHT].speed == 0)
			motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_OFF);
	}
	
	if(motor_rear_control[REAR_MOTOR_RIGHT].speed != get_motor_rear_speed(REAR_MOTOR_RIGHT)){
		motor_rear_command(REAR_MOTOR_RIGHT, motor_rear_control[REAR_MOTOR_RIGHT].speed);
		if(motor_rear_control[REAR_MOTOR_RIGHT].speed == 0)
			motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_OFF);
	}
	
}
int speed = 0;
void control_angle_front_motor(int angle){ // fonction non-testé avec le if(micros > t_time+t_turn), fonction validée avec while. A debug avec le if si ne fonctionne pas du premier coup
	static int actual_angle = ANGLE_INIT;
	static int actual_command_angle = ANGLE_INIT;
	static uint64_t t_temp = 0;
	uint64_t time_to_turn = 0;
	int diff_angle = 0;
	//int speed = 0;
	float speed_motor = 0.0;
	int threshold = 0;
	int command_angle = 0;
	
	command_angle = angle;
	
	if(command_angle > ANGLE_LEFT_MAX)
		command_angle = ANGLE_LEFT_MAX;
	if(command_angle < ANGLE_RIGHT_MAX)
		command_angle = ANGLE_RIGHT_MAX;
	
	if(command_angle != actual_command_angle){
		if(command_angle == ANGLE_LEFT_MAX && !on_stop){ //turn to the maximum angle on the left
			enableFrontMotor();
			commandFrontMotor(FRONT_MOTOR_SPEED);
			actual_angle = command_angle;
			t_temp = (uint64_t)(-1);
		}else if(command_angle == ANGLE_RIGHT_MAX && !on_stop){ //turn to the maximum angle on the right
			enableFrontMotor();
			commandFrontMotor(-FRONT_MOTOR_SPEED);
			actual_angle = command_angle;
			t_temp = (uint64_t)(-1);
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
			
			//set speed to turn
			speed_motor = (diff_angle > 0) ? FRONT_MOTOR_SPEED_R2L : FRONT_MOTOR_SPEED_L2R;
			
			// set the time to turn
			if(threshold == 0)
				time_to_turn = (uint64_t)(abs((float)diff_angle) / speed_motor);
			else
				time_to_turn = (uint64_t) ((abs((float)diff_angle) / speed_motor) + ((float)speeds[threshold-1]/(float)speeds[threshold] - 1.0) * thresholds[threshold] * (float)ANGLE_RANGE / speed_motor); 
			
			//set motor parameters
			enableFrontMotor();
			if(diff_angle<0){speed = -speed;}
			commandFrontMotor(speed);
			
			/* pour remplacer le bloc if(micros() > t_temp || on_stop) si utilisation de la fonction de controle
			dans le main, sans le scheduler*/
			t_temp = micros() + time_to_turn;	
			while(micros() <=  t_temp){}
				disableFrontMotor();
				actual_angle = command_angle;
			}
			/*fin du bloc*/
		}
		actual_command_angle = command_angle;
		//actual_angle = command_angle;
	}	

//	if(micros() > t_temp || on_stop){
//		disableFrontMotor();
//		actual_angle = command_angle;
//	}
//}

float* calculate_distance(Hall_Position pos){
	static int rear_hall[REAR_MOTORS_NB]={0};
	if(pos == HALL_REAR_LEFT || pos == HALL_REAR_RIGHT){
		rear_hall[pos-2]++;
		rear_distance[pos-2] = WHEEL_PERIMETER * ((float)rear_hall[pos-2]) / WHEEL_PULSES_NB;
	}
	return rear_distance;
}

void motor_front_stop(Hall_Position pos){
	if(pos == HALL_FRONT_LEFT || pos == HALL_FRONT_RIGHT){
		disableFrontMotor();
		on_stop = 1;
	}
}

