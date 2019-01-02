/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#define F_CPU 100000UL
#include <util/delay.h>

int main(void)
{
    DDRB = 0b00000000;
    PORTB = 0b00000000;
    TCCR1B |= 1<<CS10 | 1<<CS11;

    float curStep = 1.0;
    int count = 0;
    int isUp = 0;
    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
        if (TCNT1 > 500 / curStep) {
            TCNT1 = 1;
            PORTB = 1 << PINB6;
            _delay_ms(100);
            PORTB = ~(1 << PINB6);

            count++;
        }

        if (count > 50) {
            if (curStep > 5.0)
                isUp = 0;
            else if (curStep < 1.0)
                isUp = 1;

            if (isUp)
                curStep += 0.1;
            else
                curStep -= 0.1;

            count = 0;
        }
    }
    return 0;   /* never reached */
}
