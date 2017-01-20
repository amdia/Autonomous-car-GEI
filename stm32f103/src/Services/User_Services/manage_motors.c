/**
* @file manage_motors.c
* @brief Sercice layer for the front and rear motors
*/
#include "manage_motors.h"
#include <stdint.h>
#include <stdlib.h>
#include "motor_front.h"
#include "motor_rear.h"
#include "motor_common.h"
#include "time_systick.h"

/* Private variables ---------------------------------------------------------*/

/** 
* @brief 1 if the front motor has been stopped by the hall sensor, 0 else
*/
int on_stop = 0;
/** 
* @brief Array of the 4 possible speed for the front motor. 
*/
int speeds[4]={40,38,35,30};
/** 
* @brief Array of the 4 thresholds for the front motor. Ex : 0.25 means the diff_angle is 25 % of the maximal angle range
*/
float thresholds[4]={0.25,0.5,0.75,1};
/** 
* @brief Array of the counter of hall sensor interruptions of each wheel
*/
static int rear_hall[REAR_MOTORS_NB]={0};

/********************************/
/*       Public Functions       */
/********************************/

/** 
* @brief Rear motor controls : receive a speed and execute it. The two wheels can receive a different command.
* @param motor_rear_control[] Array of #MotorRear_Typedef, one for the right motor and the other one for the left motor.
*/
void rear_motors_control(MotorRear_Typedef motor_rear_control[]){
	
	// Check if the command of the speed is different from 0. Different from 0 means the motor needs to be turned on.
	// So we check if the left motor is already ON or not. 
	// If it is already, it's not necessary to turn it on again.
	if(motor_rear_control[REAR_MOTOR_LEFT].speed != 0 && \
		get_motor_rear_state(REAR_MOTOR_LEFT) == MOTOR_STATE_OFF )
		motor_rear_set_state(REAR_MOTOR_LEFT, MOTOR_STATE_ON);
	
	// Check if the command of the speed is different from 0. Different from 0 means the motor needs to be turned on.
	// So we check if the right motor is already ON or not. 
	// If it is already, it's not necessary to turn it on again.
	if(motor_rear_control[REAR_MOTOR_RIGHT].speed != 0 && \
		get_motor_rear_state(REAR_MOTOR_RIGHT) == MOTOR_STATE_OFF )
		motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_ON);
	
	// Left motor
	// Check if the command of the speed is different from the actual speed. 
	// If the speed is the same, there is no need to give the order again.
	// If the speed is different, we give the new speed to the motor.
	// If the speed is 0, it means that the motor needs to be disabled.
	if(motor_rear_control[REAR_MOTOR_LEFT].speed != get_motor_rear_speed(REAR_MOTOR_LEFT)){
		motor_rear_command(REAR_MOTOR_LEFT, motor_rear_control[REAR_MOTOR_LEFT].speed);
		if(motor_rear_control[REAR_MOTOR_RIGHT].speed == 0)
			motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_OFF);
	}
	
	// Right motor
	// Check if the command of the speed is different from the actual speed. 
	// If the speed is the same, there is no need to give the order again.
	// If the speed is different, we give the new speed to the motor.
	// If the speed is 0, it means that the motor needs to be disabled.
	if(motor_rear_control[REAR_MOTOR_RIGHT].speed != get_motor_rear_speed(REAR_MOTOR_RIGHT)){
		motor_rear_command(REAR_MOTOR_RIGHT, motor_rear_control[REAR_MOTOR_RIGHT].speed);
		if(motor_rear_control[REAR_MOTOR_RIGHT].speed == 0)
			motor_rear_set_state(REAR_MOTOR_RIGHT, MOTOR_STATE_OFF);
	}
	
}

