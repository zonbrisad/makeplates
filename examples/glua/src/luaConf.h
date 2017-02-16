/**
 *--------------------------------------------------------------------------- @brief   A simple lua configuration file library.
 *
 * @file    luaConf.h
 * @author  Your Name <your.name@yourdomain.org>
 * @date    2016-12-21
 * @licence GPLv2
 *
 *---------------------------------------------------------------------------
 */

#ifndef LUACONF_H
#define LUACONF_H

#ifdef __cplusplus
extern "C" {
#endif

// Includes ---------------------------------------------------------------
#include <stdint.h>

// Macros -----------------------------------------------------------------

#define LCT_INT  int
#define LCT_DBL  double
#define LCT_STR  char*
#define LCT_BOOL int


#define LC_IS_MISSING(param)  (param->err==LC_ERR_MISSING)
#define LC_IS_REQUIRED(param) (param->flags & LC_FLAG_REQUIRED)

#define LC_TYPE2STR(type) int2string(type2string, type)
#define LC_ERROR2STR(err) int2string(error2string, err)

#define LC_INT(name, desc, flags, def, min, max)  { LC_TYPE_INTEGER, name, desc, flags, LC_ERR_VALID, .data.intParam = {0, def, min, max, NULL} }
#define LC_INT_PL(name, desc, flags, def, ...)    { LC_TYPE_INTEGER, name, desc, flags, LC_ERR_VALID, .data.intParam = {0, def, 0, 0, {__VA_ARGS__,0xFFFF}}}

#define LC_DBL(name, desc, flags, def, min, max)  { LC_TYPE_DOUBLE,  name, desc, flags, LC_ERR_VALID, .data.dblParam = {0, def, min, max, NULL} }
#define LC_STR(name, desc, flags, def)            { LC_TYPE_STRING,  name, desc, flags, LC_ERR_VALID, .data.strParam = {NULL, NULL}       }

#define LCT_BOOLEAN(name, desc, flags, def)       { LC_TYPE_BOOLEAN, name, desc, flags, LC_ERR_VALID, .data.boolParam = {0, def}}

#define LC_INT_LIST(name, desc, flags, def, min, max)  { LC_TYPE_INTEGER_LIST, name, desc, flags, LC_ERR_VALID, .data.intParam = {0, def, min, max, NULL} }
#define LC_DBL_LIST(name, desc, flags, def, min, max)  { LC_TYPE_DOUBLE_LIST,  name, desc, flags, LC_ERR_VALID, .data.dblParam = {0, def, min, max, NULL} }

#define LC_LAST()  LC_TYPE_LAST

#define LCT_COMMENT(cmt)  {LC_TYPE_COMMENT, cmt}

#define LCT_INTEGER_CONST(name, val) { LC_TYPE_INTEGER_CONST, name, NULL, 0, LC_ERR_VALID, .data.intParam={val, 0, 0, 0} }
#define LCT_DOUBLE_CONST(name, val)  { LC_TYPE_DOUBLE_CONST,  name, NULL, 0, LC_ERR_VALID, .data.dblParam={val, 0, 0, 0} }
#define LCT_STRING_CONST(name, val)  { LC_TYPE_STRING_CONST,  name, NULL, 0, LC_ERR_VALID, .data.strParam={val, 0, 0, 0} }


#define PARAM_IS_INVALID(p)  (p->err  == LC_ERR_INVALID)
#define PARAM_IS_VALID(p)    (p->err  == LC_ERR_VALID)
#define PARAM_IS_COMMENT(p)  (p.type == LC_TYPE_COMMENT)

// Typedefs ---------------------------------------------------------------

typedef enum {
  LC_FLAG_REQUIRED = 0x0001,  // This parameter is required
} LC_FLAGS;

typedef enum {
  LC_ERR_VALID = 0,           // parameter has valid value
  LC_ERR_INVALID,             // parameter has invalid value
  LC_ERR_OUTOFBOUND,          // parameter value out of bound
  LC_ERR_MISSING              // required parameter is missing
} LC_ERR;

typedef enum {
  LC_TYPE_INTEGER,            // Integer parameter
  LC_TYPE_DOUBLE,             // Double parameter
  LC_TYPE_STRING,             // String parameter
  LC_TYPE_BOOLEAN,            // Boolean parameter

  LC_TYPE_INTEGER_LIST,
  LC_TYPE_DOUBLE_LIST,
  LC_TYPE_STRING_LIST,
  LC_TYPE_BOOLEAN_LIST,


  LC_TYPE_INTEGER_CONST,
  LC_TYPE_DOUBLE_CONST,
  LC_TYPE_STRING_CONST,

  LC_TYPE_CUSTOM,
  LC_TYPE_COMMENT,
  LC_TYPE_LAST,
} LC_TYPES;

typedef struct {
  LCT_INT val;         // parameter value
  LCT_INT default_val; // default value
  LCT_INT min;         // min value of parameter
  LCT_INT max;         // max value of parameter
  LCT_INT *validList;  // list of valid values
  uint32_t length;     // Size of list
  LCT_INT *list;       // list of valid values of parameter
} LUACONF_DATA_INTEGER;

typedef struct {
  LCT_DBL val;         // parameter value
  LCT_DBL default_val; // default value
  LCT_DBL min;         // min value of parameter
  LCT_DBL max;         // max value of parameter
  LCT_DBL *validList;  // list of valid values
  uint32_t length;     // Size of list
  LCT_DBL *list;       // list of valid values of parameter
} LUACONF_DATA_DOUBLE;

typedef struct {
  LCT_STR val;         // parameter value
  LCT_STR default_val; // default value
  LCT_STR *list;       // list of valid values of parameter
} LUACONF_DATA_STRING;

typedef struct {
  LCT_BOOL val;         // parameter value
  LCT_BOOL default_val; // parameter value
} LUACONF_DATA_BOOLEAN;

typedef struct {
  LC_TYPES     type;
  char         *name;
  char         *desc;
  uint16_t     flags;
  LC_ERR       err;
  union {
    LUACONF_DATA_INTEGER intParam;
    LUACONF_DATA_DOUBLE  dblParam;
    LUACONF_DATA_STRING  strParam;
    LUACONF_DATA_BOOLEAN boolParam;
  } data;

} luaConf;


typedef struct {
  int      type;
  char     *name;
} int2str;


// Variables --------------------------------------------------------------

// Functions --------------------------------------------------------------


void LC_Test(void);


#ifdef __cplusplus
} //end brace for extern "C"
#endif
#endif

