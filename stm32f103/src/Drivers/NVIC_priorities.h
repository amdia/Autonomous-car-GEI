#ifndef __NVIC_PRIORITIES_H
#define __NVIC_PRIORITIES_H

/** Priority of the interruption of the systick. Has to be the highest */
#define SYSTICK_PRIORITY		0

/** Priority of the interruption of the SPI */
#define SPI_PRIORITY				7

/** Priority of the interruption of all the ultrasonic sensors */
#define ULTRASONIC_PRIO 8

/** Priority of the interruption of all the hall sensors */
#define HALL_PRIO 7

/** Priority of the interruption of the scheduler */
#define SCHEDULER_IT_PRIORITY		10

#endif //__NVIC_PRIORITIES_H
