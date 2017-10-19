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
#include "i2i.h"

// Macros -----------------------------------------------------------------

// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------

// Code -------------------------------------------------------------------

// i2i ----------------------------------------------------------------------


i2i *i2i_new(int size) {
  i2i *db;
	
	db = malloc((size+1) * sizeof(i2i));

	db[size].key = I2I_LAST;
	db[size].val = 0;
	
	return db;
}

i2i *i2i_copy(i2i *db) {
	i2i *dst;
	int len;

	len = i2i_len(db);

	dst = i2i_new(len);

	memcpy(dst, db, len * sizeof(i2i));

	return dst;
}

void i2i_free(i2i *db) {
  free(db);
}

int i2i_findIdx(i2i *db, int val) {
    int i = 0;

    while (db[i].key != I2I_LAST) {
        if (db[i].key == val) {
            return i;
        }

        i++;
    }

    return -1;
}

int i2i_findIdxStr(i2i *db, int str) {
    int i = 0;

    while (db[i].key != I2I_LAST) {
//        if (!strncmp(db[i].val, str, I2S_STRLEN)) {
//            return i;
 //       }

        i++;
    }

    return -1;
}

char *i2i_getValue(i2i *db, int val) {
    int idx = 0;

    idx = i2i_findIdx(db, val);

    if (idx != -1) {
        return db[idx].val;
    } else {
        return NULL;
    }
}

void i2i_setValue(i2i *db, int val, int str) {
    int idx = 0;

    idx = i2i_findIdx(db, val);

    if (idx != -1) {
 //       strncpy(db[idx].val, str, i2i_STRLEN);
    }
}

void i2i_setKeyValue(i2i *db, int idx, int key, int value) {

	if (isWithin(idx, 0, i2i_len(db)-1)) {
		db[idx].key = key;
//		strncpy(db[idx].val, value, I2S_STRLEN);
	}
}


int i2i_len(i2i *db) {
    int i = 0;

    while (db[i].key != I2I_LAST) {
        i++;
    }

    return i;
}

int i2i_last(i2i *db) {
    return i2i_len(db) - 1;
}

int i2i_first(i2i *db) {
    UNUSED(db);
    return 0;
}


