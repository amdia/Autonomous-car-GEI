
#include "services_config.h"
#include "motor_front.h"
#include "motor_rear.h"
#include "hall_sensor.h"

__IO int front = 0;
__IO int rear = 0;

int main(void) {
  initServices();
  initFrontMotor();
  initRearMotor();
	Hall_Config();
  while(1) {
    // control front motor
    if (front == 1) {
      enableFrontMotor();
      commandFrontMotor(LEFT);
    } else if (front == 2) {
      commandFrontMotor(RIGHT);
      enableFrontMotor();
    } else if (front == 3) enableFrontMotor();
    else if (front == 4) disableFrontMotor();
    else commandFrontMotor(STOP);
    
    // control rear motors
    if (rear == 1) {
      enableRearMotor();
      commandRearMotor(70);
    } else if (rear == 2) {
      enableRearMotor();
      commandRearMotor(-70);
    } else {
      disableRearMotor();
    }
  }
}

void Hall_AVG_Callback(void) {
  commandFrontMotor(STOP);
  disableFrontMotor();
}
void Hall_AVD_Callback(void) {
  commandFrontMotor(STOP);
  disableFrontMotor();
}