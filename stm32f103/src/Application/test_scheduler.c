#include <stdint.h>
#include <stm32f10x_gpio.h>
#include "services_config.h"
#include "scheduler_timer_init.h"

__IO int front = 0;
__IO int rear = 0;
int c = 0;

void init_all(void);
void GPIO_init(void);

int main(void) {
	init_all();
	while(1){}
	
  return 0;
}

void init_all(void){
	initServices();
	GPIO_init();
	
	scheduler_timer_init();
}


void scheduler_IT_callback(){
	if( (c % 3) == 0 )
		GPIO_WriteBit(GPIOD, GPIO_Pin_5, Bit_SET);
	else if( (c % 3) == 1)
		GPIO_WriteBit(GPIOD, GPIO_Pin_5, Bit_RESET);
	else {}
	c++;
}

void GPIO_init(void){
	 GPIO_InitTypeDef gpioStructure;
    gpioStructure.GPIO_Pin = GPIO_Pin_5;
    gpioStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpioStructure);
}

