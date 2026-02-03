/*///////////////////////////////////////////////////
 * Nombre de archivo: Lab_2_Digital_2_LCD.c
 *
 * Created: 1/27/2026 12:02:02 PM
 * Author : Diego Alejandro Ramos Rodas
 * Curso: Electronica Digital 2
 * Actividad: Laboratorio no.2 
 */////////////////////////////////////////////////// 

/*********************** Librerias **************************/
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "LCD/LCD.h"
#include "ADC/ADC.h"
#include "UART/UART.h"
/********************* Variables ****************************/
float pot1,pot2; //Variables donde se guardaran los valores 
uint8_t adc_value;
uint16_t conv1,conv2;
uint8_t alternador;
char buff1[7], buff2[7];
/********************  Function Prototype *****************************/
/********************** Main Loop ***************************/
int main(void)
{
	init_ADC();
	init8bits();
	LCD_SET_CURSOR(2,1);
	LCD_WRITE_STRING("S1:");
	LCD_SET_CURSOR(8,1);
	LCD_WRITE_STRING("S2:");
	LCD_SET_CURSOR(14,1);
	LCD_WRITE_STRING("S3:");
	LCD_SET_CURSOR(13,2);
	LCD_WRITE_STRING("C: ");
	
	while (1)
	{
		ADCSRA |= (1 << ADSC);						
		LCD_SET_CURSOR(1,2);
		LCD_WRITE_STRING(buff1);														
		LCD_SET_CURSOR(7,2);
		LCD_WRITE_STRING(buff2);															
	}
}


/******************** Interrupt functions ****************************/
ISR(ADC_vect)
{
	adc_value = ADCH;
	switch(alternador)
	{
		case 0:
		pot1 = adc_value;
		conv1 = (pot1 * 5000 / 255);
		snprintf(buff1, sizeof(buff1), "%u.%02uV", conv1/1000, (conv1 % 1000) / 10);
		ADMUX = 0;
		ADMUX |= (1 << REFS0);												
		ADMUX |= (1 << ADLAR);												
		ADMUX |= (1 << MUX1);	
		alternador = 1;										
		break;
		
		case 1:
		pot2 = adc_value;
		conv2 = (pot2 * 5000 / 255);
		snprintf(buff2, sizeof(buff2), "%u.%02uV", conv2/1000, (conv2 % 1000) / 10);
		ADMUX = 0;
		ADMUX |= (1 << REFS0);										
		ADMUX |= (1 << ADLAR);												
		ADMUX |= (1 << MUX0);
		alternador = 0;												
		break;
		default:
		break;
	}
}
