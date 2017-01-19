#ifndef __SPI_COMMON_H
#define __SPI_COMMON_H

#include <stdint.h>
#include "SPI_services.h"

#define BUFFER_SIZE 13//(sizeof(OctetsFrame_Typedef))

extern volatile uint8_t sendBuffer[BUFFER_SIZE]; 
extern volatile uint8_t receiveBuffer[BUFFER_SIZE];

#endif //__SPI_COMMON_H
