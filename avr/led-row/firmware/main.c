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
    DDRB |= 1 << PINB0;
    DDRB |= 1 << PINB1;
    DDRB |= 1 << PINB2;

    PORTB &= ~(1 << PINB0);
    PORTB &= ~(1 << PINB1);
    PORTB &= ~(1 << PINB2);

    for(;;){
        PORTB ^= 1 << PINB0;
        _delay_ms(2000);
        PORTB ^= 1 << PINB0;
        PORTB ^= 1 << PINB1;
        _delay_ms(2000);
        PORTB ^= 1 << PINB1;
        PORTB ^= 1 << PINB2;
        _delay_ms(2000);
        PORTB ^= 1 << PINB2;
    }
    return 0;   /* never reached */
}
