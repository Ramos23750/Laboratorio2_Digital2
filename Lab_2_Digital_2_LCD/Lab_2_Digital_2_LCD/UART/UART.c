/*
 * UART.c
 *
 * Created: 2/1/2026 12:51:12 PM
 *  Author: diegu
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "UART.h"
void init_UART(void)
{
	UCSR0A = 0;
	UCSR0B |= (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0 = 103;
}
void wchar(char carac)
{
	while (!((UCSR0A & (1 << UDRE0))));
	UDR0 = carac;
}
void wstring(char* massaje){
	for (uint8_t i =0; massaje[i] != '\0';i++)
	{
		wchar(massaje[i]);
	}
}