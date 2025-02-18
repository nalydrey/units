/*
 * app_led.c
 *
 *  Created on: Feb 14, 2025
 *      Author: Oleksiy
 */
#include "Led.h"


Led Led_Init(Led_InitStruct * ledInit){

	Led led = {0};

	led.init = ledInit;


	GPIO_InitTypeDef gpio_init = {0};

	clockTheBus(led.init->gpio);

	gpio_init.Pin = led.init->pin_number;
	gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init.Pull = GPIO_NOPULL;
	gpio_init.Speed = GPIO_SPEED_LOW;

	HAL_GPIO_Init(led.init->gpio, &gpio_init);

	return led;
}


Bool Led_On(Led * led){
	(led->init->activeState == GPIO_PIN_SET) ?
	HAL_GPIO_WritePin(led->init->gpio, led->init->pin_number, GPIO_PIN_SET)
	:
	HAL_GPIO_WritePin(led->init->gpio, led->init->pin_number, GPIO_PIN_RESET);

	led->_isActive = TRUE;
	return  led->_isActive;
}

Bool Led_Off(Led * led){
	(led->init->activeState == GPIO_PIN_SET) ?
	HAL_GPIO_WritePin(led->init->gpio, led->init->pin_number, GPIO_PIN_RESET)
	:
	HAL_GPIO_WritePin(led->init->gpio, led->init->pin_number, GPIO_PIN_SET);

	led->_isActive = FALSE;
	return  led->_isActive;
}
Bool Led_Toggle(Led * led){

	HAL_GPIO_TogglePin(led->init->gpio, led->init->pin_number);

	GPIO_PinState state = HAL_GPIO_ReadPin(led->init->gpio, led->init->pin_number);

		if(state == GPIO_PIN_SET){
			led->_isActive = (led->init->activeState) ? TRUE : FALSE;
		}
		else{
			led->_isActive = (led->init->activeState) ? FALSE : TRUE;
		}

	return led->_isActive;
}
