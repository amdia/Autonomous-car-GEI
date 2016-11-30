#include "SPI_functions.h"

#include <stm32f10x.h>
#include "gpio.h"
#include "NVIC_priorities.h"
	
void InitializeSPI2(uint8_t * receiveBuffer, uint8_t * sendBuffer, int buffer_size)
{
	/***** GPIO *****/
			
	// Configure used pins for GPIOB
	GPIO_init(GPIOB, GPIO_Pin_14, GPIO_Mode_AF_PP); //MISO
	GPIO_init(GPIOB, GPIO_Pin_13, GPIO_Mode_IN_FLOATING); //SCK
	GPIO_init(GPIOB, GPIO_Pin_15, GPIO_Mode_IN_FLOATING); //MOSI
		
	/***** SPI_Slave_and_DMA_Configuration *****/

	SPI_InitTypeDef SPI_InitStructure; //Variable used to setup the SPI
	DMA_InitTypeDef DMA_InitStructure; //Variable used to setup the DMA


	//== SPI2 configuration
	SPI_StructInit(&SPI_InitStructure);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	SPI_InitStructure.SPI_CRCPolynomial = 0;
	SPI_Init(SPI2, &SPI_InitStructure);

	//NVIC
	//Enable DMA1 channel IRQ Channel 
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = SPI_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	 
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	NVIC_Init(&NVIC_InitStructure);

	//--Enable DMA1 clock--
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	//==Configure DMA1 - Channel4== (SPI -> memory)
	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(SPI2_BASE+0x0C); //Address of peripheral the DMA must map to
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)receiveBuffer; //Variable to which received data will be stored
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = buffer_size; //Buffer size
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4, &DMA_InitStructure); //Initialise the DMA  

	//==Configure DMA1 - Channel5== (memory -> SPI)
	DMA_StructInit(&DMA_InitStructure);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(SPI2_BASE+0x0C); //Address of peripheral the DMA must map to
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sendBuffer; //Variable from which data will be transmitted
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = buffer_size; //Buffer size
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5, &DMA_InitStructure); //Initialise the DMA     


	// Enable the SPI2 RX & TX DMA requests
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx, ENABLE);

	/* Enable DMA interrupts */
	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
	DMA_ITConfig(DMA1_Channel5, DMA_IT_TE, ENABLE);

	DMA_Cmd(DMA1_Channel4, ENABLE); //Enable the DMA1 - Channel4       
	DMA_Cmd(DMA1_Channel5, ENABLE); //Enable the DMA1 - Channel5  

	// Enable SPI2
	SPI_Cmd(SPI2, ENABLE);  
}
