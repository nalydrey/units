/*
 * app_utils.h
 *
 *  Created on: Feb 15, 2025
 *      Author: Oleksiy
 */

#ifndef INC_APP_UTILS_H_
#define INC_APP_UTILS_H_
#include "main.h"



typedef enum {
	FALSE,
	TRUE
} Bool;

void clockTheBus(void* instance);
void StopBusClocking(void* instance);

uint8_t getAlter(void* instance);
Bool ifSPI(void* instance);
Bool ifGPIO(void* instance);
Bool ifTimer(void* instance);

Bool IsTimerEnabled(TIM_TypeDef *TIMx);

#endif /* INC_APP_UTILS_H_ */
