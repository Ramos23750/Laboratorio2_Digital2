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
//Funcion para inicializar el LCD
void init8bits(void){
	//configuramos los puertos que vamos a utilizar como salida
	//configuramos el puerto D
	DDRD |= (1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7);
	//apagamos todos esos pines
	PORTD &= ~((1<<PORTD2)|(1<<PORTD3)|(1<<PORTD4)|(1<<PORTD5)|(1<<PORTD6)|(1<<PORTD7));
	//Configuracion de pines en el puerto B
	DDRB |= (1<<DDB0) | (1<<DDB1);
	//apagamos dichos puertos
	PORTB &= ~((1<<PORTB0) | (1<<PORTB1));
	//Configuramos el puerto C
	DDRC |= (1<<DDC0) | (1<<DDC1) | (1<<DDC2);
	//Apagamos esos pines
	PORTC &= ~((1<<PORTC0) | (1<<PORTC1) | (1<<PORTC2));
	//inicializamos todos los bits en 0
	LCDPORT(0X00);
	_delay_ms(20); //Hacemos pausa de 20 ms que le toma al display funcionar
	LCDCMD(0x30);
	_delay_ms(5);
	LCDCMD(0x30);
	_delay_ms(5);
	LCDCMD(0X30);
	_delay_ms(1);
	//FUNCTION SET
	LCDCMD(0x38);
	LCDCMD(0x08);
	LCDCMD(0x01);
	LCDCMD(0x06);
	LCDCMD(0x0C);
}
void LCDCMD(char a){
	//ponemos en RS en 0 para hacer que lo reconosca como un comando
	PORTC &= ~(1<<PORTC0);
	//mandamos al puerto
	LCDPORT(a);
	//Activamos EN
	PORTC |= (1<<PORTC2);
	_delay_ms(4);
	//Desactivamos EN
	PORTC &= ~(1<<PORTC2);
}
void LCDPORT(char a){
	if (a & (1 << 0))
	{
		PORTD |= (1<<PORTD2);
	} 
	else
	{
		PORTD &= ~(1<<PORTD2);
	}
	if (a & (1 << 1))
	{
		PORTD |= (1<<PORTD3);
	}
	else
	{
		PORTD &= ~(1<<PORTD3);
	}
	if (a & (1 << 2))
	{
		PORTD |= (1<<PORTD4);
	}
	else
	{
		PORTD &= ~(1<<PORTD4);
	}
	if (a & (1 << 3))
	{
		PORTD |= (1<<PORTD5);
	}
	else
	{
		PORTD &= ~(1<<PORTD5);
	}
	if (a & (1 << 4))
	{
		PORTD |= (1<<PORTD6);
	}
	else
	{
		PORTD &= ~(1<<PORTD6);
	}
	if (a & (1 << 5))
	{
		PORTD |= (1<<PORTD7);
	}
	else
	{
		PORTD &= ~(1<<PORTD7);
	}
	if (a & (1 << 6))
	{
		PORTB |= (1<<PORTB0);
	}
	else
	{
		PORTB &= ~(1<<PORTB2);
	}
	if (a & (1 << 6))
	{
		PORTB |= (1<<PORTB0);
	}
	else
	{
		PORTB &= ~(1<<PORTD2);
	}
	
}
void LCD_WRITE_CHAR(char c){
	//Ponemos RS en 1 para poder mandar un dato
	PORTC |= (1<<PORTC0);
	LCDPORT(c);
	//Hacemos la transicion del enable
	PORTC |= (1<<PORTC2);
	_delay_ms(4);
	PORTC &= ~(1<<PORTC2);
}
//Funcion para enviar una cadena
void LCD_WRITE_STRING(char *a){
	int i;
	for(i=0; a[i] != '\0'; i++)
	{
		LCD_WRITE_CHAR(a[i]);
	}
}
//establecer cursor del caracter
void LCD_SET_CURSOR(char c, char f){
	char temp;
	if(f == 1){
		temp = 0x80 + c - 1;
		LCDCMD(temp);
	}
	else if(f == 2){
		temp = 0xC0 + c - 1;
		LCDCMD(temp);
	}
}
//desplazamiento a la derecha
void LCD_SHIFT_RIGHT(void){
	LCDCMD(0X1C);
}
//desplazamiento a la izquierda
void LCD_SHIFT_LEFT(void){
	LCDCMD(0X18);
}