/** 
* @brief Receive an angle command and turn a certain time to reach this angle
* @param angle Angle the car has to turn
*/
void control_angle_front_motor(int angle){
	// Actual angle, in the ANGLE_RANGE
	static int actual_angle = ANGLE_INIT;
	// Actual command angle
	static int actual_command_angle = ANGLE_INIT;
	// Time to which the car has to stop to turn
	static uint64_t t_temp = 0;
	// Time during which the car has to turn
	uint64_t time_to_turn = 0;
	// Difference between the angle command and the actual angle
	int diff_angle = 0;
	// Speed to which the car has to turn
	int speed = 0;
	// Speed of the motor in degrees / microseconds, is different for the right and the left motor
	float speed_motor = 0.0;
	// Threshold for a given angle command
	int threshold = 0;
	// Angle command
	int command_angle = 0;
	
	command_angle = angle;
	
	// Saturation of the angle
	if(command_angle > ANGLE_LEFT_MAX)
		command_angle = ANGLE_LEFT_MAX;
	if(command_angle < ANGLE_RIGHT_MAX)
		command_angle = ANGLE_RIGHT_MAX;
	
	// If the wanted angle is different from the previous one
	if(command_angle != actual_command_angle){
		
		// Turn to the maximum angle on the left, is stop by the front stop interruption
		if(command_angle == ANGLE_LEFT_MAX && !on_stop){ 
			enableFrontMotor();
			commandFrontMotor(FRONT_MOTOR_SPEED);
			// Max value of uint64
			t_temp = (uint64_t)(-1);
		}
		
		// Turn to the maximum angle on the right, is stop by the front stop interruption
		else if(command_angle == ANGLE_RIGHT_MAX && !on_stop){ 
			enableFrontMotor();
			commandFrontMotor(FRONT_MOTOR_SPEED);
			// Max value of uint64
			t_temp = (uint64_t)(-1);
		}
		
		// Turn during a certain time to the left, to reach the command_angle
		else { 
			on_stop = 0;
			diff_angle = command_angle - actual_angle;
			
			// Look for threshold to which the diff_angle belongs
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
			
			speed_motor = (diff_angle > 0) ? FRONT_MOTOR_SPEED_R2L : FRONT_MOTOR_SPEED_L2R;
			
			// Set the time to turn according to the speed_motor and the speed
			if(threshold == 0)
				time_to_turn = (uint64_t)(abs((float)diff_angle) / speed_motor);
			else
				time_to_turn = (uint64_t) ((abs((float)diff_angle) / speed_motor) + ((float)speeds[threshold-1]/(float)speeds[threshold] - 1.0) * thresholds[threshold] * (float)ANGLE_RANGE / speed_motor); 
			
			if(diff_angle<0){speed = -speed;}
			
			enableFrontMotor();
			commandFrontMotor(speed);
			t_temp = micros()+time_to_turn;
			// The bloc below has to be uncommented if commands of angle have to be given everytime there is a new order to give
			// (So not in the scheduler where the function is called all the time)
			// Has to be used just for tests because there shouldn't be a blocking while in a function.
			// While micros < t_temp, we wait
			/*
			while(micros() <=  t_temp){}
 			disableFrontMotor();
				actual_angle = command_angle;
			*/
		}
		actual_command_angle = command_angle;
	}	

	// The bloc has to be commented if commands of angle have to be given outside everytime there is a new order to give
	// (So not in the scheduler where the function is called all the time)
	// When it is time to stop or when a front stop is reached, the motor is disabled.
	if(micros() > t_temp || on_stop){
		disableFrontMotor();
		actual_angle = command_angle;
	}
}

/** 
* @brief Reset the interruption hall counters to 0.
*/
void reset_distance(void){
	int i;
	for(i=0; i<REAR_MOTORS_NB; i++){
		rear_hall[i] = 0;
	}
}

/** 
* @brief Return the travelled distance according to the number of hall sensors interruptions.
* @retval Travelled distance in centimeters
*/
float calculate_distance(Hall_Position pos){
	float rear_distance;
	if(pos == HALL_REAR_LEFT || pos == HALL_REAR_RIGHT){
		rear_hall[pos-2]++;
		rear_distance = WHEEL_PERIMETER * ((float)rear_hall[pos-2]) / WHEEL_PULSES_NB;
	}
	return rear_distance;
}

/** 
* @brief Disable the front motor when a front stop is reached.
*/
void motor_front_stop(Hall_Position pos){
	if(pos == HALL_FRONT_LEFT || pos == HALL_FRONT_RIGHT){
		disableFrontMotor();
		on_stop = 1;
	}
}

