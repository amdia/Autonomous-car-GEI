#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "misc.h"
#include "SPI_functions.h"


void InitializeSPI2(unsigned char * receiveBuffer, unsigned char * sendBuffer)
{
	/***** GPIO *****/
		// Enable clock for GPIOB
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
		// Configure used pins for GPIOB
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14; //MISO
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15 | GPIO_Pin_13; //CS SCK MOSI
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		/***** SPI_Slave_and_DMA_Configuration *****/
	
		SPI_InitTypeDef SPI_InitStructure; //Variable used to setup the SPI
    DMA_InitTypeDef DMA_InitStructure; //Variable used to setup the DMA


    //--Enable the SPI2 periph
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    // Reset SPI Interface
    SPI_I2S_DeInit(SPI2);

    //== SPI2 configuration
    SPI_StructInit(&SPI_InitStructure);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);


		//NVIC
		//Enable DMA1 channel IRQ Channel 
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		 
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
		NVIC_Init(&NVIC_InitStructure);

    //--Enable DMA1 clock--
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    //==Configure DMA1 - Channel4== (SPI -> memory)
    DMA_DeInit(DMA1_Channel4); //Set DMA registers to default values
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR; //Address of peripheral the DMA must map to
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)receiveBuffer; //Variable to which received data will be stored
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE; //Buffer size
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure); //Initialise the DMA
    DMA_Cmd(DMA1_Channel4, ENABLE); //Enable the DMA1 - Channel4         

    //==Configure DMA1 - Channel5== (memory -> SPI)
    DMA_DeInit(DMA1_Channel5); //Set DMA registers to default values
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR; //Address of peripheral the DMA must map to
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)sendBuffer; //Variable from which data will be transmitted
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE; //Buffer size
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure); //Initialise the DMA
    DMA_Cmd(DMA1_Channel5, ENABLE); //Enable the DMA1 - Channel5         

    // Enable SPI2
    SPI_Cmd(SPI2, ENABLE);

    // Enable the SPI2 RX & TX DMA requests
    SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx, ENABLE);
		
		/* Enable DMA interrupts */
		DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
		DMA_ITConfig(DMA1_Channel5, DMA_IT_TE, ENABLE);
}

void init_spiFrame(Communication_Typedef *comStruct)
{
	// Initialization of the motors
	comStruct->directionMotor.direction = 0;
	comStruct->directionMotor.speed = 0;
	comStruct->leftWheelMotor.direction = 0;
	comStruct->leftWheelMotor.speed = 0;
	comStruct->rightWheelMotor.direction = 0;
	comStruct->rightWheelMotor.speed = 0;

	// Initialization of the sensors
	comStruct->frontLeftUltrasound.distance = 0;
	comStruct->frontRightUltrasound.distance = 0;
	comStruct->frontCenterUltrasound.distance = 0;
	comStruct->rearLeftUltrasound.distance = 0;
	comStruct->rearRightUltrasound.distance = 0;
	comStruct->rearCenterUltrasound.distance = 0;

	// Initialization of the battery 
	comStruct->battery.state = 0;

}

void read_spiFrame(unsigned char* spiFrame, Communication_Typedef* comStruct)
{

	// Direction motor
	comStruct->directionMotor.direction = (spiFrame[DIRECTION_MOTOR] & DIRECTION_MASK) >> DIRECTION_OFFSET;
	comStruct->directionMotor.speed = 2*(spiFrame[DIRECTION_MOTOR] & SPEED_MASK) >> SPEED_OFFSET;
	
	// Wheel left motor
	comStruct->leftWheelMotor.direction = (spiFrame[LEFT_WHEEL_MOTOR] & DIRECTION_MASK) >> DIRECTION_OFFSET;
	comStruct->leftWheelMotor.speed = 2*(spiFrame[LEFT_WHEEL_MOTOR] & SPEED_MASK) >> SPEED_OFFSET;
	
	// Wheel right motor
	comStruct->rightWheelMotor.direction = (spiFrame[RIGHT_WHEEL_MOTOR] & DIRECTION_MASK) >> DIRECTION_OFFSET;
	comStruct->rightWheelMotor.speed = 2*(spiFrame[RIGHT_WHEEL_MOTOR] & SPEED_MASK) >> SPEED_OFFSET;
}

void write_spiFrame(unsigned char* spiFrame, Communication_Typedef comStruct)
{

	// Motor values equals 0
	spiFrame[DIRECTION_MOTOR] = 0;
	spiFrame[LEFT_WHEEL_MOTOR] = 0;
	spiFrame[RIGHT_WHEEL_MOTOR] = 0;

	// Sensors values 
	spiFrame[FRONT_LEFT_ULTRASOUND] = (char)comStruct.frontLeftUltrasound.distance;
	spiFrame[FRONT_RIGHT_ULTRASOUND] = (char)comStruct.frontRightUltrasound.distance;
	spiFrame[FRONT_CENTER_ULTRASOUND] = (char)comStruct.frontCenterUltrasound.distance;
	spiFrame[REAR_LEFT_ULTRASOUND] = (char)comStruct.rearLeftUltrasound.distance;
	spiFrame[REAR_RIGHT_ULTRASOUND] = (char)comStruct.rearRightUltrasound.distance;
	spiFrame[REAR_CENTER_ULTRASOUND] = (char)comStruct.rearCenterUltrasound.distance;

	// Battery
	spiFrame[BATTERY] = (char)comStruct.battery.state;
}
