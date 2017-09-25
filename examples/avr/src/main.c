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


#include "uart.h"
#include "avrsimul.h"
#include "def_util.h"

//#define DEBUGPRINT
#define DEBUGALL
//#define NO_DEBUG_COLOR

#include "def.h"

// Macros -----------------------------------------------------------------

#define PROGNAME "avrtest"
#define VERSION  "0.1"
#define UART_BAUD_RATE 57600

// Variables --------------------------------------------------------------
static FILE mystdout = FDEV_SETUP_STREAM(simul_putchar, NULL, _FDEV_SETUP_WRITE);
//static FILE mystdout = FDEV_SETUP_STREAM(uart_putc, uart_getc, _FDEV_SETUP_WRITE);

volatile int timer2_ticks = 0;


const I2S numbersDb[] PROGMEM = {
	{ 1, "First"  },
	{ 2, "Second" },
	{ 3, "Third"  },
	{ 4, "Last"   },
	{ I2S_END     },
};



// Prototypes -------------------------------------------------------------
void hw_init(void);

// Code -------------------------------------------------------------------

/* Every ~ms */
ISR(TIMER2_COMPA_vect) {
	   timer2_ticks++;
}


int timer3 = 0;
ISR(TIMER0_COMPA_vect) {
	TIMER0_RELOAD(0);
	timer3++;
	
	if (timer3>=100) {
		timer3 = 0;
	}
}






void hw_init(void) {
	//wdt_disable();                            // disable watchdog timer
	stdout = &mystdout;                       // configure stdout to UART 0
	
	ARD_LED_INIT();
	ARD_LED_ON();
	
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));      // init uart
	
	// Timer 0
	TIMER0_CLK_PRES_1024();  // set prescaler to 1/1024
	TIMER0_OCA_IE();         // enable output compare A interrupt
	TIMER0_OCA_SET(156);
	
	
//	timer2_ticks = 0;
	/* Set up our timers and enable interrupts */
	//TCNT2 = 0;    /* Timer 1 by CLK/64 */
	OCR2A = 115;   /* ~1ms */
	TIMSK2 = _BV(OCIE2A);
	TCCR2B |= (1 << CS11) | (1 << CS10) ; 
	
	
	sei();  // enable all interrupts
}

int kalle(int a, char b);

void printSysInfo(void) {
	defprintf("File:       "__FILE__"\n");
	defprintf("Build:      "__DATE__"  "__TIME__"\n");
	defprintf("C Standard: "STRINGIZE(__STDC_VERSION__)"\n");
#ifdef __GNUC__
	defprintf("GNU C ver:  "__GNUC_VERSION__"\n");
#endif
	defprintf("Byteorder:  "STRINGIZE(__BYTE_ORDER)"\n");
}

void printResetInfo(void)  {
	if (IS_POWER_ON_RESET()) {  
		printf_P(PSTR("Power on reset\n"));
	}
	if (IS_BROWN_OUT_RESET()) {  
		printf_P(PSTR("Brown out reset\n"));
	}
	if (IS_WATCH_DOG_RESET() ) {  
		printf_P(PSTR("Watchdog reset\n"));
	}
	if (IS_EXTERNAL_RESET()) {  
		printf_P(PSTR("External reset\n"));
	}
	CLEAR_RESETS();
	
}


int main(void) {
	volatile int tmp;
	
	hw_init();
	
	printf_P(PSTR("\n\n\nMakeplate AVR example\n\n"));
	printSysInfo();
	defprintf("\n");
	printResetInfo();
	defprintf("\n");
	
	INFOPRINT("Info\n");
	DEBUGPRINT("Debug\n");
	WARNINGPRINT("Warning\n");
	ERRORPRINT("Error\n");
	FATALPRINT("Fatal\n");
	
	while (1) {
		tmp = timer2_ticks;
		printf_P(PSTR("Timer counter %-5d %-3d  Timer0: %4d\n"), tmp, TCNT2, timer3);
//		printf("Input char %c\n", simul_getchar());
		_delay_ms(100);
		ARD_LED_TOGGLE();
	}

  return 0;
}
