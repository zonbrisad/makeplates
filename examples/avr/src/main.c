
#include <stdio.h>
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


/*
 *  *  Poll the specified string out the debug port.
 *  */
void debug_puts(const char *str)
{
	  const char *c;
	
	  for ( c=str ; *c ; c++ )
		    special_output_port = *c;
}


int main() {

	stdout = &mystdout;
//	debug_puts("Test\n");
	printf("Bashplate AVR example\n");
	while (1) {
		special_output_port = 'K';
		_delay_ms(200);
	}

  return 0;
}
