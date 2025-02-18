/*
 * button.h
 *
 *  Created on: Feb 18, 2025
 *      Author: Oleksiy
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"
#include "app_utils.h"


typedef enum{
	UNPRESSED,
	PRESSED
} Button_PressedState;



typedef struct {
	GPIO_TypeDef * gpio;
	uint16_t pin;
	GPIO_PinState activeState;
	TIM_TypeDef * timer;
} Button_InitStruct;



typedef struct Button{
	Bool _isBlocked;
	uint16_t prevTimerValue;
	Button_InitStruct * init;
	Button_PressedState isPressed;
	TIM_HandleTypeDef _htim;
	void (*pressCallback)(void);
	void (*intervalCallback)(void);
	void (*pushUpCallback)(void);
} Button;

Button Button_init(Button_InitStruct * buttonInit);
Button_PressedState Button_poll(Button *);
void __Button_initTimer(Button *);
void __Button_enableAndStartTimer(TIM_HandleTypeDef * htim);
void __Button_disableAndStopTimer(TIM_HandleTypeDef * htim);



#endif /* INC_BUTTON_H_ */
