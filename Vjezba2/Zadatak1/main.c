#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char t0_cnt = 0;


ISR(TIMER0_COMPA_vect)
{
	t0_cnt++;

	if(t0_cnt == 125)
	{
		t0_cnt = 0;
		PORTB ^= 1 << 5;
	}

}


int main()
{
	DDRB |= 1 << 5; //PB5 je izlaz
	PORTB |= 1 << 5;

	TCCR0A = 0x02; //tajmer 0: CTC mod
	TCCR0B = 0x04; //tajmer 0: fclk = fosc/256
	 OCR0A = 124;

	TIMSK0 = 0x02; //dozvola prekida tajmera 0

	sei(); //I = 1 (dozvola prekida)

	while (1);

	return 0;
}

