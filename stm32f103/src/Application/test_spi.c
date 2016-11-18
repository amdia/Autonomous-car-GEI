#include "SPI_functions.h"
#include <string.h>

int main()
{
	unsigned char sendBuffer[BUFFER_SIZE];
	unsigned char receiveBuffer[BUFFER_SIZE];
	
	char send[BUFFER_SIZE] = "a";
	char receive[BUFFER_SIZE] = "b";
	
	memcpy(sendBuffer, send, BUFFER_SIZE);
	memcpy(receiveBuffer, receive, BUFFER_SIZE);	
	
	/*< Init SPI communication. */
	InitializeSPI2(receiveBuffer, sendBuffer);
	
	while(1){}
	}
