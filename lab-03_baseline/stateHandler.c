#include "stateHandler.h"
#include <avr/pgmspace.h>
#include <stdio.h>

void state_changer(uint8_t* stateChange, STATE* STATE_HANDLER) {
	/*
		Change state if stateChange is true
		Set stateChange back to 0 when done
	*/
	if (*stateChange == 1) {
		if (*STATE_HANDLER == PULSE) {
			*STATE_HANDLER = POTENTIOMETER;
		}
		else if (*STATE_HANDLER == POTENTIOMETER) {
			*STATE_HANDLER = BLINK;
		}
		else if (*STATE_HANDLER == BLINK) {
			*STATE_HANDLER = OFF;
		}
		else if (*STATE_HANDLER == OFF) {
			*STATE_HANDLER = PULSE;
		}
		*stateChange = 0;
	}
}

void state_action(STATE STATE_HANDLER, uint8_t* direction,
					uint8_t* pwmValue, uint8_t adcValue, uint8_t* counter) {
	/*
		Action based on current state

		PULSE:
			Reenable OCR0A with COM0A1 bit set to 0 in TCCR0A register
			Run simple_ramp function

		POTENTIOMETER:
			Setting ADSC bit in ADCSRA register triggers single conversion of the ADC
			timer_toggleOC0A function turns led off by disabling OCR0A pin if the adcValue is 0
			OCR0A is set to adcValue to update duty cycle/brightness of LED

		BLINK:
			By counting up to 100 I acheive a 1 Hz blinking effect
			The LED is set to max with OCR0A since it might be low from previous potentiometer state
			OCR0A pin is toggled with COM0A1 bit in TCCR0A register

		OFF:
			OCR0A pin is disabled by setting COM0A1 bit in TCCR0A register to 0
			direction and pwmValue is changed so next state PULSE starts from low LED brightness to high
	*/
	if (STATE_HANDLER == PULSE) {
		TCCR0A |= (1 << COM0A1);
		simple_ramp(direction, pwmValue);
	}
	else if (STATE_HANDLER == POTENTIOMETER) {

		ADCSRA |= (1 << ADSC);
		timer_toggleOc0a(adcValue);
		OCR0A = adcValue;
	}
	else if (STATE_HANDLER == BLINK) {
		if (*counter == 100) {
			OCR0A = 255;
			TCCR0A ^= (1 << COM0A1);
			*counter = 0;
		}
		else {
			*counter += 1;
		}
	}
	else if (STATE_HANDLER == OFF) {
		TCCR0A &= ~(1 << COM0A1);
		*direction = -1;
		*pwmValue = 0;
		
	}

}
