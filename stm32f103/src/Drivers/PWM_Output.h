#ifndef _PWM_OUTPUT_H_
#define _PWM_OUTPUT_H_

#include <stm32f10x.h>

#define COUNTER_CLOCK_FREQ_1MHz  1e6 
#define PWM_MODE_1               1
#define PWM_MODE_2               2
#define DUTY_CYCLE_MIN           25
#define DUTY_CYCLE_MAX           75
#define DUTY_CYCLE_RANGE 			(DUTY_CYCLE_MAX - DUTY_CYCLE_MIN)

typedef enum {
  PWM_INIT_OK,
  PWM_NOT_CHANNEL_1_2_3_4,
  PWM_NOT_MODE_1_2
} PWM_InitReturnType;

typedef struct {
  uint16_t outputPin;
  GPIO_TypeDef* outputPinPort;
  TIM_TypeDef* timer;
  uint16_t timerChannel;
  uint16_t periodUs;
  uint16_t dutyCyclePercent;
  uint16_t mode;
} PWM_TypeDef;

PWM_InitReturnType PWM_initialize(PWM_TypeDef* init_struct);
void PWM_CmdPeriod(PWM_TypeDef* init_struct, uint16_t period_us);
void PWM_CmdDutyCycle(PWM_TypeDef* init_struct, uint16_t duty_cycle_percent);

#endif // _PWM_OUTPUT_H_
