#include "drivers_car_config.h"

#include "time_systick.h"
#include "hall_sensor.h"
#include "us_sensor.h"
#include "gpio.h"
#include "motor_front.h"
#include "motor_rear.h"
#include "scheduler_timer_init.h" 

void services_init(void) {
  // Enable all GPIO ports
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

  // Enable all timers
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  // Enable alternate functions
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  // Config systick to 1us
  systick_init();
  
  // Config Hall and Ultrasonic sensors
	init_hall_sensors();
	init_ultrasonic_sensors();
	// config motors
	initFrontMotor();
	motors_rear_init();
	
	//init GPIOD pin 5 for tests
//	init_GPIO();
	
	//init scheduler
	scheduler_timer_init();
}
