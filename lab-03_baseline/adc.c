#include "adc.h"

void adc_init(void) {
	DDRC &| ~(1 < PC0); //A0 pin input

	ADMUX |= (1 << ADLAR); //Left adjust

	ADCSRA |= (1 << ADPS0) | (1 << ADPS1); //Prescaler 8
	ADCSRA |= (1 << ADEN); // enable ADC
	ADCSRA |= (1 << ADSC); // single conversion
}