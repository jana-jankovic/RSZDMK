/**
 * @file main.c
 * @brief Aplikacija koja implementira ogranicen broj treptanja diode
 * @author Ime Prezime
 * @date 14-03-2021
 * @version 1.0
 */
#include "timer0.h"
#include "pin.h"
#include "pulsing.h"

/// Makro za selektovanje pina na koji je povezana dioda
#define DIODE_PIN 5

/// Makro za podesavanje periode u brzom rezimu treptanja
#define FAST 200
/// Makro za podesavanje periode u sporom rezimu treptanja
#define SLOW 1000

/// Makro za podesavanje broja brzih treptaja
#define FAST_REPETITIONS 15
/// Makro za podesavanje broja sporih treptaja
#define SLOW_REPETITIONS 3

/**
 * main - funkcija koja implementiran glavni deo aplikacije
 * @return Nema povratnu vrednost
 */
int main()
{
	// Inicijalizacija
    pinInit(PORT_B, DIODE_PIN, OUTPUT);
    timer0InteruptInit();

    // Glavna petlja
    while (1)
    {
        // Brzo treptanje
    	pinPulsing(PORT_B, DIODE_PIN, FAST, FAST_REPETITIONS);

    	// Sporo treptanje
		pinPulsing(PORT_B, DIODE_PIN, SLOW, SLOW_REPETITIONS);

        // Kraj
        while (1)
        ;

    }

    return 0;
}
