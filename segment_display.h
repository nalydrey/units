/*
 * segment_display.h
 *
 *  Created on: Feb 20, 2025
 *      Author: Oleksiy
 */

#ifndef INC_SEGMENT_DISPLAY_H_
#define INC_SEGMENT_DISPLAY_H_
#include "main.h"
#include "Led.h"
#include <string.h>
#include <stdlib.h>

typedef enum {
	COMMON_CATODE,
	COMMON_ANODE
} SegDisplay_CommonLineType;

typedef struct {
	Bool hasPoint;
	char symbol;
} SegDisplay_Symbol;

typedef char  SegDisplay_SegmentName[3];

typedef struct {
	char name;
	uint8_t number_of_turned_on_leds;
	SegDisplay_SegmentName * working_leds;
} SegDisplay_Item;

typedef struct{
	SegDisplay_SegmentName name;
	GPIO_TypeDef * gpio;
	uint16_t pin_number;
} SegDisplay_LedInitStruct;

typedef struct{
	SegDisplay_SegmentName name;
	Led led;
} SegDisplay_Led;


typedef struct {
	uint8_t segment_qty;
	uint8_t line_qty;
	SegDisplay_LedInitStruct * leds;
	SegDisplay_LedInitStruct * common_lines;
	SegDisplay_CommonLineType common_line_type;
	TIM_TypeDef * timer_instance;
} SegDisplay_Init_Struct;

typedef struct {
	Led_InitStruct * led_init_struct;
	Led_InitStruct * line_init_struct;
} SegDisplay_GPIO_Init;

typedef struct {
	SegDisplay_GPIO_Init gpio;
	SegDisplay_Init_Struct * init;
	SegDisplay_Led * leds;
	SegDisplay_Led * lines;
	uint8_t current_bit;
	char *data;
	TIM_HandleTypeDef * htim;
} SegDisplay;


SegDisplay SegDisplay_Init(SegDisplay_Init_Struct * init_struct);
void SegDisplay_ShowAll(SegDisplay * display);
void SegDisplay_Show(SegDisplay * display, char value, Bool hasPoint);
void SegDisplay_Test(SegDisplay * display, uint16_t interval);
SegDisplay_Item * _Seg_Display_FindValue(char value);
Bool _SegDisplay_Include(SegDisplay_Item * item, SegDisplay_SegmentName segment);
void SegDisplay_Off(SegDisplay * display);
void SegDisplay_Change_Bit(SegDisplay * display);
void SegDisplay_Show_String(SegDisplay * display, char * str);
void SegDisplay_ShowData(SegDisplay * display);
void _SegDisplay_Init_Timer(SegDisplay * display, TIM_TypeDef * instance);

#endif /* INC_SEGMENT_DISPLAY_H_ */
