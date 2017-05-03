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
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#include "def.h"

// Defines ----------------------------------------------------------------

#define PROGNAME "makeplate"

// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------
void sigInt(int sig);
void sigHup(int sig);

// Code -------------------------------------------------------------------


void sigInt(int sig) {
	UNUSED(sig);
	
	printf("\nExiting program\n");
	exit(0);
}

void sigHup(int sig) {
	UNUSED(sig);
	printf("Sighup\n");
}

I2S numbersDb[] = {
	{ 1, "First"  },
	{ 2, "Second" },
	{ 3, "Third"  },
	{ 4, "Last"   },
	{ I2S_END     },
};


int main(int argc, char *argv[]) {
	int i;
	
	UNUSED(argc);
	UNUSED(argv);
	
	signal(SIGINT, sigInt);
	signal(SIGHUP, sigHup);
	
	printf("\nMakeplate linux C example.\n\n\n");

	INFOPRINT("Information printout\n");
	
	DEBUGPRINT("Debug printout\n");
	
	WARNINGPRINT("Warning printout\n");
	
	ERRORPRINT("Error printout\n");
	
	DEBUG_DO(printf("Debug do\n"));
	
	
	i = 0;
	
	printf("Var i = %2x\n", i);
	BIT_SET(i, 4);
	printf("Var i = %2x\n", i);
	BIT_SET(i, 2);
	printf("Var i = %2x\n", i);
	BIT_CLEAR(i,4);
	printf("Var i = %2x\n", i);

	
	for (i=1;i<=4;i++) {
		printf("I2S test %d  =  %s\n", i, I2S_getString(numbersDb, i));
	}
	
	I2S_setString(numbersDb, 4, "Fourth");
	printf("I2S test %d  =  %s\n", 4, I2S_getString(numbersDb, 4));
	
	
	printf("Use CTRL-C to stop program\n");
	while(1) {
	}
	
	return 0;
}
