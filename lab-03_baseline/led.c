#include <avr/io.h>
#include "led.h"

void led_init() {
	/*
		Set pin PD6 in register DDRD for LED output
	*/
	DDRD |= (1 << PD6);
}

uint8_t simple_ramp(void) {
}