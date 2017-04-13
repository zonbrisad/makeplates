/**
 *---------------------------------------------------------------------------
 * @brief   Makeplates main example file.
 *
 * @file    main.c
 * @author  Peter Malmberg <peter.malmberg@gmail.com>
 * @date    2016-10-24
 * @licence GPLv2
 *
 *---------------------------------------------------------------------------
 */

// Includes ---------------------------------------------------------------
// 
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


int main(void) {
	volatile int tmp;
	
	hw_init();
	
	printf("Makeplate AVR example\n");
	
	while (1) {
		tmp = timer2_ticks;
		printf("Timer counter %d\n", tmp);
//		printf("Input char %c\n", simul_getchar());
		_delay_ms(100);
		ARD_LED_TOGGLE();
	}

  return 0;
}
