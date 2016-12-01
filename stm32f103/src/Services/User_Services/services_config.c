#include "services_config.h"
#include "clocks.h"
#include "time_systick.h"
#include "SPI_functions.h"
#include "SPI_services.h"
#include "drivers_car_config.h"
#include "scheduler_timer_init.h" 


void services_init(void){
	clocks_init();

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	// Config systick to 1us
	systick_init();	
	
	drivers_car_init();
	
	// Init SPI communication
	InitializeSPI2();
	
	// Initialize the structure 
	init_spiFrame();
	receivedFrame.battery.state = 50;

	//init scheduler
	scheduler_timer_init();
}
