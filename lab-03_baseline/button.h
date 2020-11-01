#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

void button_init();

void button_set_stateChange(uint8_t* buttonStateNow, uint8_t* buttonStateLast, uint8_t* changeState);

void button_set_buttonStateNow(uint8_t* buttonStateNow);

void button_set_buttonStateLast(uint8_t* buttonStateNow, uint8_t* buttonStateLast);

#endif