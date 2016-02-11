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
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <glib-2.0/glib.h>

#include "gp_log.h"

/**
 * Defines
 *---------------------------------------------------------------------------
 */
#define VERSION "0.1"
#define DESCRIPTION "- a general purpose log program"
#define LOGFILE "glib.log"
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
static gboolean opt_info       = FALSE;
static gboolean opt_daemonTest = FALSE;


static GOptionEntry entries[] = {
  { "verbose",  'v', 0, G_OPTION_ARG_NONE, &opt_verbose,    "Be verbose output",    NULL },
  { "version",  'b', 0, G_OPTION_ARG_NONE, &opt_version,    "Output version info",  NULL },
  { "quiet",    'q', 0, G_OPTION_ARG_NONE, &opt_quiet,      "No output to console", NULL },
  { "daemon",    0,  0, G_OPTION_ARG_NONE, &opt_daemon,     "Start as daemon",      NULL },
	{ "error",     0,  0, G_OPTION_ARG_NONE, &opt_errorTest,  "Error test",           NULL },
  { "thread",    0,  0, G_OPTION_ARG_NONE, &opt_threadTest, "Thread test",          NULL },	
  { "info",     'i', 0, G_OPTION_ARG_NONE, &opt_info,       "Show info",            NULL },
	{ "daemon",   'd', 0, G_OPTION_ARG_NONE, &opt_daemonTest, "Daemon test",          NULL },
  { NULL }
};

/*
typedef struct kalle {
  *fun(void )
}
*/
/**
 * Code
 *---------------------------------------------------------------------------
 */


void safeExit() {
  gp_log_close();
	exit(0);
}

void errorTest() {
//	int i;
	gp_log_set_verbose(TRUE);
//  g_info("This is information\n");
  g_message("This is a message\n");
  g_warning("This is a warning\n");
  g_debug("This is a debug message\n");
  g_error("This is an error\n");
	//g_critical("This is critical\n");
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
							
void infoTest() {
  pid_t pid;
  pid = getpid();
  GError *err;
  char *buf;
  
  buf = g_file_read_link("/proc/self/exe", &err);
  
  printf("PID:          %d\n", pid);
  printf("Program path: %s\n", buf);
  printf("Username:     %s\n", g_get_user_name());
  printf("Full name:    %s\n", g_get_real_name());
  printf("Home dir:     %s\n", g_get_home_dir());
  printf("Hostname:     %s\n", g_get_host_name());
}


void daemonize(void) {
	pid_t pid, sid;
	int fd;
	
	/* already a daemon */
	if ( getppid() == 1 ) return;
	
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
	if ((chdir("/")) < 0)	{
		exit(EXIT_FAILURE);
	}
	
	fd = open("/dev/null",O_RDWR, 0);
	
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

void daemonTest(void) {
  printf("Starting up daemon\n");
	daemonize();

	mLoop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(mLoop);
}


int main(int argc, char *argv[]) {
	GError *error = NULL;
	GOptionContext *context;
	
	// init log system
	gp_log_init(LOGFILE);
  
  // parse command line arguments
  context = g_option_context_new (DESCRIPTION);
  g_option_context_add_main_entries (context, entries, NULL);
  if (!g_option_context_parse (context, &argc, &argv, &error)) {
    g_print ("option parsing failed: %s\n", error->message);
    exit (1);
  }

	// enable verbose mode
	if (opt_verbose) {
	  gp_log_set_verbose(TRUE);  
	}
  
  g_message("Program start\n");
	
  // print version information
	if (opt_version) {
		printf("Program version %s\nBuild ("__DATE__" "__TIME__")\n", VERSION);
		exit(0);
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
  
	// thread test
	if (opt_info) { 
		infoTest();
		exit(0);
	}

	// daemon test
	if (opt_daemonTest) { 
		daemonTest();
		exit(0);
	}

 	
	return 0;
}
