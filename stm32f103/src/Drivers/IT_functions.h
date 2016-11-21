#ifndef __IT_FUNCTION_H
#define __IT_FUNCTION_H

#include <stdint.h>

void GPIO_EXTI_Callback (uint16_t GPIO_Pin);
void scheduler_IT_callback(void);

#endif // __IT_FUNCTION_H

