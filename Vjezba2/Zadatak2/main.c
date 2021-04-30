#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long millis=0;

ISR(TIMER0_COMPA_vect)
{
	millis++;
}

int main()
{
	DDRB |= 1 << 4;

	TCCR0A = 0x02;
	TCCR0B = 0x01;
	OCR0A = 159;
	TIMSK0 = 0x02;

	sei();

	while(1);

	return 0;
}
