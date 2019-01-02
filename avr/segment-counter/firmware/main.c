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

int button_is_pressed_d(int pin)
{
        /* the button is pressed when BUTTON_BIT is clear */
        if (bit_is_clear(PIND, pin))
        {
                _delay_ms(100);
                if (bit_is_clear(PIND, pin)) return 1;
        }

        return 0;
}

int button_is_pressed_b(int pin)
{
        /* the button is pressed when BUTTON_BIT is clear */
        if (bit_is_clear(PINB, pin))
        {
                _delay_ms(100);
                if (bit_is_clear(PINB, pin)) return 1;
        }

        return 0;
}

int main(void)
{
    DDRB = 0b01111111;
    DDRD = 0b11011111;
    PORTB = 0b10000000;
    PORTD = 0b11111111;
    //TCCR1B |= 1<<CS10 | 1<<CS11;

    int curNum = 0;
    PORTB = numbers[curNum];

    /* insert your hardware initialization here */
    for(;;){
        //if (TCNT1 > 15000) {
        //    TCNT1 = 0;
        if (button_is_pressed_d(5)) {
            curNum -= 1;

            if (curNum < 0) {
                curNum = 9;
            }

            PORTB = numbers[curNum];

            while(button_is_pressed_d(5)) {
            }
        }

        if (button_is_pressed_b(7)) {
            curNum += 1;

            if (curNum > 9) {
                curNum = 0;
            }

            PORTB = numbers[curNum];

            while(button_is_pressed_b(7)) {

            }
        }





    }
    return 0;   /* never reached */
}
