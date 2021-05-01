#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long millis=0, t0=0;
unsigned char fi=0;

ISR(TIMER0_COMPA_vect)
{
	millis++;
	t0++;

	if(t0 % 781 == 0) fi++;
	if(t0  == 200000) {
		t0=0;
		fi=0;
	}

	if(millis == 256) millis=0;

	if(millis < fi)
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
