
#include <syslog.h>
#include <stdio.h>
#include <glib-2.0/glib.h>
#include <glib/gstdio.h>

#include "Def.h"
#include "gp_log.h"


gboolean gp_verbose=FALSE;
gboolean gp_syslog=FALSE;
gboolean gp_debug=FALSE;
gboolean gp_noColor=FALSE;

char *gp_logFile;
char *gp_logDir;

FILE *gpLogFile = NULL;

static void gp_log_handler(const gchar *log_domain,
                   GLogLevelFlags log_level,
                   const gchar *message,
                   gpointer user_data );


void gp_log_set_verbose(gboolean v) {
  gp_verbose = v;
}

void gp_log_init(char *logfile) {
	
	gp_log_set_verbose(FALSE);
	
	/* Set handler for all levels */
  g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_MASK, gp_log_handler, NULL);
	
	gpLogFile = g_fopen(logfile, "a");
  if (gpLogFile==NULL) {
    printf("Could not open file\n");
  }

}

void gp_log_close() {
  fclose(gpLogFile);  
}

static void gp_log_handler(const gchar *log_domain,
                           GLogLevelFlags log_level,
                           const gchar *message,
                           gpointer user_data )
{
	char *color;
  char *level;
  GDateTime *dt;
  char *dateTime;
    
  switch (log_level) {
      case G_LOG_LEVEL_WARNING:  color = E_BR_YELLOW;  level = "warn"; break;
	    case G_LOG_LEVEL_ERROR:    color = E_BR_RED;     level = "err "; break;
      case G_LOG_LEVEL_CRITICAL: color = E_ON_RED E_WHITE;  level = "crit"; break;
      case G_LOG_LEVEL_DEBUG:    color = E_BR_GREEN;   level = "dbg ";  break;
      case G_LOG_LEVEL_INFO:     color = E_WHITE;      level = "info";   break;
      case G_LOG_LEVEL_MESSAGE:  color = E_BR_CYAN;    level = "msg ";break;
      default:                   color = E_WHITE;
  }
  
  // date and time information
  dt = g_date_time_new_now_local();
  dateTime = g_date_time_format(dt,"%Y-%m-%d %k:%M:%S");
  
  if ( gp_verbose ) {
    printf("%s [%s%s%s] %s",dateTime,color,level,E_END,message);
  }
  
  fprintf(gpLogFile, "%s [%s] %s", dateTime, level, message);
  
  g_free(dateTime);
  
  return ;
}

void gp_log_print() {

}
