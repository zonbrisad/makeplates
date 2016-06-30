/**
 *---------------------------------------------------------------------------
 *
 * @brief Makeplate GLIB example
 *
 * @file    main.c
 * @author  Peter Malmberg <peter.malmberg@gmail.com>
 * @date    2015-05-19 01:20:00
 *
 *---------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <glib-2.0/glib.h>

#include "lua.h"
#include "lauxlib.h"

#include "gp_log.h"
#include "swill/swill.h"

/**
 * Defines
 *---------------------------------------------------------------------------
 */
#define VERSION "0.1"
#define DESCRIPTION "- a general purpose log program"

/**
 * Variables
 *---------------------------------------------------------------------------
 */

GTimer    *timer;
GThread   *thread1;
GThread   *thread2;
GMainLoop *mLoop;

static gboolean opt_verbose    = FALSE;
static gboolean opt_version    = FALSE;
static gboolean opt_quiet      = FALSE;
static gboolean opt_daemon     = FALSE;
static gboolean opt_webtest    = FALSE;


static GOptionEntry entries[] = {
  { "verbose",  'v', 0, G_OPTION_ARG_NONE, &opt_verbose,    "Be verbose output",    NULL },
  { "version",  'b', 0, G_OPTION_ARG_NONE, &opt_version,    "Output version info",  NULL },
  { "quiet",    'q', 0, G_OPTION_ARG_NONE, &opt_quiet,      "No output to console", NULL },
  { "daemon",    0,  0, G_OPTION_ARG_NONE, &opt_daemon,     "Start as daemon",      NULL },
  { "webtest",   0,  0, G_OPTION_ARG_NONE, &opt_webtest,    "SWILL web test",       NULL },
  { NULL }
};

/**
 * Code
 *---------------------------------------------------------------------------
 */
 
void testPage(FILE *f) {
//  swill_printf(f, "Kalle");
}

void webTest() {
  printf("Starting webserver");
//  swill_init(8080);
//  swill_handle("testPage", testPage, NULL);
//  swill_handle("mandelpage.html", mandelpage,m);

  while (1) {
    sleep(1);
//    swill_serve();
  }
}

void safeExit() {
  gp_log_close();
	exit(0);
}

int main(int argc, char *argv[]) {
	GError *error = NULL;
	GOptionContext *context;
	
	// init log system
	gp_log_init("glua.log");                 
	
  // parse command line arguments
  context = g_option_context_new (DESCRIPTION);
  g_option_context_add_main_entries (context, entries, NULL);
  if (!g_option_context_parse (context, &argc, &argv, &error)) {
    g_print ("option parsing failed: %s\n", error->message);
    exit (1);
  }

	// print version information
	if (opt_version) {
		printf("Program version %s\nBuild ("__DATE__" "__TIME__")\n", VERSION);
		safeExit();
	}
	
	// enable verbose mode
	if (opt_verbose) {
	  gp_log_set_verbose(TRUE);  
	}
	
  if (opt_webtest) {
    webTest();
  }
	
	printf("Ett litet testprogram.\n");
	
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "test.lua");
	lua_close(L);
	 	
	safeExit();
}
