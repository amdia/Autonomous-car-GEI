#include "PWM_Output.h"
#include "timer.h"

PWM_InitReturnType PWM_initialize(PWM_TypeDef* init_struct) {
  TIM_OCInitTypeDef outputCaptureInit;
  GPIO_InitTypeDef pinInit;
  
  // configure output pin
  pinInit.GPIO_Mode = GPIO_Mode_AF_PP;
  pinInit.GPIO_Pin = init_struct->outputPin;
  pinInit.GPIO_Speed = init_struct->speed;
  GPIO_Init(init_struct->outputPinPort, &pinInit);
  
  // configure timer output compare
	timer_init(init_struct->timer, COUNTER_CLOCK_FREQ_1MHz, init_struct->periodUs);
  
  // configure a timer channel as pwm output mode 1
  if (init_struct->mode == PWM_MODE_1) outputCaptureInit.TIM_OCMode = TIM_OCMode_PWM1;
  else if (init_struct->mode == PWM_MODE_2) outputCaptureInit.TIM_OCMode = TIM_OCMode_PWM2;
  else return PWM_NOT_MODE_1_2;
  outputCaptureInit.TIM_OutputState = TIM_OutputState_Enable;
  outputCaptureInit.TIM_Pulse = (uint16_t)(init_struct->periodUs * init_struct->dutyCyclePercent / 100) - 1;
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
  
  return PWM_INIT_OK;
}


void PWM_CmdDutyCycle(PWM_TypeDef* init_struct, uint16_t duty_cycle_percent) {
  uint16_t pulseLength = (uint16_t)(init_struct->periodUs * duty_cycle_percent / 100) - 1;
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



void PWM_CmdPeriod(PWM_TypeDef* init_struct, uint16_t period_us) {
  TIM_SetAutoreload(init_struct->timer, period_us); 
  init_struct->periodUs = period_us;
}
