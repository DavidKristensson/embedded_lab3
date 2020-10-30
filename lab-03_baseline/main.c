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
/*
	See README for shield configuration
*/
volatile uint8_t adcValue = 0;
uint8_t direction = 1;
uint8_t pwmValue = 1;

ISR(TIMER2_COMPA_vect) {
	/*
		ISR interrupt that triggers on timer2
		Setting ADSC bit in ADCSRA register triggers single conversion of the ADC
		timer_toggleOC0A function turns led off by disabling OCR0A pin if the adcValue is 0
		The conveted adcValue is set to OCR0A to update duty cycle/brightness of LED

	*/
	ADCSRA |= (1 << ADSC);
	timer_toggleOc0a(adcValue);
	OCR0A = adcValue;
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
		sei function enables global interrupts
	*/
	uart_init();
	adc_init();
	timer_init();
	led_init();
	sei();
	while (1) {
		printf_P(PSTR("%d\n"), adcValue);
	}
	return 0;
}

