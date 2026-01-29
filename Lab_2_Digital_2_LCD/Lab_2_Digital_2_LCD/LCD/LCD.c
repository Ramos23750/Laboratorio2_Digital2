/*
 * LCD.c
 *
 * Created: 1/27/2026 3:50:53 PM
 *  Author: diegu
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "LCD.h"

void inicializar_LCD_8bits()
{	
	//bits de salida del lcd
	DDRD |= (1 << DDD2) | (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7); //PD2 a PD7
	DDRC |= (1 << DDC0) | (1 << DDC1); //PINC0 y PINC1
	DDRB |= (1 << DDB0) | (1 << DDB1); //E y RS
	PORTB &= ~((1 << PORTB0) | (1 << PORTB1));
	PORTD &= ~((1 << DDD2) | (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7));
	PORTC &= ~((1 << DDC0) | (1 << DDC1));
	//Power on
	_delay_ms(20);
	LCD_PORT(0x30);
	_delay_ms(5);
	LCD_PORT(0x30);
	_delay_ms(1);
	LCD_PORT(0x30);
	_delay_ms(20);
	LCD_PORT(0x38); //function set
	_delay_ms(1);
	LCD_PORT(0x0C); //Display on/off
	_delay_ms(1);
	LCD_PORT(0x06); //Entry mode
	_delay_ms(1);
	LCD_PORT(0x01); //Clear display
	
}
void LCD_PORT(uint8_t a)
{
	//D0
	if (a & 1)
	PORTC |= (1 << PORTC0);
	else
	PORTC &= ~(1 << PORTC0);
	//D1
	if (a & 2)
	PORTC |= (1 << PORTC1);
	else
	PORTC &= ~(1 << PORTC1);
	//D2
	if (a & 4)
	PORTD |= (1 << PORTD2);
	else
	PORTD &= ~(1 << PORTD2);
	//D3
	if (a & 8)
	PORTD |= (1 << PORTD3);
	else
	PORTD &= ~(1 << PORTD3);
	//D4
	if (a & 16)
	PORTD |= (1 << PORTD4);
	else
	PORTD &= ~(1 << PORTD4);
	//D5
	if (a & 32)
	PORTD |= (1 << PORTD5);
	else
	PORTD &= ~(1 << PORTD5);
	//D6
	if (a & 64)
	PORTD |= (1 << PORTD6);
	else
	PORTD &= ~(1 << PORTD6);
	//D7
	if (a & 128)
	PORTD |= (1 << PORTD7);
	else
	PORTD &= ~(1 << PORTD7);
}
void LCD_CMD(char a)
{
	PORTB &= ~(1 << PORTB1);
	LCD_PORT(a);
	PORTB |= (1 << PORTB1);
	_delay_ms(4);
	PORTB &= ~(1 << PORTB1);
}

void LCD_write_char(char c)
{
	//char CD, CC;
	//CD = c & 0x3F;
	//CC = (c & 0xC0) >> 6;
	//RS => 1
	PORTB |= (1 << PORTB0);
	LCD_PORT(c);
	PORTB |= (1 << PORTB1);
	_delay_ms(4);
	PORTB &= ~(1 << PORTB1);
	
	
	
}

void LCD_write_string(char *a)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		LCD_write_char(a[i]);
	}
}

void LCD_set_cursor(char c, char f)
{
	char temp;
	if (f == 1)
	{
		temp = 0x80 + c - 1;
		LCD_CMD(temp);
	}
	else if (f == 2)
	{
		temp = 0xC0 + c - 1;
		LCD_CMD(temp);
	}
}