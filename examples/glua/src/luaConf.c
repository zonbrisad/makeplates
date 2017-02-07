
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

#include "def.h"

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

// Macros -----------------------------------------------------------------

// Variables --------------------------------------------------------------

typedef struct {
  int      type;
  char     *name;
} int2str;

int2str type2string[] = {
  {LC_TYPE_INTEGER,      "Integer"},
  {LC_TYPE_DOUBLE,       "Double"},
  {LC_TYPE_STRING,       "String"},
  {LC_TYPE_BOOLEAN,      "Boolean"},
  {LC_TYPE_INTEGER_LIST, "Integer List"},
  {LC_TYPE_DOUBLE_LIST,  "Double List"},
  {LC_TYPE_LAST,         NULL}
};

int2str error2string[] = {
  {LC_ERR_VALID,      "Valid"},
  {LC_ERR_INVALID,    "Invalid"},
  {LC_ERR_OUTOFBOUND, "OutOfBound"},
  {LC_ERR_MISSING,    "Missing"},
};


luaConf confTest[] = {
  {LC_INT("IntParam1",        "Correct Integer parameter",       0, -42, 0, 0)},
  {LC_INT("IntParamInvalid1", "Integer parameter value invalid", 0, 0, 0, 0)},
  {LC_INT("IntParamInvalid2", "Integer parameter value to low",  0, 0, 0, 100)},
  {LC_INT("IntParamInvalid3", "Integer parameter value to high", 0, 0, 0, 100)},
  {LC_INT("IntParamInvalid4", "Integer parameter value to high", 0, 0, 0, 100)},
  {LC_DBL("DblParam1",        "Correct Double parameter",        0, 0, 0, 0)},
  {LC_DBL("DblParamInvalid1", "Double parameter value invalid",  0, 0, 0, 0)},
  {LC_DBL("DblParamInvalid2", "Double parameter value to low",   0, 0, 1, 100)},
  {LC_DBL("DblParamInvalid3", "Double parameter value to high",  0, 0, 1, 100)},
  {LC_STR("StrParam1",        "Correct String parameter",        0, "")},
  {LC_STR("StrParamInvalid1", "Invalid String parameter",        0, "")},
  {LC_DBL("MissingParam",     "Missing parameter",               0, 0, 0, 0)},
  {LC_INT_LIST("IntList",     "Integer List parameter",          0, 0, 0 ,0)},
  {LC_DBL_LIST("DblList",     "Double List parameter",           0, 0, 0 ,0)},


  {LC_LAST()},
};

// Prototypes -------------------------------------------------------------

// Code -------------------------------------------------------------------



char *int2string(int2str *i2s, LC_TYPES type) {
  int i;
  i=0;
  while (i2s[i].type != type) {
    i++;
    if (i2s[i].type == LC_TYPE_LAST)
      return NULL;
  }
  
  return i2s[i].name;
}


char *val2string(luaConf *param) {
  static char buf[128];
  switch (param->type) {
   	 case LC_TYPE_INTEGER:sprintf(buf, "%d", param->data.intParam.val); break;
   	 case LC_TYPE_DOUBLE: sprintf(buf, "%8.2f", param->data.dblParam.val); break;
   	 case LC_TYPE_STRING: return param->data.strParam.val;
   default:
    return "";
  }
  return buf;
}

