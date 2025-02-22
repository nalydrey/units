/*
 * led_template.h
 *
 *  Created on: Feb 21, 2025
 *      Author: Oleksiy
 */

#ifndef INC_LED_TEMPLATE_H_
#define INC_LED_TEMPLATE_H_
#include "segment_display.h"


SegDisplay_SegmentName leds_1[] = {"b", "c"};
SegDisplay_SegmentName leds_2[] = {"a", "b", "g", "e", "d"};
SegDisplay_SegmentName leds_3[] = {"a", "b", "c", "d", "g"};
SegDisplay_SegmentName leds_4[] = {"b", "c", "f", "g"};
SegDisplay_SegmentName leds_5[] = {"a", "f", "g", "c", "d"};
SegDisplay_SegmentName leds_6[] = {"a", "c", "e", "d", "f", "g"};
SegDisplay_SegmentName leds_7[] = {"a", "b", "c"};
SegDisplay_SegmentName leds_8[] = {"a", "b", "c", "d", "e", "f", "g"};
SegDisplay_SegmentName leds_9[] = {"a", "b", "c", "d", "f", "g"};
SegDisplay_SegmentName leds_0[] = {"a", "b", "c", "d", "e", "f"};
SegDisplay_SegmentName leds_point[] = {"dp"};
SegDisplay_SegmentName leds_minus[] = {"g"};
SegDisplay_SegmentName leds_o[] = {"g", "c", "d", "e"};
SegDisplay_SegmentName leds_A[] = {"a", "b", "c", "e", "f", "g"};
SegDisplay_SegmentName leds_L[] = {"d", "e", "f"};
SegDisplay_SegmentName leds_l[] = {"e", "f"};
SegDisplay_SegmentName leds_H[] = {"b", "c", "e", "f", "g"};
SegDisplay_SegmentName leds_d[] = {"b", "c", "d", "e", "g"};
SegDisplay_SegmentName leds_b[] = {"c", "d", "e", "f", "g"};
SegDisplay_SegmentName leds_E[] = {"a", "d", "e", "f", "g"};
SegDisplay_SegmentName leds_P[] = {"a", "b", "e", "f", "g"};
SegDisplay_SegmentName leds_S[] = {"a", "c", "d", "f", "g"};
SegDisplay_SegmentName leds_F[] = {"a", "e", "f", "g"};
SegDisplay_SegmentName leds_c[] = {"d", "e", "g"};
SegDisplay_SegmentName leds_r[] = {"g", "e"};
SegDisplay_SegmentName leds_t[] = {"d", "e", "f", "g"};
SegDisplay_SegmentName leds_U[] = {"b", "c", "d", "e", "f"};
SegDisplay_SegmentName leds_u[] = {"c", "d", "e"};
SegDisplay_SegmentName leds_leftBracket[] = {"a", "d", "e", "f"};
SegDisplay_SegmentName leds_rightBracket[] = {"a", "b", "c", "d"};

SegDisplay_Item template[] = {
		{'1', 2, leds_1},
		{'2', 5, leds_2},
		{'3', 5, leds_3},
		{'4', 4, leds_4},
		{'5', 5, leds_5},
		{'6', 6, leds_6},
		{'7', 3, leds_7},
		{'8', 7, leds_8},
		{'9', 6, leds_9},
		{'0', 6, leds_0},
		{'.', 1, leds_point},
		{'-', 1, leds_minus},
		{'o', 4, leds_o},
		{'O', 6, leds_0},
		{'A', 6, leds_A },
		{'b', 5, leds_b},
		{'C', 5, leds_leftBracket},
		{'c', 3, leds_c},
		{'d', 5, leds_d},
		{'E', 5, leds_E},
		{'F', 4, leds_F},
		{'L', 3, leds_L},
		{'l', 2, leds_l},
		{'H', 5, leds_H},
		{'P', 5, leds_P},
		{'S', 5, leds_S},
		{'t', 4, leds_t},
		{'U', 5, leds_U},
		{'u', 3, leds_u},
		{'r', 2, leds_r},
		{'(', 4, leds_leftBracket},
		{')', 4, leds_rightBracket},
};





#endif /* INC_LED_TEMPLATE_H_ */
