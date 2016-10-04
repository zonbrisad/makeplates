
#include <stdio.h>
#include "def.h"

int main(int argc, char *argv[]) {
   printf("Makeplate c example.\n");
   
   DEBUGPRINT("Debug printout\n");
   
   DEBUG_DO(printf("Debug do\n"));
   
   return 0;
}
