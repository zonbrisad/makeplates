/**
 *---------------------------------------------------------------------------
 * @brief   Some usefull C routines.
 *
 * @file    pmutil.c
 * @author  Your Name <your.name@yourdomain.org>
 * @date    2017-05-04
 * @licence GPLv2
 *
 *---------------------------------------------------------------------------
 */

// Includes ---------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "def.h"
#include "def_util.h"

// Macros -----------------------------------------------------------------

// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------

// Code -------------------------------------------------------------------

// I2S ----------------------------------------------------------------------

// S2S ----------------------------------------------------------------------


int S2S_findIdx(S2S *db, char *key) {
    int i = 0;

    while (strncmp(db[i].key, "",  S2S_STRLEN)) {
        if (!strncmp(db[i].key, key, S2S_STRLEN)) {
            return i;
        }

        i++;
    }

    return -1;
}

int S2S_len(S2S *db) {
    int i = 0;

    while (strncmp(db[i].key, "",  S2S_STRLEN)) {
        i++;
    }

    return i;
}


char *S2S_getValue(S2S *db, char *key) {
    int i;
    i = S2S_findIdx(db, key);

    if (i != -1) {
        return db[i].val;
    }

    return NULL;
}



// Binary--------------------------------------------------------------------

#define MAXBITS  32

char *int2bin(int val, uint8_t bits) {
	static char buf[MAXBITS+1];
	int i;
	int n;
	int mb;
	
  n = val;
	
	mb = Clamp(bits, 0, MAXBITS);
//	printf("Maxibits %d\n", mb);
	buf[mb] = '\0';
	
	for (i = mb-1; i >= 0; --i) {
		buf[i] = (n & 1) ? '1' : '0';
		n >>= 1;
	}

	return buf;
}





// Linux specific  ---------------------------------------------------------

#ifdef PMU_LINUX

void daemonize(void) {
    pid_t pid, sid;
    int fd;

    /* already a daemon */
    if ( getppid() == 1 ) {
        return;
    }

    /* Fork off the parent process */
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Killing the Parent Process*/
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* At this point we are executing as the child process */

    /* Create a new SID for the child process */
    sid = setsid();

    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory. */
    if ((chdir("/")) < 0)   {
        exit(EXIT_FAILURE);
    }

    fd = open("/dev/null", O_RDWR, 0);

    // redirect streams
    if (fd != -1) {
        dup2 (fd, STDIN_FILENO);
        dup2 (fd, STDOUT_FILENO);
        dup2 (fd, STDERR_FILENO);

        if (fd > 2) {
            close (fd);
        }
    }

    /* resettign File Creation Mask */
    umask(027);
}

#endif
