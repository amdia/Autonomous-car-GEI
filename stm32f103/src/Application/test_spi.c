#include <stdint.h>
#include <stdlib.h>

#include "SPI_functions.h"
#include "drivers_car_config.h"
#include "manage_motors.h"
#include "us_sensor.h"
#include "SPI_services.h"

int main()
{
	// Init SPI communication
	InitializeSPI2((uint8_t *)receiveBuffer, (uint8_t *)sendBuffer, BUFFER_SIZE);
	
	// Init all the rest
	services_init();
	
	// Initialize the structure 
	Communication_Typedef * p_receivedFrame = (Communication_Typedef *)&receivedFrame;
	init_spiFrame(p_receivedFrame); 
	
	/* ------------------------------------------------------------- */
	/*																															 */
	/*  Creation of a structure to test the stm-raspi communication  */
	/*																															 */
	/* ------------------------------------------------------------- */	
	// Set random value to the structure for the test
			// Sensors values 
	receivedFrame.ultrasounds[ULTRASONIC_ARG].distance = 80;
	receivedFrame.ultrasounds[ULTRASONIC_ARC].distance = 81;
	receivedFrame.ultrasounds[ULTRASONIC_AVC].distance = 82;
	receivedFrame.ultrasounds[ULTRASONIC_AVD].distance = 83;
	receivedFrame.ultrasounds[ULTRASONIC_AVG].distance = 84;
	receivedFrame.ultrasounds[ULTRASONIC_ARD].distance = 85;
			// Battery value
	receivedFrame.battery.state = 86;

	while(1){}
}
