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
#include "argtable3.h"


// Defines ----------------------------------------------------------------

#define APP_NAME        "glibtest"
#define APP_VERSION     "0.1"
#define APP_DESCRIPTION "- a general purpose log program"
#define APP_LOGFILE     "glib.log"
#define APP_PIDFILE     "/tmp/glibtest.pid"
#define PROGNAME "makeplate"
#define LOCKFILE "test/" PROGNAME ".PID"

// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------
void sigInt(int sig);
void sigHup(int sig);

// Code -------------------------------------------------------------------


// http://stackoverflow.com/questions/27989858/converting-enum-error-code-to-string
typedef struct {
  int errorCode;
  char errorString[32];
} errorString;

char *errString(errorString *es, int errorCode) {
  int i;
  i = 0;
  while(es[i].errorCode != -0xFFFFFF) {
    if (errorCode == es[i].errorCode) {
      return es[i].errorString;
    }
    i++;
  }
  return NULL;
}


void sigInt(int sig) {
  UNUSED(sig);
  INFO_DO(printf("\n"));
  INFOPRINT("Exiting program\n");
  exit(0);
}

void sigHup(int sig) {
  UNUSED(sig);
  INFOPRINT("Sighup\n");
}

void removePidFile(char *pidFile) {
  remove(pidFile);
}

/**
 * http://www.man7.org/tlpi/code/online/dist/filelock/create_pid_file.c.html
 */
int createPidFile(char *pidFile) {
  pid_t pid, fPid;
  int  e;
  FILE *file;

  DEBUGPRINT("Creating PID file. (%s)\n", pidFile);
	
  // get pid of this process
  pid = getpid();   	        	
	
  DEBUGPRINT("This process PID=%d\n", pid);
	
  // open pid file and read PID 
  file = fopen(pidFile, "a+");
  if ( file == NULL ) {        
    ERRORPRINT("Failed to open pidfile (%s) [%s]\n", pidFile, strerror(errno));
    return -1;
  } else {
		
    e = fscanf(file, "%d", &fPid);
		
    // if pid file exist check if process is running
    if (e > 0) {
			
    }
		
    if (e == -1) {
      goto writePid;
    } else {
      WARNINGPRINT("Found PID file %d\n", fPid);
    }

    // check if process is running
    e = kill(fPid, 0);
				
    // write new pid to file
writePid:
    rewind(file);
    fprintf(file, "%d\n", pid);
closePid:
    fclose(file);
  }
}

// find path to self
char *getPathToSelf(void) {
  static char buf[128];
  int size;
	
  size = readlink("/proc/self/exe", buf, 128);
  buf[size] = '\0';
  return buf;
}


int main(int argc, char *argv[]) {
  struct arg_lit  *list    = arg_lit0("lL",NULL,                      "list files");
  struct arg_lit  *recurse = arg_lit0("R",NULL,                       "recurse through subdirectories");
  struct arg_int  *repeat  = arg_int0("k","scalar",NULL,              "define scalar value k (default is 3)");
  struct arg_str  *defines = arg_strn("D","define","MACRO",0,argc+2,  "macro definitions");
  struct arg_file *outfile = arg_file0("o",NULL,"<output>",           "output file (default is \"-\")");
  struct arg_lit  *verbose = arg_lit0("v","verbose,debug",            "verbose messages");
  struct arg_lit  *help    = arg_lit0(NULL,"help",                    "print this help and exit");
  struct arg_lit  *version = arg_lit0(NULL,"version",                 "print version information and exit");
  //	struct arg_file *infiles = arg_filen(NULL,NULL,NULL,1,argc+2,       "input file(s)");
  struct arg_end  *end     = arg_end(20);
  void* argtable[] = {list,recurse,repeat,defines,outfile,verbose,help,version,end};
	
  const char* progname = "myprog";
  int nerrors;
  int exitcode=0;
	
  /* verify the argtable[] entries were allocated sucessfully */
  if (arg_nullcheck(argtable) != 0) {
		/* NULL entries were detected, some allocations must have failed */
    printf("%s: insufficient memory\n",progname);
    exitcode=1;
    goto exit;
  }
	
  /* set any command line default values prior to parsing */
//	repeat->ival[0]=3;
//	outfile->filename[0]="-";
	
	/* Parse the command line as defined by argtable[] */
  nerrors = arg_parse(argc,argv,argtable);
	
	/* special case: '--help' takes precedence over error reporting */
  if (help->count > 0) {
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
  if (version->count > 0) {
    printf("'%s' example program for the \"argtable\" command line argument parser.\n",progname);
		
    exitcode=0;
    goto exit;
  }
  
  /* If the parser returned any errors then display them and exit */
  if (nerrors > 0) {
    /* Display the error details contained in the arg_end struct.*/
    arg_print_errors(stdout,end,progname);
    printf("Try '%s --help' for more information.\n",progname);
    exitcode=1;
    goto exit;
  }
	
  /* special case: uname with no command line options induces brief help */
/*	    if (argc==1)
		{
			printf("Try '%s --help' for more information.\n",progname);
			exitcode=0;
			goto exit;
		}
	*/
	/* normal case: take the command line options at face value */
/*	exitcode = mymain(list->count, recurse->count, repeat->ival[0],
												                      defines->sval, defines->count,
										outfile->filename[0], verbose->count,
										infiles->filename, infiles->count);
*/
  signal(SIGINT, sigInt);
  signal(SIGHUP, sigHup);

  printf("\nMakeplate linux C example.\n\n\n");

  DEBUGPRINT_COND(1,"Sant\n");
  DEBUGPRINT_COND(0,"Falskt\n");
	
  createPidFile(LOCKFILE);

  printf("Path to binary: %s\n", getPathToSelf());
	
	/*	
	while(1) {
	}
	 */
exit:
//	removePidFile(LOCKFILE);
  return 0;
}
