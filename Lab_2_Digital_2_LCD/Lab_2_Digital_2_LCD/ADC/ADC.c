/*
 * ADC.c
 *
 * Created: 1/27/2026 3:48:32 PM
 *  Author: diegu
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

void init_ADC()
{
	cli();
	ADMUX = 0;
	ADMUX |= (1 << REFS0) | (1 << ADLAR);
	ADMUX |= (1 << MUX1); // ADC2
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); 
	ADCSRA |= (1 << ADIE) | (1 << ADEN) | (1 << ADSC); 
	sei();
}