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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib-2.0/glib.h>

#include "gp_log.h"

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
static gboolean opt_errorTest  = FALSE;
static gboolean opt_threadTest = FALSE;

static GOptionEntry entries[] = {
	//  { "repeats",  'r', 0, G_OPTION_ARG_INT,  &repeats,   "Average over N repetitions", "N" },
  //  { "max-size", 'm', 0, G_OPTION_ARG_INT,  &max_size,  "Test up to 2^M items", "M" },
  { "verbose",  'v', 0, G_OPTION_ARG_NONE, &opt_verbose,    "Be verbose output",    NULL },
  { "version",  'b', 0, G_OPTION_ARG_NONE, &opt_version,    "Output version info",  NULL },
  { "quiet",    'q', 0, G_OPTION_ARG_NONE, &opt_quiet,      "No output to console", NULL },
  { "daemon",    0,  0, G_OPTION_ARG_NONE, &opt_daemon,     "Start as daemon",      NULL },
	{ "error",     0,  0, G_OPTION_ARG_NONE, &opt_errorTest,  "Error test",           NULL },
	{ "thread",    0,  0, G_OPTION_ARG_NONE, &opt_threadTest, "Thread test",          NULL },	
	
  { NULL }
};

/*
typedef struct kalle {
  *fun(void )
}
*/
/**
 *
 *---------------------------------------------------------------------------
 */


void safeExit() {
  gp_log_close();
	exit(0);
}

void errorTest() {
	gp_log_set_verbose(TRUE);
//  g_info("This is information\n");
  g_message("This is message\n");
  g_warning("This is warning\n");
  g_debug("This is debug\n");
  g_error("This is an error\n");
	g_critical("This is critical\n");

}

void sig_ctrl_c(int sig) {
  g_main_loop_quit(mLoop);
}

void thread_t() {
	while (1) {
	  printf("Kalle");	
	}
}

gboolean timeout_1() {
	gulong t;
	gdouble d;
	d = g_timer_elapsed(timer, &t);
	printf("Elapsed time %f s\n", d);
	return TRUE;
}

void threadTest() {
	timer = g_timer_new();
	g_timer_start(timer);
	
  signal(SIGINT, sig_ctrl_c);
	
	mLoop = g_main_loop_new(NULL, FALSE);
	  
	g_timeout_add_seconds(1, timeout_1, "Timeout 1");

//	thread = g_thread_new("TestThread", thread_t, NULL);
	
	g_main_loop_run(mLoop);

}
								 

int main(int argc, char *argv[]) {
	GError *error = NULL;
	GOptionContext *context;
	
	// init log system
	gp_log_init();                 
	
  // parse command line arguments
  context = g_option_context_new (DESCRIPTION);
  g_option_context_add_main_entries (context, entries, NULL);
  if (!g_option_context_parse (context, &argc, &argv, &error)) {
    g_print ("option parsing failed: %s\n", error->message);
    exit (1);
  }

	// print version information
	if (opt_version) {
		printf("Program Version: %s\n", VERSION);
		exit(0);
	}
	
	// enable verbose mode
	if (opt_verbose) {
	  gp_log_set_verbose(TRUE);  
	}
	
	// Error Test
	if (opt_errorTest) {
		errorTest();
		exit(0);
	}
	
	// thread test
	if (opt_threadTest) { 
		threadTest();
		exit(0);
	}
	
	return 0;
}
