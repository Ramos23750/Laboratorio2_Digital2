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
#define RS PORTB0
#define EN PORTB1
void inicializar_LCD_8bits(void)
{
	//bits de salida del lcd
	DDRD |= (1 << DDD2) | (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7); //PD2 a PD7
	DDRC |= (1 << DDC0) | (1 << DDC1); //PD0 y PD1
	DDRB |= (1 << DDB0) | (1 << DDB1); //RS y E
	//DDRB |= (1 << DDC4); //E temporal
	PORTD &= ~((1 << PORTD2) | (1 << PORTD3) | (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7));
	PORTB &= ~((1 << PORTB0) | (1 << PORTB1));
	PORTC &= ~((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC4));
	//Power on
	//_delay_ms(20);
	//LCD_CMD(0x30);
	//_delay_ms(5);
	//LCD_CMD(0x30);
	//_delay_ms(5);
	//LCD_CMD(0x30);
	//_delay_ms(20);
	//LCD_CMD(0x38); //function set
	//_delay_ms(1);
	//LCD_CMD(0x08); //Display off
	//_delay_ms(1);
	//LCD_CMD(0x01); //Clear display
	//_delay_ms(2);
	//LCD_CMD(0x06); //Entry mode
	//LCD_CMD(0x0C); //Display on
	_delay_ms(20); 
	LCD_CMD_RAW(0x30);
	_delay_ms(5);
	LCD_CMD_RAW(0x30);
	_delay_us(120); 
	LCD_CMD_RAW(0x30);
	_delay_us(120);
	LCD_CMD(0x38);
	_delay_us(120);
	// Function set
	LCD_CMD(0x38);
	_delay_us(120);
	// Display OFF 
	LCD_CMD(0x08);
	_delay_us(120);
	// Clear display
	LCD_CMD(0x01);
	_delay_ms(2);
	// Entry mode
	LCD_CMD(0x06);
	// Display ON
	LCD_CMD(0x0C);
	_delay_ms(2);
	//test
	LCD_set_cursor(1,1);
	LCD_write_char('A');
	LCD_set_cursor(1,2);
	LCD_write_char('B');
	
}
void LCD_PORT(uint8_t a)
{
	uint8_t portd = PORTD & ~(
	(1 << PORTD2) |
	(1 << PORTD3) |
	(1 << PORTD4) |
	(1 << PORTD5) |
	(1 << PORTD6) |
	(1 << PORTD7)
	);

	uint8_t portc = PORTC & ~(
	(1 << PORTC0) |
	(1 << PORTC1)
	);

	if (a & 0x01) portc |= (1 << PORTC0);
	if (a & 0x02) portc |= (1 << PORTC1);

	if (a & 0x04) portd |= (1 << PORTD2);
	if (a & 0x08) portd |= (1 << PORTD3);
	if (a & 0x10) portd |= (1 << PORTD4);
	if (a & 0x20) portd |= (1 << PORTD5);
	if (a & 0x40) portd |= (1 << PORTD6);
	if (a & 0x80) portd |= (1 << PORTD7);

	PORTC = portc;
	PORTD = portd;  
}

void LCD_CMD(char a)
{
	PORTB &= ~(1 << RS); //RS -> 0
	LCD_PORT(a);
	_delay_us(2);
	PORTB |= (1 << EN); //En -> 1
	_delay_ms(4);
	PORTB &= ~(1 << EN); //En -> 0
	//_delay_ms(2);
}
void LCD_CMD_RAW(char a)
{
	// RS = 0
	PORTB &= ~(1 << RS);

	// SOLO escribir datos
	LCD_PORT(a);

	// Pulso E largo (modo power-up)
	PORTB |= (1 << EN);
	_delay_ms(5);
	PORTB &= ~(1 << EN);
}
void LCD_write_char(char c)
{
	//char CD, CC;
	//CD = c & 0x3F;
	//CC = (c &  0xC0) >> 6;
	//RS => 1
	PORTB |= (1 << RS); //RS --> 1
	LCD_PORT(c);
	_delay_us(2);
	PORTB |= (1 << EN);
	_delay_ms(4);
	PORTB &= ~(1 << EN);
	
	
	
}
void LCD_Shift_Right(void){
	LCD_CMD(0x01);
	LCD_CMD(0x0C);
}
//Desplazamiento a la izquierda
void LCD_Shift_Left(void){
	LCD_CMD(0x01);
	LCD_CMD(0x0C);
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