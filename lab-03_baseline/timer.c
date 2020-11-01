#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void timer_init() {
	/*
		Timer0:
		Reset TCCR0A-B registers
		WGM00-1 bits set in TCCR0A register activates PWM fast mode
		COM0A1 bit set activates clear OC0A on match(start from bottom), non inverted.
		With CS00 and CS01 bits set we get a 64 prescaler

		Timer2:
		Reset TCCR2A-B registers
		WGM21 bit set in TCCR2A register activates CTC mode
		Bits CS20-2 set in TCCR2B register sets a 1024 prescaler

		Reset TIMSK2 register
		OCIE2A bit is set in TIMSK2 register enables timer/counter2 compare match A interrupt

		Top value of OCR2A is set to 155
		TCNT2 is initated to a value of 0
	*/
	TCCR0A = 0;
	TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1);
	TCCR0B = 0;
	TCCR0B |= (1 << CS00) | (1 << CS01);

	TCCR2A = 0;
	TCCR2A |= (1 << WGM21);

	TCCR2B = 0;
	TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22);

	TIMSK2 = 0;
	TIMSK2 |= (1 << OCIE2A); 

	OCR2A = 155;
	TCNT2 = 0;
}

void timer_toggleOc0a(uint8_t adcValue) {
	/*
		When adcValue is 0 OCR0A pin is disabled since PWM fast doesnt turn LED off completely
		If adcValue is greater than 0 it enables the pin again
	*/
	if (adcValue > 0) {
		TCCR0A |= (1 << COM0A1);
	}
	else {
		TCCR0A &= ~(1 << COM0A1);
	}
}

