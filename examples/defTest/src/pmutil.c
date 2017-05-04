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

#include "pmutil.h"
#include "def.h"

// Macros -----------------------------------------------------------------

// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------

// Code -------------------------------------------------------------------

// I2S ----------------------------------------------------------------------

int I2S_findIdx(I2S *db, int val) {
	  int i=0;
	  while (db[i].val != I2S_LAST) {
			    if (db[i].val==val) {
						      return i;
					}
			    i++;
		}
	  return -1;
}

int I2S_findIdxStr(I2S *db, char *str) {
	  int i=0;
	  while (db[i].val != I2S_LAST) {
			    if (!strncmp(db[i].str, str, I2S_STRLEN)) {
						      return i;
					}
			    i++;
		}
	  return -1;
}

char *I2S_getString(I2S *db, int val) {
	  int idx=0;
	
	  idx = I2S_findIdx(db, val);
	
	  if (idx != -1) {
			    return db[idx].str;
		} else {
			    return NULL;
		}
}

void I2S_setString(I2S *db, int val, char *str) {
	  int idx=0;
	    
	  idx = I2S_findIdx(db, val);
	
	  if (idx != -1) {
			    strncpy(db[idx].str, str, I2S_STRLEN);
		}
}

int I2S_len(I2S *db) {
	  int i=0;
	
	  while (db[i].val != I2S_LAST) {
			    i++;
		}
	  return i;
}

int I2S_last(I2S *db) {
	  return I2S_len(db) - 1;
}

int I2S_first(I2S *db) {
	  UNUSED(db);
	  return 0;
}


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
	  int i=0;
	
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
