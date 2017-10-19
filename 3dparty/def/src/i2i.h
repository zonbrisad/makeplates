/**
 *---------------------------------------------------------------------------
 * @brief   Int 2 int assiciative array
 *
 * @file    i2i.h
 * @author  Peter Malmberg <peter.malmberg@gmail.com>
 * @date    2017-05-04
 * @licence GPLv2
 *
 *---------------------------------------------------------------------------
 */

#ifndef PMUTIL_H
#define PMUTIL_H

#ifdef __cplusplus
extern "C" {
#endif

// Includes ---------------------------------------------------------------

// Macros -----------------------------------------------------------------

	
// Activate linux specific utils
//#define PMU_LINUX 1



#define I2I_LAST (int)0xFFFFFFFF
#define I2I_END I2I_LAST, ""


	

// Typedefs ---------------------------------------------------------------

typedef struct {
    int  key;
	  int  val;
} i2i;


// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------

i2i *i2i_new(int size);
i2i *i2i_copy(i2i *db);
void i2i_free(i2i *db);

int i2i_findIdx(i2i *db, int key);
int i2i_findIdxStr(i2i *db, int value);
char *i2i_getValue(i2i *db, int key);
void i2i_setValue(i2i *db, int key, int value);

void i2i_setKeyValue(i2i *db, int idx, int key, int value);

int i2i_last(i2i *db);
int i2i_first(i2i *db);
int i2i_len(i2i *db);





	
#ifdef __cplusplus
} //end brace for extern "C"
#endif
#endif

