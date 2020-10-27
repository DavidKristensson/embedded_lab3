#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

void button_init();

void button_print_state(uint8_t* buttonStateNow, uint8_t* buttonStateLast);

void button_set_state_now(uint8_t* buttonStateNow);

void button_set_state_last(uint8_t* buttonStateNow, uint8_t* buttonStateLast);

#endif