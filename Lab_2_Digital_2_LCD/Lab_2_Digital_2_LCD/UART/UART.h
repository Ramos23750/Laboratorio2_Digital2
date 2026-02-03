/*
 * UART.h
 *
 * Created: 2/2/2026 12:51:00 PM
 *  Author: diegu
 */ 

//#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#ifndef UART_H_
#define UART_H_


void init_UART(void);
void wstring(char* massaje);
void wchar(char carac);


#endif /* UART_H_ */