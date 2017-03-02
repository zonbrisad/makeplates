/**
 *---------------------------------------------------------------------------
 * @brief   A simple lua configuration file library.
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
#include <float.h>

#include "lua.h"

// Macros -----------------------------------------------------------------


#define LCT_NAME_LENGTH 64

// LCT Types
#define LCT_INT  int32_t
#define LCT_DBL  double
#define LCT_STR  char*
#define LCT_BOOL int

#define LCT_INT_MAX INT32_MAX
#define LCT_DBL_MAX DBL_MAX

#define LCT_INT_LIST_END LCT_INT_MAX
#define LCT_DBL_LIST_END LCT_DBL_MAX

#define LCT_INT_VLIST(...) {__VA_ARGS__, LCT_INT_MAX}
#define LCT_DBL_VLIST(...) {__VA_ARGS__, LCT_DBL_MAX}


#define LC_TYPE2STR(type) int2string(type2string, type)
#define LC_ERROR2STR(err) int2string(error2string, err)

#define LC_INT(name, desc, flags, def, min, max)  { LC_TYPE_INTEGER,    name, desc, flags, LC_ERR_VALID, .data.intParam  = { 0, def, min, max, NULL} }
#define LC_INT_PL(name, desc, flags, def, vl)     { LC_TYPE_INTEGER_PL, name, desc, flags, LC_ERR_VALID, .data.intParam  = { 0, def, 0, 0, vl} }
#define LC_DBL(name, desc, flags, def, min, max)  { LC_TYPE_DOUBLE,     name, desc, flags, LC_ERR_VALID, .data.dblParam  = { 0, def, min, max, NULL} }
#define LC_DBL_PL(name, desc, flags, def, vl)     { LC_TYPE_DOUBLE_PL,  name, desc, flags, LC_ERR_VALID, .data.dblParam  = { 0, def, 0, 0, vl} }
#define LC_STR(name, desc, flags, def)            { LC_TYPE_STRING,     name, desc, flags, LC_ERR_VALID, .data.strParam  = { NULL, def} }
#define LCT_BOOLEAN(name, desc, flags, def)       { LC_TYPE_BOOLEAN,    name, desc, flags, LC_ERR_VALID, .data.boolParam = { 0, def} }

#define LC_INT_LIST(name, desc, flags, def, min, max)  { LC_TYPE_INTEGER_LIST, name, desc, flags, LC_ERR_VALID, .data.intParam = {0, def, min, max, NULL} }
#define LC_DBL_LIST(name, desc, flags, def, min, max)  { LC_TYPE_DOUBLE_LIST,  name, desc, flags, LC_ERR_VALID, .data.dblParam = {0, def, min, max, NULL} }
#define LC_STR_LIST(name, desc, flags, def)            { LC_TYPE_STRING_LIST,  name, desc, flags, LC_ERR_VALID, .data.strParam = {NULL, def} }

#define LC_CUSTOM(name, params)       {LC_TYPE_CUSTOM,      name, NULL, 0, LC_ERR_VALID, .data.customParam = {params}}
#define LC_CUSTOM_LIST(name, params)  {LC_TYPE_CUSTOM_LIST, name, NULL, 0, LC_ERR_VALID, .data.customParam = {params}}

#define LC_LAST()  {LC_TYPE_LAST}

#define LCT_COMMENT(cmt)  {LC_TYPE_COMMENT, cmt}

#define LCT_INTEGER_CONST(name, val) { LC_TYPE_INTEGER_CONST, name, NULL, 0, LC_ERR_VALID, .data.intParam={val, 0, 0, 0, NULL} }
#define LCT_DOUBLE_CONST(name, val)  { LC_TYPE_DOUBLE_CONST,  name, NULL, 0, LC_ERR_VALID, .data.dblParam={val, 0, 0, 0, NULL} }
#define LCT_STRING_CONST(name, val)  { LC_TYPE_STRING_CONST,  name, NULL, 0, LC_ERR_VALID, .data.strParam={val, "", NULL} }

#define LC_IS_REQUIRED(param)    (param->flags & LC_FLAG_REQUIRED)

#define PARAM_IS_INVALID(param)  (param->err  == LC_ERR_INVALID)
#define PARAM_IS_VALID(param)    (param->err  == LC_ERR_VALID)
#define PARAM_IS_COMMENT(param)  (param->type == LC_TYPE_COMMENT)
#define PARAM_IS_FUNCTION(param) (param->type == LC_TYPE_FUNCTION)
#define IS_PARAM(param)          ((param->type >= LC_TYPE_FIRST) && ((param->type < LC_TYPE_LAST_PARAMETER)))

#define LCT_FUNCTION(name, params) { LC_TYPE_FUNCTION, name, NULL, 0, LC_ERR_VALID, .data.function={params}}

#define LC_ARG_INT()      { LC_TYPE_ARG_INTEGER,      NULL, NULL, 0, LC_ERR_VALID }
#define LC_ARG_DBL()      { LC_TYPE_ARG_DOUBLE,       NULL, NULL, 0, LC_ERR_VALID }
#define LC_ARG_STR()      { LC_TYPE_ARG_STRING,       NULL, NULL, 0, LC_ERR_VALID }
#define LC_ARG_INT_LIST() { LC_TYPE_ARG_INTEGER_LIST, NULL, NULL, 0, LC_ERR_VALID }
#define LC_ARG_DBL_LIST() { LC_TYPE_ARG_DOUBLE_LIST,  NULL, NULL, 0, LC_ERR_VALID }
#define LC_ARG_TABLE(tbl) { LC_TYPE_CUSTOM,           NULL, NULL, 0, LC_ERR_VALID, .data.customParam = {tbl}}

#define LC_RET_INT()      { LC_TYPE_INTEGER,          NULL, NULL, 0, LC_ERR_VALID }

#define LC_GLOBAL_INT(name)     { LC_TYPE_INTEGER, name, NULL, LC_FLAG_PUSH|LC_FLAG_PULL, LC_ERR_VALID, .data.intParam  = {0,0,0,0,0} }
#define LC_GLOBAL_DBL(name)     { LC_TYPE_DOUBLE,  name, NULL, LC_FLAG_PUSH|LC_FLAG_PULL, LC_ERR_VALID, .data.dblParam  = {0,0,0,0,0} }
#define LC_GLOBAL_STR(name)     { LC_TYPE_STRING,  name, NULL, LC_FLAG_PUSH|LC_FLAG_PULL, LC_ERR_VALID, .data.strParam  = {NULL,0,0,0,0} }
#define LC_GLOBAL_BOOLEAN(name) { LC_TYPE_BOOLEAN, name, NULL, LC_FLAG_PUSH|LC_FLAG_PULL, LC_ERR_VALID, .data.boolParam = {0,0,0,0,0} }

#define LCT_API(name, params, function) { LC_TYPE_API, name, NULL, 0, LC_ERR_VALID, .data.api = {params, function} }

// Typedefs ---------------------------------------------------------------

typedef enum {
    LC_FLAG_REQUIRED = 0x0001,  // This parameter is required
    LC_FLAG_GLOBAL   = 0x0002,  // This parameter is global variable
    LC_FLAG_PUSH     = 0x0004,  // Push global variable from c space to lua space
    LC_FLAG_PULL     = 0x0008,  // Pull global variable  from lua space to c space
} LC_FLAGS;

typedef enum {
    LC_ERR_VALID = 0,           // parameter has valid value
    LC_ERR_INVALID,             // parameter has invalid value
    LC_ERR_OUTOFBOUND,          // parameter value out of bound
    LC_ERR_MISSING              // required parameter is missing
} LC_ERR;

typedef enum {
    LC_TYPE_FIRST   = 0,
    LC_TYPE_INTEGER = 0,        // Integer parameter
    LC_TYPE_DOUBLE,             // Double parameter
    LC_TYPE_STRING,             // String parameter
    LC_TYPE_BOOLEAN,            // Boolean parameter

    LC_TYPE_INTEGER_PL,         // Integer parameter pick list
    LC_TYPE_DOUBLE_PL,          // Double parameter pick list

    LC_TYPE_INTEGER_NL,         // Integer parameter name list
    LC_TYPE_DOUBLE_NL,          // Double parameter name list

    LC_TYPE_INTEGER_LIST,
    LC_TYPE_DOUBLE_LIST,
    LC_TYPE_STRING_LIST,
    LC_TYPE_BOOLEAN_LIST,
    LC_TYPE_BYTE_LIST,

    LC_TYPE_LAST_PARAMETER,    // indicates last parameter type

    LC_TYPE_INTEGER_CONST,
    LC_TYPE_DOUBLE_CONST,
    LC_TYPE_STRING_CONST,

    LC_TYPE_CUSTOM,
    LC_TYPE_CUSTOM_LIST,
    LC_TYPE_COMMENT,

    LC_TYPE_FUNCTION,
	LC_TYPE_API,

    LC_TYPE_ARG_INTEGER,
    LC_TYPE_ARG_DOUBLE,
    LC_TYPE_ARG_STRING,
    LC_TYPE_ARG_INTEGER_LIST,
    LC_TYPE_ARG_DOUBLE_LIST,
    LC_TYPE_ARG_STRING_LIST,

	// Global variable types
    LC_TYPE_GLOBAL_INTEGER,
    LC_TYPE_GLOBAL_DOUBLE,
    LC_TYPE_GLOBAL_STRING,
    LC_TYPE_GLOBAL_BOOLEAN,


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
    void *params;
    uint32_t length;
    void *list;
} LUACONF_DATA_CUSTOM;

typedef struct {
    void *params;
} LUACONF_DATA_FUNCTION;

typedef struct {
    void *params;
    void (*function)(void*);
} LUACONF_DATA_API;

typedef void (*intArgGet)(int *);

typedef struct {
    LCT_INT  val;
    LCT_INT *pVal;
    intArgGet getVal;
} LUACONF_DATA_ARG_INTEGER;

typedef struct {
    LCT_DBL  val;
    LCT_INT *pVal;
    intArgGet getVal;
} LUACONF_DATA_ARG_DOUBLE;

typedef struct {
    LCT_STR  val;
    LCT_INT *pVal;
    intArgGet getVal;
} LUACONF_DATA_ARG_STRING;

typedef struct {
    LC_TYPES     type;
    char         name[LCT_NAME_LENGTH];
    char         *desc;
    uint16_t     flags;
    LC_ERR       err;
    union {
        LUACONF_DATA_INTEGER     intParam;
        LUACONF_DATA_DOUBLE      dblParam;
        LUACONF_DATA_STRING      strParam;
        LUACONF_DATA_BOOLEAN     boolParam;
        LUACONF_DATA_CUSTOM      customParam;
        LUACONF_DATA_FUNCTION    function;
        LUACONF_DATA_API         api;
        LUACONF_DATA_ARG_INTEGER intArg;
        LUACONF_DATA_ARG_DOUBLE  dblArg;
        LUACONF_DATA_ARG_STRING  strArg;
    } data;
    void *valPtr;
} luaConf;

typedef struct {
    lua_State *L;
    luaConf   *params;
} LCT;

typedef struct {
    int      type;
    char     *name;
} int2str;

typedef struct {
    double   type;
    char     *name;
} dbl2str;


// Variables --------------------------------------------------------------

// Functions --------------------------------------------------------------


LCT *LCT_New(luaConf *params);

void LCT_CallFunction(LCT *lct, luaConf *param);

void LC_Test(void);


#ifdef __cplusplus
} //end brace for extern "C"
#endif
#endif

