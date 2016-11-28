#include <stdint.h>
#include <stdlib.h>
/*#include "motor_front.h"
#include "motor_rear.h"*/
#include "SPI_functions.h"
#include "drivers_car_config.h"
#include "manage_motors.h"

// Initialization of the reception and send buffers
volatile uint8_t sendBuffer[BUFFER_SIZE] = {0}; 
volatile uint8_t receiveBuffer[BUFFER_SIZE] = {0};
volatile Communication_Typedef receivedFrame;
Communication_Typedef * p_receivedFrame = (Communication_Typedef *)&receivedFrame;

int main()
{
	// Init SPI communication
	InitializeSPI2((uint8_t *)receiveBuffer, (uint8_t *)sendBuffer);
	// Init all the rest
	services_init();
	
	/* ------------------------------------------------------------- */
	/*																															 */
	/*  Creation of a structure to test the stm-raspi communication  */
	/*																															 */
	/* ------------------------------------------------------------- */
	
	init_spiFrame(p_receivedFrame); //initialize the structure 
	// Set random value to the structure for the test
			// Sensors values 
	int i = 0;
	for(i = 0; i < 6 ; i++) 
		receivedFrame.ultrasounds[i].distance = 80+i;

			// Battery value
	receivedFrame.battery.state = 86;
	while(1){}
}
