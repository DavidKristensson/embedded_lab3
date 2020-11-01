#ifndef STATEHANDLER_H_
#define STATEHANDLER_H_
#include <stdio.h>
#include "led.h"
#include "timer.h"

typedef enum {
	PULSE,
	POTENTIOMETER,
	BLINK,
	OFF
}STATE;

void state_changer(uint8_t* stateChange, STATE* STATE_HANDLER);

void state_action(STATE STATE_HANDLER, uint8_t* direction, uint8_t* pwmValue, uint8_t adcValue, uint8_t* counter);

#endif