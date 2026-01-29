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
/********************* Variables ****************************/

/********************  Function Prototype *****************************/

/********************** Main Loop ***************************/
int main(void)
{

    while (1) 
    {
		inicializar_LCD_8bits();
		LCD_set_cursor(1,1);
		LCD_write_char('H');
		LCD_write_char('o');
		LCD_write_char('l');
		LCD_write_char('a');
		LCD_write_char('n');
		LCD_write_char('d');
		LCD_write_char('a');
    }
}

/******************* Non-interrupt functions ******************************/



/******************** Interrupt functions ****************************/

