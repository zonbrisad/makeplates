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
#include "argtable2.h"

// Macros -----------------------------------------------------------------

#define PROGNAME "makeplate"

// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------

// Code -------------------------------------------------------------------


void sigInt(int sig) {
	INFO_DO(printf("\n"));
	INFOPRINT("Exiting program\n");
	exit(0);
}

void sigHup(int sig) {
	INFOPRINT("Sighup\n");
}


int main(int argc, char *argv[]) {
	int i;
	struct arg_lit  *list    = arg_lit0("lL",NULL,                      "list files");
	struct arg_lit  *recurse = arg_lit0("R",NULL,                       "recurse through subdirectories");
	struct arg_int  *repeat  = arg_int0("k","scalar",NULL,              "define scalar value k (default is 3)");
	struct arg_str  *defines = arg_strn("D","define","MACRO",0,argc+2,  "macro definitions");
	struct arg_file *outfile = arg_file0("o",NULL,"<output>",           "output file (default is \"-\")");
	struct arg_lit  *verbose = arg_lit0("v","verbose,debug",            "verbose messages");
	struct arg_lit  *help    = arg_lit0(NULL,"help",                    "print this help and exit");
	struct arg_lit  *version = arg_lit0(NULL,"version",                 "print version information and exit");
	struct arg_file *infiles = arg_filen(NULL,NULL,NULL,1,argc+2,       "input file(s)");
	struct arg_end  *end     = arg_end(20);
	void* argtable[] = {list,recurse,repeat,defines,outfile,verbose,help,version,infiles,end};
	const char* progname = "myprog";
	int nerrors;
	int exitcode=0;
	
	 /* verify the argtable[] entries were allocated sucessfully */
	if (arg_nullcheck(argtable) != 0)
		{
			/* NULL entries were detected, some allocations must have failed */
			printf("%s: insufficient memory\n",progname);
			exitcode=1;
			goto exit;
		}
	
	/* set any command line default values prior to parsing */
	repeat->ival[0]=3;
	outfile->filename[0]="-";
	
	/* Parse the command line as defined by argtable[] */
	nerrors = arg_parse(argc,argv,argtable);
	
	/* special case: '--help' takes precedence over error reporting */
	if (help->count > 0)
		{
			printf("Usage: %s", progname);
			arg_print_syntax(stdout,argtable,"\n");
			        printf("This program demonstrates the use of the argtable2 library\n");
			printf("for parsing command line arguments. Argtable accepts integers\n");
			printf("in decimal (123), hexadecimal (0xff), octal (0o123) and binary\n");
			printf("(0b101101) formats. Suffixes KB, MB and GB are also accepted.\n");
			arg_print_glossary(stdout,argtable,"  %-25s %s\n");
			exitcode=0;
			goto exit;
		}
	
	/* special case: '--version' takes precedence error reporting */
	if (version->count > 0)
		{
			printf("'%s' example program for the \"argtable\" command line argument parser.\n",progname);
			printf("September 2003, Stewart Heitmann\n");
			exitcode=0;
			goto exit;
		}
	
	/* If the parser returned any errors then display them and exit */
	    if (nerrors > 0)
		{
			        /* Display the error details contained in the arg_end struct.*/
			arg_print_errors(stdout,end,progname);
			printf("Try '%s --help' for more information.\n",progname);
			exitcode=1;
			goto exit;
		}
	
	/* special case: uname with no command line options induces brief help */
	    if (argc==1)
		{
			printf("Try '%s --help' for more information.\n",progname);
			exitcode=0;
			goto exit;
		}
	
	/* normal case: take the command line options at face value */
/*	exitcode = mymain(list->count, recurse->count, repeat->ival[0],
												                      defines->sval, defines->count,
										outfile->filename[0], verbose->count,
										infiles->filename, infiles->count);
	
*/
	signal(SIGINT, sigInt);
	signal(SIGHUP, sigHup);
	
	printf("\nMakeplate linux C example.\n\n\n");

	
	

	while(1) {
	}
	
exit:
	return 0;
}
