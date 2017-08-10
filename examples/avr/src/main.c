/**
 *---------------------------------------------------------------------------
 * @brief   Makeplates main example file.
 *
 * @file    main.c
 * @author  Peter Malmberg <peter.malmberg@gmail.com>
 * @date    2016-10-24
 * @license GPLv2
 *
 *---------------------------------------------------------------------------
 */

// Includes ---------------------------------------------------------------

#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
	
#include "def.h"
#include "def_avr.h"
#include "uart.h"
#include "avrsimul.h"

// Macros -----------------------------------------------------------------

#define PROGNAME "makeplate"
#define VERSION  "0.1"
#define UART_BAUD_RATE 57600

// Variables --------------------------------------------------------------
// static FILE mystdout = FDEV_SETUP_STREAM(simul_putchar, NULL, _FDEV_SETUP_WRITE);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putc, uart_getc, _FDEV_SETUP_WRITE);

volatile int timer2_ticks;


// Prototypes -------------------------------------------------------------
void hw_init(void);

// Code -------------------------------------------------------------------

/* Every ~ms */
ISR(TIMER2_COMPA_vect) {
	   timer2_ticks++;
}

void hw_init(void) {
	//wdt_disable();                            // disable watchdog timer
	stdout = &mystdout;                       // configure stdout to UART 0
	
	ARD_LED_INIT();
	ARD_LED_ON();
	
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));      // init uart
	
	timer2_ticks = 0;
	/* Set up our timers and enable interrupts */
	TCNT2 = 0;    /* Timer 1 by CLK/64 */
	OCR2A = 115;   /* ~1ms */
	TIMSK2 = _BV(OCIE2A);
	TCCR2B |= (1 << CS11) | (1 << CS10) ; 
	sei();
}

int kalle(int a, char b);

void printColor(char *str, char *color) {
	printf("%s%-15s Example text and chars #/-_+!@$%%&{}() %s\n", color, str, E_END);
}
void printColor2(char *str, char *color, char *bg) {
	printf("%s%s%-15s Example text and chars #/-_+!@$%%&{}() %s\n", bg, color, str, E_END);
}

char *bgColors[] = {E_ON_WHITE, E_ON_YELLOW,E_ON_RED, E_ON_BLUE, E_ON_GREEN, E_ON_CYAN, E_ON_MAGENTA,  NULL};
char *fgColors[] = {E_WHITE, E_RED, E_BR_RED, E_BLUE, E_BR_BLUE, E_GREEN, E_BR_GREEN,
                    E_MAGENTA, E_BR_MAGENTA, E_CYAN, E_BR_CYAN, E_YELLOW, E_BR_YELLOW, NULL };

void printColors(void) {
	int i;
	
	printf("\n\n");
	printf("Normal text\n");
	printf(E_ATTR_BOLD "Bold text\n" E_END);
	printf(E_ATTR_BLINK "Blink text\n" E_END);
	printf(E_ATTR_LOWI "Low intensity text\n" E_END);
	printf(E_ATTR_REVERSE "Reverse text\n" E_END);
	printf(E_ATTR_UNDERLINE "Underline text\n" E_END);	
	printf("\n\n");
	
	printColor("Green",          E_GREEN);
	printColor("Bright Green",   E_BR_GREEN);
	printColor("Red",            E_RED);
	printColor("Bright Red",     E_BR_RED);
	printColor("Blue",           E_BLUE);
	printColor("Bright Blue",    E_BR_BLUE);
	printColor("Cyan",           E_CYAN);
	printColor("Bright Cyan",    E_BR_CYAN);
	printColor("Magenta",        E_MAGENTA);
	printColor("Bright Magenta", E_BR_MAGENTA);
	printColor("Gray",           E_GRAY);
	printColor("Dark Gray",      E_DARKGRAY);
	printColor("Yellow",         E_YELLOW);
	printColor("Bright Yellow",  E_BR_YELLOW);
	printColor("White",          E_WHITE);
	
	i = 0;
	while (bgColors[i]!=NULL) {
		printColor2("", E_WHITE, bgColors[i] );
		i++;
	}
}

int getCh() {
	int ch;
	
	while (1) {
		ch = uart_getc();
		if (ch != 0x100) {
			return ch;
		}
		_delay_ms(10);
	}
}

void waitKeyPressed() {
	getCh();
}

int keyPressed() {
	int ch;
	ch = uart_getc();
	if (ch != 0x100) {
			return 1;
	}
	return 0;
}

void uart_clear(void) {
  int ch;
	while (1) {
		ch = uart_getc();
		if (ch == 0x100) 
			return;
	}
	
}

void printData(void) {
	uint32_t x;
	x = 0;
	uart_clear();
	while (1) {
		printf("Printing a counter: %-10d\n",x);
		if (keyPressed())
				return;
		
		x++;
	}
}


int main(void) {
	volatile int tmp;
	int ch;
	int counter = 0;
	
	hw_init();
	
	printf("Makeplate AVR example\n");
	
	
	while (1) {
		printf("Press a key 1-4\n");
		
		ch = getCh();
		switch (ch) {
		 case '1': printColors(); break;
		 case '2': printData(); break;
		 case '3': break;
		 case '4': break;
			
		 default:break;
		}
	}
	
//	printColors();
	
	while (1) {
		tmp = timer2_ticks;
//		printf("Timer counter %d\n", tmp);
		printf("Counter %-6d\n", counter);
		
		ch = uart_getc();
		if (ch!= 0x100) {
//			printf("CH = %x\n", ch);
			printf("%c", ch);
		}
		_delay_ms(200);
		ARD_LED_TOGGLE();
		
		counter++;
	}

  return 0;
}
