#include "button.h"

void button_init() {
	/*
	 	Initializing Arduino pin D2 by setting PD2 bit to 0(INPUT) in DDRD register
		Using external pulldown resistor
	*/
	DDRD &= ~(1 << PD2);
}

void button_set_buttonStateNow(uint8_t* buttonStateNow) {
	/*
		If button is pressed PIND2 bit in PIND register is high
		If it is high buttonStateNow is changed it accordingly
	*/
	if (PIND & (1 << PIND2)) {
		*buttonStateNow = 1;
	}
	else {
		*buttonStateNow = 0;
	}
}

void button_set_stateChange(uint8_t* buttonStateNow, uint8_t* buttonStateLast, uint8_t* stateChange) {
	/*
		"Pushed\n\r" is sent through UART when the button is pressed
		"Released\n\r" when the button is released
		Upon button release stateChange is set
	*/
	if (*buttonStateNow == 1 && *buttonStateLast == 0) {
		printf_P(PSTR("pushed\r\n"));
	}
	else if (*buttonStateNow == 0 && *buttonStateLast == 1) {
		printf_P(PSTR("released\r\n"));
		*stateChange = 1;
	}
}

void button_set_buttonStateLast(uint8_t* buttonStateNow, uint8_t* buttonStateLast) {
	/*
		The last button state is updated
	*/
	*buttonStateLast = *buttonStateNow;
}