#ifndef __SPI_COMMON_H
#define __SPI_COMMON_H

#include <stdint.h>
#include "SPI_services.h"

#define BUFFER_SIZE (sizeof(OctetsFrame_Typedef))

extern volatile int8_t sendBuffer[BUFFER_SIZE]; 
extern volatile int8_t receiveBuffer[BUFFER_SIZE];

#endif //__SPI_COMMON_H
