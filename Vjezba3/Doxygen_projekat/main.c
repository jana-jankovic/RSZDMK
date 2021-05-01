/**
 * @file main.c
 * @brief Aplikacija koja implementira ogranicen broj treptaja diode
 * @author Jana Jankovic
 * @date 16-03-2021
 * @version 1.0
 */
#include <avr/io.h>
#include <avr/interrupt.h>

///Makro za podesavanje visoke vrijednosti signala
#define HIGH 1
///Makro za podesavanje niske vrijednosti signala
#define LOW 0

#define OUTPUT 1
#define INPUT 0

#define PORT_B 0
#define PORT_C 1
#define PORT_D 2

#define DIODE_PIN 5

#define FAST 1000
#define SLOW 5000

#define FAST_REPETITIONS 8
#define SLOW_REPETITIONS 5

///Broj milisekundi od pocetka izvrsavanja programa
volatile unsigned long ms = 0;

/**
 * pinPulse - Funkcija koja implementiran podizanje i spustanje vrednosti na pinu odgovarajucom brzinom
 * @param port - ulaz tipa unsigned char - Port na kojem je potrebno implementirati funkcionalnost
 * @param pin - ulaz tipa unsigned char - Pin na kojem je potrebno implementirati funkcionalnost
 * @param period - ulaz tipa unsigned long - Perioda promene vrednosti na pinu
 * @return Nema povratnu vrednost
 */
void pinPulse(unsigned char port, unsigned char pin, unsigned long period);
void pinPulsing(unsigned char port, unsigned char pin, unsigned long period, unsigned char num_of_repetitions);
void pinSetValue(unsigned char port, unsigned char pin, unsigned char value);
void pinInit(unsigned char port, unsigned char pin, unsigned char direction);

unsigned long timer0DelayMs(unsigned long delay_length);
void timer0InteruptInit();

unsigned long calculateHalfPeriod(unsigned long period);

int main()
{
	unsigned long period = 1000; // Period jednog treptaja
	unsigned char repetitions = 5; // Broj treptaja
	int 		  i;

	// Inicijalizacija
	pinInit(PORT_B, DIODE_PIN, OUTPUT);
	timer0InteruptInit();

	// Glavna petlja
	while (1)
	{

		pinPulsing(PORT_B, DIODE_PIN, FAST, FAST_REPETITIONS);
		pinPulsing(PORT_B, DIODE_PIN, SLOW, SLOW_REPETITIONS);
	}
	return 0;
}

/******************************************************************************************/

void pinPulsing(unsigned char port, unsigned char pin, unsigned long period, unsigned char num_of_repetitions)
{
	for (int i = 0; i < num_of_repetitions; i++)
	{
		pinPulse(port, pin, period);
	}

}

/******************************************************************************************/

void pinPulse(unsigned char port, unsigned char pin, unsigned long period)
{
	// Poluperioda u kojoj pin ima visoku vrednost
	pinSetValue(port, pin, HIGH);
	timer0DelayMs(calculateHalfPeriod(period));

	// Poluperioda u kojoj pin ima nisku vrednost
	pinSetValue(port, pin, LOW);
	timer0DelayMs(calculateHalfPeriod(period));
}

/******************************************************************************************/

void pinSetValue(unsigned char port, unsigned char pin, unsigned char value)
{
	// Postavljanje vrednosti pina
	switch (port)
	{
	case PORT_B:
		if (value == HIGH)
			PORTB |= 1 << pin;
		else
			PORTB &= ~(1 << pin);
		break;
	case PORT_C:
		if (value == HIGH)
			PORTC |= 1 << pin;
		else
			PORTC &= ~(1 << pin);
		break;
	case PORT_D:
		if (value == HIGH)
			PORTD |= 1 << pin;
		else
			PORTD &= ~(1 << pin);
		break;
	default:
		break;
	}
}

/******************************************************************************************/

void pinInit(unsigned char port, unsigned char pin, unsigned char direction)
{
	// Inicijalizacija smera pina
	switch (port)
	{
	case PORT_B:
		if (direction == OUTPUT)
			DDRB |= 1 << pin;
		else
			DDRB &= ~(1 << pin);
		break;
	case PORT_C:
		if (direction == OUTPUT)
			DDRC |= 1 << pin;
		else
			DDRC &= ~(1 << pin);
		break;
	case PORT_D:
		if (direction == OUTPUT)
			DDRD |= 1 << pin;
		else
			DDRD &= ~(1 << pin);
		break;
	default:
		break;
	}
}

/******************************************************************************************/

unsigned long calculateHalfPeriod(unsigned long period)
{
	return (period/2);
}

/******************************************************************************************/

unsigned long timer0DelayMs(unsigned long delay_length)
{
	unsigned long t0; // Trenutak pocevsi od kog se racuna pauza

	// Implementacija pauze
	t0 = ms;
	while ((ms - t0) < delay_length)
		; // Pauza delay_length milisekundi

	return ms;
}
/******************************************************************************************/

void timer0InteruptInit()
{
	// Inicijalizacija tajmera 0 tako da perioda prekida bude 1ms
	TCCR0A = 0x02;
	TCCR0B = 0x03;
	OCR0A = 249;
	TIMSK0 = 0x02;

	// Podesavanje globalne dozvole prekida
	sei();
}

/******************************************************************************************/

ISR(TIMER0_COMPA_vect)
{
	// Inkrementovanje broja milisekundi koje su prosle od pokretanja aplikacije
	ms++;
}

