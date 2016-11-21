#ifndef _MOTOR_FRONT_H_
#define _MOTOR_FRONT_H_

#include "motor_control.h"
#include "drivers_car_config.h"

typedef enum {
  STOP,
  LEFT,
  RIGHT
} Direction;

void initFrontMotor(void);
void commandFrontMotor(Direction direction);
void enableFrontMotor(void);
void disableFrontMotor(void);
Direction getFrontDirection(void);
void setFrontDirection(Direction direction);

#endif // _MOTOR_FRONT_H_
