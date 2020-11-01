#include "adc.h"
#include <avr/interrupt.h>
void adc_init(void) {
	/*
		Reset ADMUX register
		Set ADLAR bit in ADMUX register to left adjust, this way we only need to read ADCH for 8-bit precision
		Set REFS0 bit in ADMUX register for AVcc with external capacitor at AREF pin

		Reset ADCSRA register
		Set ADPS0-1 bits in ADCSRA for prescaler 8
		Set ADEN bit in ADCSRA to enable ADC
		Set ADIE bit in ADCSRA to enable ADC interrupt
	*/
	ADMUX = 0;
	ADMUX |= (1 << ADLAR) | (1 << REFS0);

	ADCSRA = 0;
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1);
	ADCSRA |= (1 << ADEN) | (1 << ADIE);
}