/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int main(void)
{
    DDRB &= ~(1 << PINB1);
    DDRB |= 1 << PINB0;
    DDRB |= 1 << PINB2;
    PORTB ^= 1 << PINB0;
    PORTB |= 1 << PINB1;

    int triggered = 0;
    int currentPin = PINB0;

    for(;;){
        if (bit_is_clear(PINB, 1)) {
            if (!triggered) {
            PORTB ^= 1 << PINB0; //Toggle LED in pin 0
            PORTB ^= 1 << PINB2; //Toggle LED on pin 2
            }

            triggered = 1;
        }
        else {
            triggered = 0;
        }
    }
    return 0;
}
