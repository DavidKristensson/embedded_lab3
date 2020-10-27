#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "button.h"
/*
	See README for shield configuration
*/
int main (void) {
	uart_init();
	button_init();

	uint8_t buttonStateLast = 0;
	uint8_t buttonStateNow = 0;

	while (1) {
		button_set_state_now(&buttonStateNow);

		button_print_state(&buttonStateNow, &buttonStateLast);

		button_set_state_last(&buttonStateNow, &buttonStateLast);
	}
	return 0;
}

