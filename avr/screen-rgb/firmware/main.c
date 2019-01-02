#include <avr/io.h>
#define F_CPU 8000000UL 
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD 9800UL      // Baudrate
 
// Berechnungen
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.

int readNumber(int digits) {
    int num = 0;
    int i;

    for (i = 0; i < digits; i++) {
        num *= 10;
        while (!(UCSRA & (1<<RXC)));
        char c = UDR;
        num += c - '0';
    }

    return num;
}

int main(void)
{
    DDRB = 0b11111111;
    PORTB = 0b00000000;
    UBRRH = UBRR_VAL >> 8;  
    UBRRL = UBRR_VAL & 0xFF;
    
    UCSRB |= (1<<TXEN) | (1<<RXEN); // UART TX einschalten - UART RX einschalten
    
    UCSRC |= (1<<UCSZ1) | (1<<UCSZ0);   
 
    sei();

    _delay_ms(10);

    PORTB = 0b00000000;

    for(;;){
        int red = readNumber(3);
        int green = readNumber(3);
        int blue = readNumber(3);

        if (red > 0) {
            PORTB = 0b00000001;
            _delay_ms(100);
        }
        else
            PORTB = ~(1 << PIN0);
        
        if (green > 0) {
            PORTB = 0b00000010;
            _delay_ms(100);
        }
        else
            PORTB = ~(1 << PIN1);

        if (blue > 0) {
            PORTB = 0b00000100;
            _delay_ms(100);
        }
        else
            PORTB = ~(1 << PIN2);
        
    }
    return 0;   /* never reached */
}
