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
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "luaConf.h"

// Macros -----------------------------------------------------------------

// Variables --------------------------------------------------------------

/* 
 * - flag for variable must be present
 * - ability to generate a configuration file
 * - ability to define configuration file with configuration file
 * - conditional parameters (if one is given another must be given)
 * - possible to use as cmd line parameter
 * - built in constants
 * 
 * https://www.lua.org/pil/25.html
 */ 


// Prototypes -------------------------------------------------------------

#define LCT_INT  int
#define LCT_DBL  double
#define LCT_STR  char*

// Code -------------------------------------------------------------------

char *trueList[]  = { "on",  "yes", "true",  "1", NULL };
char *falseList[] = { "off", "no",  "false", "0", NULL };

typedef enum {
  LC_FLAG_REQUIRED = 0x0001,  // This parameter is required
	LC_FLAG_MISSING  = 0x0100,  // Indicates that this parameter is missing in configuration
	LC_FLAG_INVALID  = 0x0200,  // Parameter exists but value is invalid
} LC_FLAGS;

typedef enum {
  LC_TYPE_INTEGER,
  LC_TYPE_DOUBLE,
  LC_TYPE_STRING,
  LC_TYPE_BOOLEAN,

	LC_TYPE_INTEGER_LIST,
	LC_TYPE_DOUBLE_LIST,
	LC_TYPE_STRING_LIST,
	LC_TYPE_BOOLEAN_LIST,

  LC_TYPE_CUSTOM,
	LC_TYPE_COMMENT,
  LC_TYPE_LAST,
} LC_TYPES;

typedef struct {
  LCT_INT val;         // parameter value
  LCT_INT default_val; // default value
  LCT_INT max;         // max value of parameter
  LCT_INT min;         // min value of parameter
  LCT_INT list[];      // list of valid values of parameter
} LUACONF_DATA_INTEGER;

typedef struct {
  LCT_DBL val;         // parameter value
  LCT_DBL default_val; // default value
  LCT_DBL max;         // max value of parameter
  LCT_DBL min;         // min value of parameter
  LCT_DBL list[];      // list of valid values of parameter
} LUACONF_DATA_DOUBLE;

typedef struct {
  LCT_STR val;         // parameter value
  LCT_STR default_val; // default value
  LCT_STR list[];      // list of valid values of parameter
} LUACONF_DATA_STRING;


typedef struct {
  LC_TYPES     type;
  char         *name;
  char         *desc;
  uint16_t     flags;
  union {
    LUACONF_DATA_INTEGER intParam;
    LUACONF_DATA_DOUBLE  dblParam;
    LUACONF_DATA_STRING  strParam;
  } data;
  
} luaConf;

typedef struct {
  LC_TYPES type;
  char     *name;
} type2str;


#define LC_INT(name, desc, flags, def)  LC_TYPE_INTEGER, name, desc, flags, .data.intParam = {0, def}
#define LC_DBL(name, desc, flags, def)  LC_TYPE_DOUBLE,  name, desc, flags, .data.dblParam = {0, def}
#define LC_STR(name, desc, flags, def)  LC_TYPE_STRING,  name, desc, flags, .data.strParam = {NULL, NULL}
#define LC_LAST()  LC_TYPE_LAST

type2str t2s[] = {
  {LC_TYPE_INTEGER, "Integer"},
  {LC_TYPE_DOUBLE,  "Double"},
	{LC_TYPE_STRING,  "String"},
	{LC_TYPE_BOOLEAN, "Boolean"},
  {LC_TYPE_LAST,    NULL}
};

luaConf confTest[] = {
  {LC_INT("IntParam1", "Integer desc 1.", 0, -42)},
  {LC_INT("IntParamInvalid1", "Integer desc 2.", 0, -43)},
  {LC_DBL("DoubleParam",  "Double desc.",     0, -4.2)},
	{LC_STR("StringParam",  "String desc.",     0, "")},
	{LC_DBL("MissingParam", "Missing desc.",    0, -4.2)},

  {LC_LAST()},
};

char *type2string(LC_TYPES type) {
  int i;
  i=0;
  while (t2s[i].type != type) {
    i++;
    if (t2s[i].type == LC_TYPE_LAST)
      return NULL;
  }
  
  return t2s[i].name;
}

char *val2string(luaConf *param) {
  static char buf[128];
  switch (param->type) {
   	 case LC_TYPE_INTEGER:sprintf(buf, "%d", param->data.intParam.val); break;
   	 case LC_TYPE_DOUBLE: sprintf(buf, "%f", param->data.dblParam.val); break;
   	 case LC_TYPE_STRING: return param->data.strParam.val;
   default:
    return "";
  }
  return buf;
}

void printParam(luaConf *param) {
  printf("Name: %s\n", param->name);
  printf("Desc: %s\n", param->desc);
  printf("Type: %s\n", type2string(param->type));
  printf("Val:  %s\n", val2string(param));
}

void printParams(luaConf *conf) {
  int i;
  i=0;
  
  while (conf[i].type != LC_TYPE_LAST) {
    printParam(&conf[i]);
    printf("\n");
//    printf("%20s %s\n", conf[i].varName, conf[i].desc);
    i++;
  }
}

#define SET_INVALID(param) param->flag |= LC_FLAG_INVALID

void LC_validate(luaConf *param) {
	switch (param->type) {
	 	 case LC_TYPE_INTEGER:
	 		 if (param->data.intParam.min != param->data.intParam.max)
	 		 break;
	 	 case LC_TYPE_DOUBLE:  break;
	 	 case LC_TYPE_STRING:  break;
	 	 default:break;
	}
}

void LC_read(luaConf *conf, char *confFile) {
	lua_State *L;
  int i;
  int isnum;
  char *s;
  
  L = luaL_newstate();
	luaL_openlibs(L);
	
  (void) luaL_dofile(L, confFile);

	i=0;
  while (conf[i].type != LC_TYPE_LAST) {
    lua_getglobal(L, conf[i].name);
    switch (conf[i].type) {
    	case LC_TYPE_INTEGER: conf[i].data.intParam.val = (LCT_INT) lua_tonumberx(L, -1, &isnum); break;
    	case LC_TYPE_DOUBLE:  conf[i].data.dblParam.val = (LCT_DBL) lua_tonumberx(L, -1, &isnum); break;
    	case LC_TYPE_STRING:
    		s=lua_tostring(L, -1);
    		 conf[i].data.strParam.val = malloc(  strlen(s)+10 );
    		//strcpy(conf[i].data.strParam.val,s);
    		break;
			default: break;
    }

    //if (isnum)
    	printf("%-20s %s\n", conf[i].name, val2string(&conf[i]));

    i++;
  }
		 
	lua_close(L);
}


void LC_Test(void) {
	printParams(confTest);

	LC_read(confTest, "conftest.lua");


	exit(0);

}


