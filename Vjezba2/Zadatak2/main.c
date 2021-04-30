#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long millis=0;
unsigned char fi=50;

ISR(TIMER0_COMPA_vect)
{
	millis++;

	if(millis == 256) millis=0;

	if(millis < 250)
		PORTB |= 1 << 5;
	else
	{
		PORTB &= ~(1 << 5);
	}
}

int main()
{
	DDRB |= 1 << 5;

	TCCR0A = 0x02;
	TCCR0B = 0x01;
	OCR0A = 159;
	TIMSK0 = 0x02;

	sei();

	while(1);

	return 0;
}
