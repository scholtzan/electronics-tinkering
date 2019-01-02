/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#define F_CPU 100000UL
#include <util/delay.h>

const unsigned char numbers[10] = {
    0b01111011,
    0b01100000,
    0b00110111,
    0b01110110,
    0b01101100,
    0b01011110,
    0b01011111,
    0b01110000,
    0b01111111,
    0b01111110
};

int button_is_pressed(int pin) {
    if (bit_is_clear(PIND, pin)) {
        _delay_ms(100);

        if (bit_is_clear(PIND, pin)) return 1;
    }

    return 0;
}

int main(void)
{
    DDRB = 0b11111111;
    DDRD = 0b00000000;

    PORTB = 0b00000000;
    PORTD = 0b11111111;

    int curNum = 0;
    PORTB = ~(numbers[curNum]);

    for(;;){
        curNum = 0;

        if (button_is_pressed(5)) {
            curNum += 4;
        }

        if (button_is_pressed(4)) {
            curNum += 2;
        }

        if (button_is_pressed(3)) {
            curNum += 1;
        }

        PORTB = ~(numbers[curNum]);
    }
    return 0;   /* never reached */
}
