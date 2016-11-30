#ifndef __NVIC_PRIORITIES_H
#define __NVIC_PRIORITIES_H

#define SYSTICK_PRIORITY		0

#define SPI_PRIORITY				7

// All ultrasonic sensor interrupts share the same priority
#define ULTRASONIC_PRIO 8

// All hall sensor interrupts share the same priority
#define HALL_PRIO 7

#define SCHEDULER_IT_PRIORITY		10


#endif //__NVIC_PRIORITIES_H
