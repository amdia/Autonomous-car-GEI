/**
* @file main.c
* @brief Application layer. Only initialize the services. Everything is handle in callbacks_services.c
*/
#include <stdint.h>
#include <stdlib.h>
#include "services_config.h"

/**
* @brief Initialize the services and while(1).
*/
int main()
{	
	// Init services
	services_init();

	while(1){}
}
