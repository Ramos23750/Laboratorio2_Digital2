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
/********************  Function Prototype *****************************/

/********************** Main Loop ***************************/
int main(void)
{
	init8bits();
	LCD_SET_CURSOR(1,1);
	
	while (1)
	{
		
	}
}

/******************* Non-interrupt functions ******************************/



/******************** Interrupt functions ****************************/

///////////////////////////Pruebas
