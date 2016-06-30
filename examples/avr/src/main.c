
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>


/* This port correponds to the "-W 0x20,-" command line option. */
#define special_output_port (*((volatile char *)0x20))

/* This port correponds to the "-R 0x22,-" command line option. */
#define special_input_port  (*((volatile char *)0x22))

static int uart_putchar(char c, FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

static int uart_putchar(char c, FILE *stream) {
	special_output_port = c;
	return 0;
}

volatile int timer2_ticks;

/* Every ~ms */
ISR(TIMER2_COMPA_vect) {
	   timer2_ticks++;
}

int main(void) {
	volatile int tmp;
	stdout = &mystdout;
	
	timer2_ticks = 0;
	/* Set up our timers and enable interrupts */
	TCNT2 = 0;    /* Timer 1 by CLK/64 */
	OCR2A = 115;   /* ~1ms */
	TIMSK2 = _BV(OCIE2A);
	TCCR2B |= (1 << CS11) | (1 << CS10) ; 
	sei();
	
	printf("Bashplate AVR example\n");
	while (1) {
		tmp = timer2_ticks;
		printf("Timer counter %d\n", tmp);
		_delay_ms(200);
	}

  return 0;
}
