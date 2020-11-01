#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "button.h"
#include "adc.h"
#include "stateHandler.h"
/*
	See README for shield configuration
*/

uint8_t adcValue = 0;
uint8_t direction = 1;
uint8_t pwmValue = 1;
uint8_t buttonStateNow = 0;
uint8_t buttonStateLast = 0;
uint8_t stateChange = 0;
uint8_t counter = 0;
STATE STATE_HANDLER = PULSE;

ISR(TIMER2_COMPA_vect) {
	/*
		ISR interrupt that triggers on timer2
	*/
	button_set_buttonStateNow(&buttonStateNow);
	button_set_stateChange(&buttonStateNow, &buttonStateLast, &stateChange);
	button_set_buttonStateLast(&buttonStateNow, &buttonStateLast);
	state_changer(&stateChange, &STATE_HANDLER);
	state_action(STATE_HANDLER, &direction, &pwmValue, adcValue, &counter);
}

ISR(ADC_vect) {
	/*
		ISR interrupt that triggers when ADC conversation is finished
		Adc converted value is set to adcValue variabel
	*/
	adcValue = ADCH;
}

int main (void) {
	/*
		Initializing peripherals
		sei function enables global interrupts
	*/
	
	uart_init();
	adc_init();
	timer_init();
	led_init();
	button_init();
	
	sei();
	while (1) {
	}
	return 0;
}

