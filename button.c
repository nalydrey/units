/*
 * button.c
 *
 *  Created on: Feb 18, 2025
 *      Author: Oleksiy
 */

#include "button.h"
#include "app_utils.h"

Button Button_init(Button_InitStruct * buttonInit){

	Button button = {0};
	button.init = buttonInit;
	button.isPressed = FALSE;
	button._isBlocked = FALSE;


	GPIO_InitTypeDef gpio_init;

	clockTheBus(buttonInit->gpio);

	gpio_init.Pin = buttonInit->pin;
	gpio_init.Mode = GPIO_MODE_INPUT;
	gpio_init.Pull = buttonInit->activeState ? GPIO_PULLDOWN : GPIO_PULLUP;
	gpio_init.Speed = GPIO_SPEED_LOW;

	HAL_GPIO_Init(buttonInit->gpio, &gpio_init);

	if(buttonInit->timer){
		__Button_initTimer(&button);
	}

	return button;
}



Button_PressedState Button_poll(Button * button){

	GPIO_PinState state = HAL_GPIO_ReadPin(button->init->gpio, button->init->pin);
	uint16_t currentTimerValue = __HAL_TIM_GET_COUNTER(&button->_htim);
	Bool interrupt = FALSE;

	if(button->_htim.State == HAL_TIM_STATE_RESET){
		button->_isBlocked = FALSE;
	}

	if(button->_htim.State == HAL_TIM_STATE_BUSY){
		uint16_t interval= currentTimerValue - button->prevTimerValue;
		if(currentTimerValue < button->prevTimerValue){
			interval = ~interval;
			interrupt = TRUE;
		}
		button->_isBlocked = interval > 20 ? FALSE : TRUE;
	}

	if(button->init->activeState == state && !button->_isBlocked){
		__Button_enableAndStartTimer(&button->_htim);
		button->prevTimerValue = currentTimerValue;

		if(button->isPressed == UNPRESSED){
			button->isPressed = PRESSED;
			button->pressCallback();
		}

		if(interrupt){
			button->intervalCallback();
		}

	}
	if(button->init->activeState != state && !button->_isBlocked && button->isPressed){
		button->isPressed = UNPRESSED;
		__Button_disableAndStopTimer(&button->_htim);
		button->pushUpCallback();
	}

	return button->isPressed;
}

void __Button_initTimer(Button * button){

	TIM_TypeDef *timer = button->init->timer;

	TIM_HandleTypeDef htim = {0};

	htim.Instance = timer;

	htim.Init.Prescaler = 15999;
	htim.Init.Period = 999;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	button->_htim = htim;
}

void __Button_enableAndStartTimer(TIM_HandleTypeDef * htim){
	if(htim->Instance){
		if(htim->State == HAL_TIM_STATE_RESET){
			clockTheBus(htim->Instance);
			HAL_TIM_Base_Init(htim);
			HAL_TIM_Base_Start(htim);
		}
	}
}

void __Button_disableAndStopTimer(TIM_HandleTypeDef * htim){
		if(htim->Instance){
		if(htim->State == HAL_TIM_STATE_BUSY){
			HAL_TIM_Base_Stop(htim);
			HAL_TIM_Base_DeInit(htim);
			StopBusClocking(htim->Instance);
		}
	}
}


