/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#define F_CPU 8000000UL 
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 9800UL      // Baudrate
 
// Berechnungen
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.



int main(void)
{
    DDRB = 0b11111111;
    PORTB = 0b00000000;
    UBRRH = UBRR_VAL >> 8;      // Wichtig! UBRRH vor UBRRL setzten!
    UBRRL = UBRR_VAL & 0xFF;
    
    // #if USE_2X
    // /* U2X-Modus erforderlich */
    // UCSRA |= (1 << U2X);
    // #else
    // /* U2X-Modus nicht erforderlich */
    // UCSRA &= ~(1 << U2X);
    // #endif
    
    UCSRB |= (1<<TXEN) | (1<<RXEN); // UART TX einschalten - UART RX einschalten
    
    UCSRC |= (1<<UCSZ1) | (1<<UCSZ0);   // Asynchron 8N1
    /* insert your hardware initialization here */
 
    sei();

    _delay_ms(10);
    int isOne = 0;
    PORTB = 0b00000111;

    for(;;){
        // while (!(UCSRA & (1<<UDRE))) { }    // warten bis Senden möglich ist
    

        // UDR = 'p';
        while (!(UCSRA & (1<<RXC)))   // warten bis Zeichen verfuegbar
        ;
        int c = UDR;

        if (c == '1' || isOne == 1) {
            PORTB = 0b00000000;
            isOne = 1;
            _delay_ms(100);
        }
        
        if (c == '0' || isOne == 0) {
            PORTB = 0b00000111;
            isOne = 0;
        }
        
    }
    return 0;   /* never reached */
}
