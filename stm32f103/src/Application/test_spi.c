#include <stdint.h>
#include <stdlib.h>
#include "motor_front.h"
#include "motor_rear.h"
#include "SPI_functions.h"
#include "drivers_car_config.h"
#include "manage_motors.h"

int no_action;
/* 
*		Une liste chainée est crée (initialisé dans SPI_function.c)
*		Cette liste contient l'enchainement des actions à faire 
*
*		Un booléen global : no_action permet de savoir si une action est en cours ou non 
*
*		Dès qu'une action est terminé, le programme doit appeler la fonction présente dans spi_test.h
* 				void detectEndAction(void)
*		La fonction va défiler la liste et mettre le booléen no_action à vrai 		
*
*		Dans le main, on a une boucle while(1),
*				si une action est en cours ou aucune action est en attente
* 						on fait rien 
*				si aucune action est en cours et une action est en attente
*							on met à jour les valeurs de distance et d'angle 			
*			
*/

int main()
{
	
	// Initialization of the reception and send buffers
	unsigned char sendBuffer[BUFFER_SIZE] = {0}; 
	unsigned char receiveBuffer[BUFFER_SIZE] = {0};
	// Init SPI communication
	InitializeSPI2(receiveBuffer, sendBuffer);
	// Init all the rest
	services_init();
	
	/* ------------------------------------------------------------- */
	/*																															 */
	/*  Creation of a structure to test the stm-raspi communication  */
	/*																															 */
	/* ------------------------------------------------------------- */
	Communication_Typedef receivedFrame;
	init_spiFrame(&receivedFrame); //initialize the structure 
	// Set random value to the structure for the test
			// Sensors values 
	receivedFrame.frontLeftUltrasound.distance = 80;
	receivedFrame.frontRightUltrasound.distance = 81;
	receivedFrame.frontCenterUltrasound.distance = 82;
	receivedFrame.rearLeftUltrasound.distance = 83;
	receivedFrame.rearRightUltrasound.distance = 84;
	receivedFrame.rearCenterUltrasound.distance = 85;
			// Battery value
	receivedFrame.battery.state = 86;
	
	while(1)
	{
		read_spiFrame(receiveBuffer); // Read the Frame 
		write_spiFrame(sendBuffer); // Write the Frame 
		if(no_action == 1 && actionList != NULL)
		{
			// TODO: Mettre a jours les variables distances et angles 
			//dist = 
			// angl = 
			front = receivedFrame.directionMotor.direction;
			rear = 
			distance = receivedFrame.wheelMotor.distance;
		/*	__IO float distance = 0;
__IO int motor_speed = 50;
__IO int command_angle = ANGLE_INIT;*/
			
			extern __IO Direction front;
			extern __IO int rear;
			extern __IO float distance;
			no_action = 0;
		}
			
	}
}


// Detect the end of the both action (distance and angle) 
void detectEndAction(void)
{
	del_action();
	no_action = 1;
}
