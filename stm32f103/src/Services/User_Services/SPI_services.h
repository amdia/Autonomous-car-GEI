#ifndef __SPI_SERVICES_H
#define __SPI_SERVICES_H

#include <stdint.h>
#include "SPI_functions.h"

extern volatile uint8_t sendBuffer[BUFFER_SIZE]; 
extern volatile uint8_t receiveBuffer[BUFFER_SIZE];
extern volatile Communication_Typedef receivedFrame;

#endif // __SPI_SERVICES_H
