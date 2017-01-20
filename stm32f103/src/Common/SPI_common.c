#include "SPI_common.h"

/* Shared variables ----------------------------------------------------------*/

/**
* @brief Buffer to send SPI frame - shared variable between @ref SPI_functions.c and @ref SPI_services.c
*/
volatile uint8_t sendBuffer[BUFFER_SIZE]; 
/**
* @brief Buffer to receive SPI frame - shared variable between @ref SPI_functions.c and @ref SPI_services.c
*/
volatile uint8_t receiveBuffer[BUFFER_SIZE];
