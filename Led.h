/*
 * app_led.h
 *
 *  Created on: Feb 14, 2025
 *      Author: Oleksiy
 */


#ifndef INC_APP_LED_H_
#define INC_APP_LED_H_
// main.h contain HAL - library
#include "main.h"
#include "app_utils.h"


typedef struct {
	GPIO_TypeDef * gpio;
	uint16_t pin_number;
	GPIO_PinState activeState;
} Led_InitStruct;


typedef struct {
	Led_InitStruct * init;
	Bool _isActive;
} Led;

Led Led_Init(Led_InitStruct *);
Bool Led_On(Led * led);
Bool Led_Off(Led * led);
Bool Led_Toggle(Led * led);



#endif /* INC_APP_LED_H_ */
