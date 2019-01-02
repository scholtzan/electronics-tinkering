#include <avr/io.h>           //Required to use assembler commands
#define F_CPU 1000000UL
#include <util/delay.h>


 
int main()
{
 
DDRB = 0b00000001; //Data Direction Register setting pin0 to output and the remaining pins as input
PORTB = 0b00000001; //Set pin0 to 5 volts
while(1)
{
PORTB = 0b00000001; //Set pin0 to 5 volts
_delay_ms(700);
PORTB = 0b00000000; //Set pin0 to 5 volts
_delay_ms(700);
}
 
    return 0;
}