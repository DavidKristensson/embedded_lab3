#include "adc.h"
#include <avr/interrupt.h>
void adc_init(void) {
	/*
		Set ADLAR bit in ADMUX register to left adjust this way we only need to read ADCH for 8-bit precision
		Set RESFS0 bit in ADMUX register for AVcc with external capacitor at AREF pin

		Set ADPS0-1 bit in ADCSRA for prescaler 8
		Set ADEN bit in ADCSRA to enable ADC
		Set ADIE bit in ADCSRA to enable ADC interrupt
	*/
	ADMUX |= (1 << ADLAR) | (1 << REFS0);

	ADCSRA |= (1 << ADPS0) | (1 << ADPS1);
	ADCSRA |= (1 << ADEN) | (1 << ADIE);
}