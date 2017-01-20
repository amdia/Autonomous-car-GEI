/**
* @file services_config.c
* @brief Service layer for the initialization of all the drivers
*/

#include "services_config.h"
#include "clocks.h"
#include "time_systick.h"
#include "SPI_functions.h"
#include "SPI_services.h"
#include "drivers_car_config.h"
#include "scheduler_timer_init.h" 

/**
* @brief Initialization of the clocks, the NVIC priority setting, the systick, the car drivers, the SPI and the scheduler
*/
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
	communicationFrame.battery.state = 50; //random value, battery is not implemented

	//init scheduler
	scheduler_timer_init();
}
