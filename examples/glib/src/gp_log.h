/* 
 * File:   gp_log.h
 * Author: pmg
 *
 * Created on April 14, 2015, 6:34 PM
 */

#ifndef GP_LOG_H
#define	GP_LOG_H

#include <glib-2.0/glib.h>

#ifdef	__cplusplus
extern "C" {
#endif

  /**
   * Init log system.
   */
  void gp_log_init();
	
	void gp_log_set_verbose(gboolean v);


#ifdef	__cplusplus
}
#endif

#endif	/* GP_LOG_H */

