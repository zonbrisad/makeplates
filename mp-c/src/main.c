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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "def.h"

// Macros -----------------------------------------------------------------

#define PROGNAME "makeplate"

// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------

// Code -------------------------------------------------------------------


void sigInt(int sig) {
	printf("\nExiting program\n");
	exit(0);
}

void sigHup(int sig) {
	printf("Sighup\n");
}


int main(int argc, char *argv[]) {
	int i;
	
	signal(SIGINT, sigInt);
	signal(SIGHUP, sigHup);
	
	printf("Makeplate c example.\n");

	INFOPRINT("Information printout\n");
	
	DEBUGPRINT("Debug printout\n");

	DEBUG_DO(printf("Debug do\n"));
	
	
	i = 0;
	
	printf("Var i = %2x\n", i);
	BIT_SET(i, 4);
	printf("Var i = %2x\n", i);
	BIT_SET(i, 2);
	printf("Var i = %2x\n", i);
	BIT_CLEAR(i,4);
	printf("Var i = %2x\n", i);

	
	while(1) {
	}
	
	return 0;

}
