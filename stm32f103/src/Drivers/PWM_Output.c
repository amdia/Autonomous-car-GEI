/**
* @file PWM_Output.c
* @brief driver layer for the pwm
*/
#include "PWM_Output.h"
#include "timer.h"
#include "gpio.h"

/* Private function prototypes -----------------------------------------------*/
static uint16_t get_pulse_length(uint16_t duty_cycle_percent, uint16_t periodUs);

/********************************/
/*      Public Functions        */
/********************************/

/**
* @brief initialization of a PWM
* @param init_struct PWM structure contains the information necessary to the configuration and is read by this function
* @retval status of the initialization (ok or not)
*/
PWM_InitReturnType PWM_initialize(PWM_TypeDef* init_struct) {
	TIM_OCInitTypeDef outputCaptureInit;
  
  // configure output pin
	GPIO_init(init_struct->outputPinPort, init_struct->outputPin, GPIO_Mode_AF_PP);
  
  // configure timer output compare
	timer_init(init_struct->timer, COUNTER_CLOCK_FREQ_1MHz, init_struct->periodUs);
	
  // configure a timer channel as pwm output mode 1
		 if (init_struct->mode == PWM_MODE_1) 
			outputCaptureInit.TIM_OCMode = TIM_OCMode_PWM1;
  else if (init_struct->mode == PWM_MODE_2) 
			outputCaptureInit.TIM_OCMode = TIM_OCMode_PWM2;
  else 
			return PWM_NOT_MODE_1_2;
  
  outputCaptureInit.TIM_OutputState = TIM_OutputState_Enable;
  outputCaptureInit.TIM_Pulse = get_pulse_length(init_struct->dutyCyclePercent, init_struct->periodUs);
  outputCaptureInit.TIM_OCPolarity = TIM_OCPolarity_High;
  
  if (init_struct->timerChannel == TIM_Channel_1) {
    TIM_OC1Init(init_struct->timer, &outputCaptureInit);
    TIM_OC1PreloadConfig(init_struct->timer, TIM_OCPreload_Enable);
  } else if (init_struct->timerChannel == TIM_Channel_2) {
    TIM_OC2Init(init_struct->timer, &outputCaptureInit);
    TIM_OC2PreloadConfig(init_struct->timer, TIM_OCPreload_Enable);
  } else if (init_struct->timerChannel == TIM_Channel_3) {
    TIM_OC3Init(init_struct->timer, &outputCaptureInit);
    TIM_OC3PreloadConfig(init_struct->timer, TIM_OCPreload_Enable);
  } else if (init_struct->timerChannel == TIM_Channel_4) {
    TIM_OC4Init(init_struct->timer, &outputCaptureInit);
    TIM_OC4PreloadConfig(init_struct->timer, TIM_OCPreload_Enable);
  } else return PWM_NOT_CHANNEL_1_2_3_4;
  
  //TIM_ARRPreloadConfig(init_struct->timer, ENABLE);
  //TIM_Cmd(init_struct->timer, ENABLE);
  
  return PWM_INIT_OK;
}

/**
* @brief configuration of the PWM duty cyle which can be changed at any time
* @param init_struct PWM structure contains the information necessary to the configuration and is written by this function
* @param duty_cycle_percent wanted duty cycle for the PWM [0,100]
* @retval None
*/
void PWM_CmdDutyCycle(PWM_TypeDef* init_struct, uint16_t duty_cycle_percent) {
  uint16_t pulseLength = get_pulse_length(duty_cycle_percent, init_struct->periodUs);
  if (init_struct->timerChannel == TIM_Channel_1) {
    TIM_SetCompare1(init_struct->timer, pulseLength);
  } else if (init_struct->timerChannel == TIM_Channel_2) {
    TIM_SetCompare2(init_struct->timer, pulseLength);
  } else if (init_struct->timerChannel == TIM_Channel_3) {
    TIM_SetCompare3(init_struct->timer, pulseLength);
  } else if (init_struct->timerChannel == TIM_Channel_4) {
    TIM_SetCompare4(init_struct->timer, pulseLength);
  } else return;
  init_struct->dutyCyclePercent = duty_cycle_percent;
}

/**
* @brief configuration of the PWM period
* @param init_struct PWM structure contains the information necessary to the configuration and is written by this function
* @param period_us wanted period for the PWM
* @retval None
*/
void PWM_CmdPeriod(PWM_TypeDef* init_struct, uint16_t period_us) {
  TIM_SetAutoreload(init_struct->timer, period_us); 
  init_struct->periodUs = period_us;
}

/********************************/
/*      Private Functions       */
/********************************/

/**
* @brief returns the pulse length, based on the duty cycle percent and the period
* @param duty_cycle_percent duty cycle percent of the PWM
* @param period_us period of the PWM
* @retval pulse length
*/
uint16_t get_pulse_length(uint16_t duty_cycle_percent, uint16_t periodUs){
	return (uint16_t)(periodUs * duty_cycle_percent / 100) - 1;
}
