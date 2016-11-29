#ifndef __SPI_FUNCTIONS_H
#define __SPI_FUNCTIONS_H

#include <stdint.h>

/** 
 *	\brief Initialize the SPI communication
 *	\param receiveBuffer : The Buffer that contains the receive frame 
 * 	\param sendBuffer : The Buffer that contains the send frame 
 *	\param bufferSize : The size of the buffer
 *	\return None
*/
void InitializeSPI2(uint8_t * receiveBuffer, uint8_t * sendBuffer, int buffer_size);

#endif

