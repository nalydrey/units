/*
 * app_utils.c
 *
 *  Created on: Feb 15, 2025
 *      Author: Oleksiy
 */
#include "app_utils.h"





void clockTheBus(void* instance){
	if(ifSPI(instance)){
		if(instance == SPI1){__HAL_RCC_SPI1_CLK_ENABLE();	return;}
	}

	if(ifGPIO(instance)){
		if(instance == GPIOA){ __HAL_RCC_GPIOA_CLK_ENABLE(); return;}
		if(instance == GPIOB){ __HAL_RCC_GPIOB_CLK_ENABLE(); return;}
		if(instance == GPIOC){ __HAL_RCC_GPIOC_CLK_ENABLE(); return;}
		if(instance == GPIOD){ __HAL_RCC_GPIOD_CLK_ENABLE(); return;}
		if(instance == GPIOE){ __HAL_RCC_GPIOE_CLK_ENABLE(); return;}
		if(instance == GPIOH){ __HAL_RCC_GPIOH_CLK_ENABLE(); return;}
	}
	if(ifTimer(instance)){
		if(instance == TIM1){ __HAL_RCC_TIM1_CLK_ENABLE();	return;}
		if(instance == TIM2){ __HAL_RCC_TIM2_CLK_ENABLE();	return;}
	}


}

void StopBusClocking(void* instance){
	if(ifTimer(instance)){
		if(instance == TIM1){ __HAL_RCC_TIM1_CLK_DISABLE();	return;}
		if(instance == TIM2){ __HAL_RCC_TIM2_CLK_ENABLE();	return;}
	}
}


uint8_t getAlter(void* instance){
	if(instance == SPI1) return GPIO_AF5_SPI1;
	if(instance == SPI2) return GPIO_AF5_SPI2;
	if(instance == SPI3) return GPIO_AF5_SPI3;
	if(instance == SPI4) return GPIO_AF5_SPI4;
	return 0;
}

IRQn_Type get_IRQn_Type(void* instance){
	if(instance == TIM2) return TIM2_IRQn;
	if(instance == TIM3) return TIM3_IRQn;
	if(instance == TIM4) return TIM4_IRQn;
	if(instance == TIM5) return TIM5_IRQn;
}

Bool ifSPI(void* instance){
	SPI_TypeDef * list[] = {SPI1, SPI2};
	uint8_t length = sizeof(list)/sizeof(list[0]);
	for(uint8_t i = 0; i < length; i++){
		if(list[i] == instance) return TRUE;
	}
	return FALSE;
}

Bool ifGPIO(void* instance){
	GPIO_TypeDef * list[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH};
	uint8_t length = sizeof(list)/sizeof(list[0]);
	for(uint8_t i = 0; i < length; i++){
		if(list[i] == instance) return TRUE;
	}
	return FALSE;
}

Bool ifTimer(void* instance){
	TIM_TypeDef * list[] = {TIM1, TIM2, TIM3, TIM4, TIM5, TIM9, TIM10, TIM11};
	uint8_t length = sizeof(list)/sizeof(list[0]);
	for(uint8_t i = 0; i < length; i++){
		if(list[i] == instance) return TRUE;
	}
	return FALSE;
}

Bool IsTimerEnabled(TIM_TypeDef *TIMx) {

    return (TIMx->CR1 & TIM_CR1_CEN) ? TRUE : FALSE;
}



