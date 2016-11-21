#include "manage_motors.h"

void motor_front_stop(Hall_Position pos){
	if(pos == HALL_AVG || pos == HALL_AVD){
		disableFrontMotor();
		setFrontDirection((Direction)front);
		front = STOP;
	}
}