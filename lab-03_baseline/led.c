#include <avr/io.h>
#include "led.h"

void led_init() {
	/*
		Set pin PD6 in register DDRD for LED output
	*/
	DDRD |= (1 << PD6);
}

void simple_ramp(uint8_t* direction, uint8_t* pwmValue) {
	/*
		pwmValue goes up and down from 0-255
		OCR0A is set to pwmValue to change LED brightness/duty cycle
	*/
	if (*pwmValue == 255) {
		*direction *= -1;
	}
	else if (*pwmValue == 0) {
		*direction *= -1;
	}

	*pwmValue += *direction;
	OCR0A = *pwmValue;
}