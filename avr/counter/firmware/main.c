/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>

int main(void)
{
    DDRB = 0b01111111;
    PORTB = 0b00000000;
    TCCR1B |= 1<<CS10 | 1<<CS11;
    int led = 0;

    for(;;){
        if (TCNT1 > 10000) {
            TCNT1 = 0;

            PORTB = 1 << led;
            led += 1;

            if (led > 6) {
                led = 0;
            }
        }
    }
    return 0;   /* never reached */
}