void printParam(luaConf *param) {
  printf("Name: %s\n", param->name);
  printf("Desc: %s\n", param->desc);
  printf("Type: %s\n", LC_TYPE2STR(param->type));
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

void LC_File(luaConf *conf) {
  int i;

  i=0;
  while (conf[i].type != LC_TYPE_LAST) {
    printf("-- %s\n", conf[i].desc);
    printf("%s = %s\n\n", conf[i].name, val2string(&conf[i]));
    i++;
  }
}


void LC_validate(luaConf *param) {

  switch (param->type) {
    case LC_TYPE_INTEGER:

      // check if value is within limits
      if (param->data.intParam.min != param->data.intParam.max) {
        if (!((param->data.intParam.val >= param->data.intParam.min) && (param->data.intParam.val<=param->data.intParam.max)))
          param->err = LC_ERR_OUTOFBOUND;
      }
      break;
    case LC_TYPE_DOUBLE:
      // check if value is within limits
      if (param->data.dblParam.min != param->data.dblParam.max) {
        if (!((param->data.dblParam.val >= param->data.dblParam.min) && (param->data.dblParam.val<=param->data.dblParam.max)))
    	  param->err = LC_ERR_OUTOFBOUND;
      }
      break;
    case LC_TYPE_STRING:  break;
    default:break;
  }
}

void LC_read(luaConf *conf, char *confFile) {
  lua_State *L;
  int i, j, l;
  int isnum;
  const char *s;
  
  L = luaL_newstate();
  luaL_openlibs(L);

	
  luaL_dofile(L, confFile);


  isnum = 1;
  i=0;
  while (conf[i].type != LC_TYPE_LAST) {
    //DEBUGPRINT("i=%d name=%s\n", i, conf[i].name);
    lua_getglobal(L, conf[i].name);

    if (!lua_isnil(L, -1)) {


    switch (conf[i].type) {
      case LC_TYPE_INTEGER:
    	conf[i].data.intParam.val = (LCT_INT) lua_tonumberx(L, -1, &isnum);
    	 if (!isnum) {
    		 conf[i].err = LC_ERR_INVALID;
    	  }
    	break;
      case LC_TYPE_DOUBLE:
    	conf[i].data.dblParam.val = (LCT_DBL) lua_tonumberx(L, -1, &isnum);
    	 if (!isnum) {
    	   	conf[i].err = LC_ERR_INVALID;
    	 }
    	break;
      case LC_TYPE_STRING:
        s=lua_tostring(L, -1);
        if (s == NULL) {
        	conf[i].err = LC_ERR_INVALID;
        	break;
        }
        printf("String: %s\n",s);
        conf[i].data.strParam.val = malloc(  strlen(s)+10 );
        conf[i].data.strParam.val[0] = '\0';
        strcpy(conf[i].data.strParam.val,s);
        break;
      case LC_TYPE_INTEGER_LIST:
    	  printf("List length %d\n", lua_rawlen(L, -1));
    	  l = lua_rawlen(L, -1);
    	  //conf[i].data.intParam.list = malloc( sizeof(char) * l);
    	  for (j=1;j<=l; j++) {
    		  lua_rawgeti(L, -1, j);
    		  printf("Int List %d\n", (LCT_INT) lua_tonumberx(L, -1, &isnum));
    		  //conf[i].data.intParam.list[j-1] = (LCT_INT) lua_tonumberx(L, -1, &isnum);
    		  lua_pop(L,1);
    	  }
    	break;
      case LC_TYPE_DOUBLE_LIST:
          printf("List length %d\n", lua_rawlen(L, -1));
          l = lua_rawlen(L, -1);
              //conf[i].data.intParam.list = malloc( sizeof(char) * l);
          for (j=1;j<=l; j++) {
            lua_rawgeti(L, -1, j);
            printf("Dbl List %f\n", (LCT_DBL) lua_tonumberx(L, -1, &isnum));
            //conf[i].data.intParam.list[j-1] = (LCT_INT) lua_tonumberx(L, -1, &isnum);
            lua_pop(L,1);
          }
    	break;
      default: break;
    }

    LC_validate(&conf[i]);


    } else {
      conf[i].err = LC_ERR_MISSING;
    }
      printf("%-20s %-10s %-10s %-10s\n", conf[i].name, val2string(&conf[i]), LC_TYPE2STR(conf[i].type), LC_ERROR2STR(conf[i].err));
      i++;
  }

  lua_close(L);
}


void LC_Test(void) {

  printParams(confTest);

  LC_File(confTest);

  LC_read(confTest, "conftest.lua");
	
  exit(0);

}


