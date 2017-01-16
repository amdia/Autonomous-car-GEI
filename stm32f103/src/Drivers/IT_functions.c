/**
* @file IT_functions.c
* @brief driver layer for the interruption handling
*/

#include "IT_functions.h"
#include <stm32f10x.h>

/* Private macro -------------------------------------------------------------*/

 /**
* @brief check on which exti the GPIO has the interrupt flag set 
* and then call the callback function and clear the pending bit
*
* 	A macro is a copy-paste
* "##x" allow to concatenate the param to the end of a string
* "##x##" allow to concatenante the param inside a string
* @param n number of the exti line
 */

#define EXTI_CALLBACKS(n) \
	if(EXTI_GetITStatus(EXTI_Line##n) != RESET){\
		GPIO_EXTI_Callback(GPIO_Pin_##n);\
		EXTI_ClearITPendingBit(EXTI_Line##n);\
	}\

/**
* @brief check on which timer the scheduler has the interrupt flag set 
* and then call the callback function and clear the pending bit
*
* A macro is a copy-paste
* "##x" allow to concatenate the param to the end of a string
* "##x##" allow to concatenante the param inside a string
* @param n: timer number
 */
	
#define SCHEDULER_CALLBACKS(n) \
	 if (TIM_GetITStatus(TIM##n, TIM_IT_Update) != RESET){\
		 scheduler_IT_callback();\
       TIM_ClearITPendingBit(TIM##n, TIM_IT_Update); \
    }\

	 
/* Private function prototypes -----------------------------------------------*/
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler (void);

void TIM1_UP_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
	 
/********************************/
/*       Public Functions       */
/********************************/

/**
* @brief  Overridable callback function for the GPIO interrupts (for the project, hall sensors)
* @param  GPIO_Pin GPIO pin
* @retval None
*/
__weak void GPIO_EXTI_Callback (uint16_t GPIO_Pin){}
	
/**
* @brief  Overridable callback function for the timer interrupt (for the project, scheduler)
* @param  None
* @retval None
*/
__weak void scheduler_IT_callback(void){}
	
/********************************/
/*      Private Functions       */
/********************************/

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
* @brief  This function handles EXTI0_IRQHandler interrupt request.
* @param  None
* @retval None
*/
void EXTI0_IRQHandler(void){
	EXTI_CALLBACKS(0);
}

/**
* @brief  This function handles EXTI1_IRQHandler interrupt request.
* @param  None
* @retval None
*/
void EXTI1_IRQHandler(void){
	EXTI_CALLBACKS(1);
}

/**
* @brief  This function handles EXTI2_IRQHandler interrupt request.
* @param  None
* @retval None
*/
void EXTI2_IRQHandler(void){
	EXTI_CALLBACKS(2);
}

/**
* @brief  This function handles EXTI3_IRQHandler interrupt request.
* @param  None
* @retval None
*/
void EXTI3_IRQHandler(void){
	EXTI_CALLBACKS(3);
}

/**
* @brief  This function handles EXTI4_IRQHandler interrupt request.
* @param  None
* @retval None
*/
void EXTI4_IRQHandler(void){
	EXTI_CALLBACKS(4);
}

/**
* @brief  This function handles EXTI9_5_IRQHandler interrupt request.
* @param  None
* @retval None
*/
void EXTI9_5_IRQHandler(void)
{
	EXTI_CALLBACKS(5);
	EXTI_CALLBACKS(6);
	EXTI_CALLBACKS(7);
	EXTI_CALLBACKS(8);
	EXTI_CALLBACKS(9);
}

/**
* @brief  This function handles EXTI15_10_IRQHandler interrupt request.
* @param  None
* @retval None
*/
void EXTI15_10_IRQHandler(void)
{
	EXTI_CALLBACKS(10);
	EXTI_CALLBACKS(11);
	EXTI_CALLBACKS(12);
	EXTI_CALLBACKS(13);
	EXTI_CALLBACKS(14);
	EXTI_CALLBACKS(15);
}

/**
* @brief  This function handles TIM1_UP_IRQHandler interrupt request.
* @param  None
* @retval None
*/
void TIM1_UP_IRQHandler(void){
	SCHEDULER_CALLBACKS(1);
}

/**
* @brief  This function handles TIM2_IRQHandler interrupt request.
* @param  None
* @retval None
*/
void TIM2_IRQHandler(void){
	SCHEDULER_CALLBACKS(2);
}

/**
* @brief  This function handles TIM3_IRQHandler interrupt request.
* @param  None
* @retval None
*/
void TIM3_IRQHandler(void){
	SCHEDULER_CALLBACKS(3);
}

/**
* @brief  This function handles TIM4_IRQHandler interrupt request.
* @param  None
* @retval None
*/
void TIM4_IRQHandler(void){
	SCHEDULER_CALLBACKS(4);
}

/**
* @brief  This function handles DMA1_Channel4 interrupt request.
* @param  None
* @retval None
*/
void DMA1_Channel4_IRQHandler(void){
	DMA_ClearITPendingBit(DMA1_IT_GL4);
}

/**
* @brief  This function handles DMA1_Channel5 interrupt request.
* @param  None
* @retval None
*/
void DMA1_Channel5_IRQHandler(void){
	DMA_ClearITPendingBit(DMA1_IT_GL5);
}



