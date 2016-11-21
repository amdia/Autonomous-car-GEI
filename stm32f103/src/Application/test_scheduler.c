#include <stdint.h>
#include <stm32f10x_gpio.h>
#include "drivers_car_config.h"
#include "scheduler_timer_init.h"

int c = 0;


int main(void) {
	services_init();
	while(1){}
	
  return 0;
}


void scheduler_IT_callback(){
	if( (c % 3) == 0 )
		GPIO_WriteBit(GPIOD, GPIO_Pin_5, Bit_SET);
	else if( (c % 3) == 1)
		GPIO_WriteBit(GPIOD, GPIO_Pin_5, Bit_RESET);
	else {}
	c++;
}


