#ifndef __SPI_COMMON_H
#define __SPI_COMMON_H

#include <stdint.h>
#include "SPI_services.h"

/** Size of the sending and receiving buffers, equal to the size of the OctetsFrame_Typedef */
#define BUFFER_SIZE (sizeof(OctetsFrame_Typedef))

extern volatile uint8_t sendBuffer[BUFFER_SIZE]; 
extern volatile uint8_t receiveBuffer[BUFFER_SIZE];

#endif //__SPI_COMMON_H
