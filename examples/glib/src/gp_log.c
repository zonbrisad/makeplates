
#include <syslog.h>
#include <stdio.h>
#include <glib-2.0/glib.h>
#include <glib/gstdio.h>

#include <glib/gstdio.h>

#include "Def.h"
#include "gp_log.h"


gboolean gp_verbose=FALSE;
gboolean gp_syslog=FALSE;
gboolean gp_debug=FALSE;
gboolean gp_noColor=FALSE;

char *gp_logFile;
char *gp_logDir;

FILE *gpLogFile;

static void gp_log_handler(const gchar *log_domain,
                   GLogLevelFlags log_level,
                   const gchar *message,
                   gpointer user_data );


void gp_log_set_verbose(gboolean v) {
  gp_verbose = v;
}

void gp_log_init() {
	
	gp_log_set_verbose(FALSE);
	
	/* Set handler for all levels */
  g_log_set_handler(G_LOG_DOMAIN, G_LOG_LEVEL_MASK, gp_log_handler, NULL);
	
	gpLogFile = g_fopen("gplog.log", "RW");
	
}

void gp_log_close() {
  
}

static void gp_log_handler(const gchar *log_domain,
                           GLogLevelFlags log_level,
                           const gchar *message,
                           gpointer user_data )
{
	char *color;
    
  switch (log_level) {
      case G_LOG_LEVEL_WARNING:  color = E_BR_YELLOW;  break;
	    case G_LOG_LEVEL_ERROR:    color = E_BR_RED;     break;
      case G_LOG_LEVEL_CRITICAL: color = E_ON_RED E_WHITE;  break;
      case G_LOG_LEVEL_DEBUG:    color = E_BR_GREEN;   break;
      case G_LOG_LEVEL_INFO:     color = E_WHITE;      break;
      case G_LOG_LEVEL_MESSAGE:  color = E_BR_CYAN;    break;
      default:                   color = E_WHITE;
  }

  if ( gp_verbose ) {
    printf("%s%s" E_END, color, message);
  }
  
	
	
  return ;
}
