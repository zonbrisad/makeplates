
#include <stdio.h>
#include "def.h"

int main(int argc, char *argv[]) {
	int i;
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
	
	
	return 0;

}
