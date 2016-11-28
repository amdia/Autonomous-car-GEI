#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "misc.h"
#include "SPI_functions.h"
#include "motor_rear.h"
#include "us_sensor.h"


void InitializeSPI2(uint8_t * receiveBuffer, uint8_t * sendBuffer)
{
	/***** GPIO *****/
			
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		// Configure used pins for GPIOB
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14; //MISO
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = /*GPIO_Pin_12 |*/ GPIO_Pin_13 | GPIO_Pin_15; //CS SCK MOSI
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		/***** SPI_Slave_and_DMA_Configuration *****/
	
		SPI_InitTypeDef SPI_InitStructure; //Variable used to setup the SPI
    DMA_InitTypeDef DMA_InitStructure; //Variable used to setup the DMA


    //--Enable the SPI2 periph
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    // Reset SPI Interface
    //SPI_I2S_DeInit(SPI2);

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
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 9;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		 
		NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
		NVIC_Init(&NVIC_InitStructure);

    //--Enable DMA1 clock--
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    //==Configure DMA1 - Channel4== (SPI -> memory)
    //DMA_DeInit(DMA1_Channel4); //Set DMA registers to default values
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(SPI2_BASE+0x0C);//&SPI2->DR; //Address of peripheral the DMA must map to
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

    //==Configure DMA1 - Channel5== (memory -> SPI)
    //DMA_DeInit(DMA1_Channel5); //Set DMA registers to default values
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(SPI2_BASE+0x0C);//&SPI2->DR; //Address of peripheral the DMA must map to
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

void init_spiFrame(Communication_Typedef *comStruct)
{
	// Initialization of the motors
	comStruct->directionMotor.direction = STOP;
	comStruct->directionMotor.angle = 0;
	
	comStruct->rear_motors[MOTOR_ARG].direction = MOTOR_REAR_STOP;
	comStruct->rear_motors[MOTOR_ARG].speed = 0;
	comStruct->rear_motors[MOTOR_ARG].distance = 0;
	
	comStruct->rear_motors[MOTOR_ARD].direction = MOTOR_REAR_STOP;
	comStruct->rear_motors[MOTOR_ARD].speed = 0;
	comStruct->rear_motors[MOTOR_ARD].distance = 0;

	// Initialization of the sensors
	comStruct->ultrasounds[ULTRASONIC_AVG].distance = 0;
	comStruct->ultrasounds[ULTRASONIC_AVD].distance = 0;
	comStruct->ultrasounds[ULTRASONIC_AVC].distance = 0;
	comStruct->ultrasounds[ULTRASONIC_ARG].distance = 0;
	comStruct->ultrasounds[ULTRASONIC_ARD].distance = 0;
	comStruct->ultrasounds[ULTRASONIC_ARC].distance = 0;

	// Initialization of the battery 
	comStruct->battery.state = 0;

}

void read_spiFrame(uint8_t* spiFrame, Communication_Typedef* comStruct)
{
		
		int dir, angle, speed;
		// ---------------------------------------------------------------------------- //
		//  																Direction motor															//
		//																																							//
		//  	Format of the octets : 																										//
		// 		| Direction | Angle | Angle | Angle | Angle | Angle | Angle | Angle |  		//
		// ---------------------------------------------------------------------------- //
			
		dir = (spiFrame[DIRECTION_MOTOR] & DIRECTION_MASK) >> DIRECTION_OFFSET;
	  angle = (spiFrame[DIRECTION_MOTOR] & ANGLE_MASK) >> ANGLE_OFFSET;
	
		if(angle == 0)
		{
			comStruct->directionMotor.direction = STOP;
			comStruct->directionMotor.angle = angle;
		}
		else
		{
			switch (dir) {
				case 0: // left
					comStruct->directionMotor.direction = LEFT;
					comStruct->directionMotor.angle = -angle;
				break;
				case 1: // right
					comStruct->directionMotor.direction = RIGHT;
					comStruct->directionMotor.angle = angle;	
				break;
				default:
						comStruct->directionMotor.direction = STOP;
						comStruct->directionMotor.angle = 0;	
			}
		}
		
		// -------------------------------------------------------------------------------------------------------- //
		//  																				leftwheel motor 		 																						//
		//																																																					//
		//  	Format of the octet : 																																								//
		// 		| Direction | Direction | Speed     | Speed     | Speed     | Speed     | Speed     | Speed    |  		//
		// -------------------------------------------------------------------------------------------------------- //	
			
		dir = (spiFrame[LEFT_WHEEL_MOTOR] & DIRECTION_MASK) >> DIRECTION_OFFSET;
		speed = (spiFrame[LEFT_WHEEL_MOTOR] & SPEED_MASK) >> SPEED_OFFSET;
		
		if(speed == 0)
		{
			comStruct->rear_motors[MOTOR_ARG].direction = MOTOR_REAR_STOP;
			comStruct->rear_motors[MOTOR_ARG].speed = speed;
		}
		else
		{
			switch (dir) {
				case 0: // forward
					comStruct->rear_motors[MOTOR_ARG].direction = MOTOR_REAR_FORWARD;
					comStruct->rear_motors[MOTOR_ARG].speed = speed;
				break;
				case 1: // backward
					comStruct->rear_motors[MOTOR_ARG].direction = MOTOR_REAR_BACKWARD;
					comStruct->rear_motors[MOTOR_ARG].speed = speed;
				break;
				default:
					comStruct->rear_motors[MOTOR_ARG].direction = MOTOR_REAR_STOP;
					comStruct->rear_motors[MOTOR_ARG].speed = 0;
			}
		}
			
		
		// -------------------------------------------------------------------------------------------------------- //
		//  																					rightwheel motor 		 																					//
		//																																																					//
		//  	Format of the octet : 																																								//
		// 		| Direction | Direction | Speed     | Speed     | Speed     | Speed     | Speed     | Speed    |  		//
		// -------------------------------------------------------------------------------------------------------- //	
			
		dir = (spiFrame[RIGHT_WHEEL_MOTOR] & DIRECTION_MASK) >> DIRECTION_OFFSET;
		speed = (spiFrame[RIGHT_WHEEL_MOTOR] & SPEED_MASK) >> SPEED_OFFSET;
		
		if(speed == 0)
		{
			comStruct->rear_motors[MOTOR_ARD].direction = MOTOR_REAR_STOP;
			comStruct->rear_motors[MOTOR_ARD].speed = 0;
		}
		else
		{
			switch (dir) {
				case 0: //forward 
					comStruct->rear_motors[MOTOR_ARD].direction = MOTOR_REAR_FORWARD;
					comStruct->rear_motors[MOTOR_ARD].speed = speed;
				break;
				case 1: // backward
					comStruct->rear_motors[MOTOR_ARD].direction = MOTOR_REAR_BACKWARD;
					comStruct->rear_motors[MOTOR_ARD].speed = speed;
				break;
				default:
					comStruct->rear_motors[MOTOR_ARD].direction = MOTOR_REAR_STOP;
					comStruct->rear_motors[MOTOR_ARD].speed = 0;
			}
		}
}

void write_spiFrame(uint8_t* spiFrame, Communication_Typedef comStruct)
{
	
	// Motor values equals 0
	spiFrame[DIRECTION_MOTOR] = 0;
	spiFrame[RIGHT_WHEEL_MOTOR] = 0;
	spiFrame[LEFT_WHEEL_MOTOR] = 0;
	spiFrame[LEFT_WHEEL_MOTOR_DISTANCE] = (int8_t)comStruct.rear_motors[MOTOR_ARD].distance;
	spiFrame[RIGHT_WHEEL_MOTOR_DISTANCE] = (int8_t)comStruct.rear_motors[MOTOR_ARG].distance;

	// Sensors values 
	spiFrame[FRONT_LEFT_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_AVG].distance;
	spiFrame[FRONT_RIGHT_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_AVD].distance;
	spiFrame[FRONT_CENTER_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_AVC].distance;
	spiFrame[REAR_LEFT_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_ARG].distance;
	spiFrame[REAR_RIGHT_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_ARD].distance;
	spiFrame[REAR_CENTER_ULTRASOUND] = (int8_t)comStruct.ultrasounds[ULTRASONIC_ARC].distance;

	// Battery
	spiFrame[BATTERY] = (int8_t)comStruct.battery.state;
	
}





