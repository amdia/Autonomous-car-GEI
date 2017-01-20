#ifndef _PWM_OUTPUT_H_
#define _PWM_OUTPUT_H_

#include <stm32f10x.h>

/** Counter clock frequency for the PWM */
#define COUNTER_CLOCK_FREQ_1MHz  1e6 
/** PWM output mode 1 */
#define PWM_MODE_1               1
/** PWM output mode 2 */
#define PWM_MODE_2               2
/** Minimal duty cycle for the PWM */
#define DUTY_CYCLE_MIN           25
/** Maximal duty cycle for the PWM */
#define DUTY_CYCLE_MAX           75
/** Duty cycle range for the PWM */
#define DUTY_CYCLE_RANGE 			(DUTY_CYCLE_MAX - DUTY_CYCLE_MIN)

/**
* @brief Values returned during a PWM initialization 
*/
typedef enum {
	/** Initialization went well */
	PWM_INIT_OK,
	/** The channel given has parameter for the initialization is different from 1,2,3 or 4 */
	PWM_NOT_CHANNEL_1_2_3_4,
	/** The mode given has parameter for the initialization is different from 1 or 2 */
	PWM_NOT_MODE_1_2
} PWM_InitReturnType;

/**
* @brief Structure that contains information about a PWM
*/
typedef struct {
	/** Pin on which the PWM has to be sent */
	uint16_t outputPin;
	/** Port on which the PWM has to be sent */
	GPIO_TypeDef* outputPinPort;
	/** Timer on which the PWM is set */
	TIM_TypeDef* timer;
	/** Timer channel on which the PWM is set */
	uint16_t timerChannel;
	/** Period of the PWM in microseconds */
	uint16_t periodUs;
	/** Duty cycle of the PWM in percent */
	uint16_t dutyCyclePercent;
	/** Mode of the PWM */
	uint16_t mode;
} PWM_TypeDef;

PWM_InitReturnType PWM_initialize(PWM_TypeDef* init_struct);
void PWM_CmdPeriod(PWM_TypeDef* init_struct, uint16_t period_us);
void PWM_CmdDutyCycle(PWM_TypeDef* init_struct, uint16_t duty_cycle_percent);

#endif // _PWM_OUTPUT_H_
