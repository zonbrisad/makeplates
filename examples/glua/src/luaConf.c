/**
 *---------------------------------------------------------------------------
 * @brief   A simple lua configuration file library.
 *
 * @file    luaConf.c
 * @author  Your Name <your.name@yourdomain.org>
 * @date    2016-12-21
 * @licence GPLv2
 *
 *---------------------------------------------------------------------------
 */

// Includes ---------------------------------------------------------------

#include "luaConf.h"

// Macros -----------------------------------------------------------------

// Variables --------------------------------------------------------------

/* 
 * - flag for variable must be present
 * - ability to generate a configuration file
 * - ability to define confinguration file with configuration file
 * - conditional parameters (if one is given another must be given)
 * - possible to use as cmd line parameter
 * 
 */ 


// Prototypes -------------------------------------------------------------

#define LCT_INT  int
#define LCT_DBL  double
#define LCT_STR  char

// Code -------------------------------------------------------------------

//char *trueList = { "on", "yes", "true", "1" };


typedef enum {
  LUACONF_INTEGER,
  LUACONF_DOUBLE,
  LUACONF_STRING,
  LUACONF_BOOLEAN,
  LUACONF_CUSTOM,
  LUACONF_LAST,
} LUACONF_TYPE;

typedef struct {
  LCT_INT val;         // parameter value
  LCT_INT default_val; // default value
  LCT_INT max;         // max value of paramter
  LCT_INT min;         // min value of paramter
  LCT_INT list[];      // list of valid values of parameter
} LUACONF_DATA_INTEGER;

typedef struct {
  LCT_DBL val;         // parameter value
  LCT_DBL default_val; // default value
  LCT_DBL max;         // max value of paramter
  LCT_DBL min;         // min value of paramter
  LCT_DBL list[];      // list of valid values of parameter
} LUACONF_DATA_DOUBLE;

typedef struct {
  LUACONF_TYPE type;
  char         *varName;
  char         *desc;
  union {
    LUACONF_DATA_INTEGER intParam;
    LUACONF_DATA_DOUBLE  dblParam;
  } data;
  
} luaConf;

#define LC_INT(name,desc,def)  LUACONF_INTEGER, name, desc, .data.intParam = {0, def}
#define LC_DBL(name,desc,def)  LUACONF_DOUBLE,  name, desc, .data.dblParam = {0, def}
#define LC_LAST()  LUACONF_LAST

luaConf confTest[] = {
  {LC_INT("IntParam", "Int desc.", 42)},
  {LC_DBL("DblParam", "Dbl desc.", 4.2)},
  {LC_LAST()},
};



void printParam(luaConf *param) {
  printf("Name: %s\n",param->varName);
  printf("Desc: %s\n",param->desc);
}

void printParams(luaConf *conf) {
  int i;
  i=0;
  conf = confTest;
  
  while (conf[i].type != LUACONF_LAST) {
    printParam(&conf[i]);
    printf("\n");
//    printf("%20s %s\n", conf[i].varName, conf[i].desc);
    i++;
  }
}
