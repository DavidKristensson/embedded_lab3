#ifndef _LED_H_
#define _LED_H_

#include <avr/io.h>

void led_init(void);

void simple_ramp(uint8_t* direction, uint8_t* pwmValue);

#endif // _LED_H_

