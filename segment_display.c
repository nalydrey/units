/*
 * segment_display.c
 *
 *  Created on: Feb 20, 2025
 *      Author: Oleksiy
 */
#include "segment_display.h"
#include "led_template.h"



SegDisplay SegDisplay_Init(SegDisplay_Init_Struct * init_struct){

	SegDisplay display = {0};

	TIM_HandleTypeDef * htim = (TIM_HandleTypeDef *)malloc(sizeof(TIM_HandleTypeDef));

	Led_InitStruct * led_init_struct = (Led_InitStruct *)malloc(init_struct->segment_qty*sizeof(Led_InitStruct));
	Led_InitStruct * line_init_struct = (Led_InitStruct *)malloc(init_struct->line_qty*sizeof(Led_InitStruct));

	SegDisplay_Led * led_list = (SegDisplay_Led *)malloc(init_struct->segment_qty*sizeof(SegDisplay_Led));
	SegDisplay_Led * line_list = (SegDisplay_Led *)malloc(init_struct->line_qty*sizeof(SegDisplay_Led));

	display.htim = htim;
	display.leds = led_list;
	display.lines = line_list;
	display.gpio.led_init_struct = led_init_struct;
	display.gpio.line_init_struct = line_init_struct;
	display.init = init_struct;
	display.current_bit = 0;

	for(uint8_t i = 0; i < init_struct->segment_qty; i++){
		strcpy(display.leds[i].name, init_struct->leds[i].name);
		led_init_struct[i].gpio = init_struct->leds[i].gpio;
		led_init_struct[i].pin_number = init_struct->leds[i].pin_number;
		led_init_struct[i].activeState = (init_struct->common_line_type == COMMON_CATODE) ? GPIO_PIN_SET : GPIO_PIN_RESET;
		display.leds[i].led = Led_Init(&led_init_struct[i]);
	}

	for(uint8_t i = 0; i < init_struct->line_qty; i++){
		strcpy(display.lines[i].name, init_struct->common_lines[i].name);
		line_init_struct[i].gpio = init_struct->common_lines[i].gpio;
		line_init_struct[i].pin_number = init_struct->common_lines[i].pin_number;
		line_init_struct[i].activeState = (init_struct->common_line_type == COMMON_CATODE) ? GPIO_PIN_RESET : GPIO_PIN_SET;
		display.lines[i].led = Led_Init(&line_init_struct[i]);
	}

	_SegDisplay_Init_Timer(&display, init_struct->timer_instance);

	SegDisplay_Off(&display);

	return display;
}

void SegDisplay_Deinit(SegDisplay * display){
	free(display->gpio.led_init_struct);
	free(display->gpio.line_init_struct);
	free(display->leds);
	free(display->lines);
	free(display->htim);
}

void SegDisplay_ShowAll(SegDisplay * display){

	for(uint8_t i = 0; i < display->init->segment_qty; i++){
		Led_On(&display->leds[i].led);
	}
	for(uint8_t i = 0; i < display->init->line_qty; i++){
		Led_On(&display->lines[i].led);
	}
}

void SegDisplay_Show(SegDisplay * display, char value, Bool hasPoint){

	SegDisplay_Off(display);

	SegDisplay_Item * item = _Seg_Display_FindValue(value);

	for(uint8_t i = 0; i < display->init->segment_qty; i++){
		if(_SegDisplay_Include(item, display->leds[i].name)){
			Led_On(&display->leds[i].led);
		}
	}
	if(hasPoint) Led_On(&display->leds[7].led);

	for(uint8_t i = 0; i < display->init->line_qty; i++){
		if(i == display->current_bit) Led_On(&display->lines[i].led);
	}
}

void SegDisplay_Test(SegDisplay * display, uint16_t interval){

	uint8_t size = sizeof(template)/sizeof(template[0]);

	for(uint8_t i = 0; i < size; i++){
		SegDisplay_Show(display, template[i].name, FALSE);
		HAL_Delay(interval);
	}
}

SegDisplay_Item * _Seg_Display_FindValue(char value){

	uint8_t size = sizeof(template)/sizeof(template[0]);

	for(uint8_t i = 0; i < size; i++ ){
		if(value == template[i].name) return &template[i];
	}
	return 0;
}

Bool _SegDisplay_Include(SegDisplay_Item * item, SegDisplay_SegmentName segment){


	for(uint8_t i = 0; i < item->number_of_turned_on_leds; i++){
		if(!strcmp(item->working_leds[i], segment)) return TRUE;
	}
	return FALSE;
}

void SegDisplay_Off(SegDisplay * display){
	for(uint8_t i = 0; i < display->init->segment_qty; i++){
		Led_Off(&display->leds[i].led);
	}

	for(uint8_t i = 0; i < display->init->line_qty; i++){
		Led_Off(&display->lines[i].led);
	}
}

void SegDisplay_Change_Bit(SegDisplay * display){
	if(display->current_bit < display->init->line_qty)	display->current_bit++;
	else display->current_bit = 0;
}

void SegDisplay_Show_String(SegDisplay * display, char * str){
	uint8_t symbolQty = 0;


	for(uint8_t i = 0; str[i]; i++){
		symbolQty++;
	}

	SegDisplay_Symbol * arr = (SegDisplay_Symbol *)malloc(display->init->line_qty * sizeof(SegDisplay_Symbol));


	for(uint8_t i = 0, j=0; i < display->init->line_qty && j <= symbolQty ; i++, j++){
		Bool isNextPoint = (str[j + 1] == '.');
		Bool isCurrentPoint = (str[j] == '.');
		if(isCurrentPoint) {
			arr[i].symbol = ' ';
			arr[i].hasPoint = TRUE;
		}
		else if(isNextPoint){
			arr[i].symbol = str[j];
			arr[i].hasPoint = TRUE;
			j++;
		}
		else{
			arr[i].symbol = str[j];
			arr[i].hasPoint = FALSE;
		}

	}


	SegDisplay_Show(display, arr[display->current_bit].symbol, arr[display->current_bit].hasPoint);

	free(arr);
}

void SegDisplay_ShowData(SegDisplay * display){
	SegDisplay_Show_String(display, display->data);
	SegDisplay_Change_Bit(display);
}

void _SegDisplay_Init_Timer(SegDisplay * display, TIM_TypeDef * instance){

	clockTheBus(instance);

	display->htim->Instance = instance;

	display->htim->Init.Prescaler = 15;
	display->htim->Init.Period = 5999;
	display->htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	display->htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	HAL_TIM_Base_Init(display->htim);



	HAL_NVIC_SetPriority(get_IRQn_Type(instance), 0x0, 0);
	HAL_NVIC_EnableIRQ(get_IRQn_Type(instance));

	HAL_TIM_Base_Start_IT(display->htim);
}





