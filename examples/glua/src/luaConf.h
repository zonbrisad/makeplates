/**
 *---------------------------------------------------------------------------
 * @brief   A simple lua configuration file library.
 *
 * @file    luaConf.h
 * @author  Peter Malmberg <peter.malmberg@gmail.com>
 * @date    2016-12-21
 * @license LGPLv2
 *
 *---------------------------------------------------------------------------
 * Features.
 *
 * - Integer, Double, Boolean and string parameters
 * - List parameters
 * - Table parameters
 * - Value validation
 *
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

#define LC_INT(name, desc, flags, def, min, max)  { LC_TYPE_INTEGER,    name, desc, flags | LC_FLAG_PARAM, LC_ERR_VALID, .data.intParam  = { 0, def, min, max, NULL, 0, NULL} }
#define LC_INT_PL(name, desc, flags, def, vl)     { LC_TYPE_INTEGER_PL, name, desc, flags | LC_FLAG_PARAM, LC_ERR_VALID, .data.intParam  = { 0, def, 0, 0, vl, 0, NULL } }
#define LC_DBL(name, desc, flags, def, min, max)  { LC_TYPE_DOUBLE,     name, desc, flags | LC_FLAG_PARAM, LC_ERR_VALID, .data.dblParam  = { 0, def, min, max, NULL, 0, NULL} }
#define LC_DBL_PL(name, desc, flags, def, vl)     { LC_TYPE_DOUBLE_PL,  name, desc, flags | LC_FLAG_PARAM, LC_ERR_VALID, .data.dblParam  = { 0, def, 0, 0, vl, 0, NULL} }
#define LC_STR(name, desc, flags, def)            { LC_TYPE_STRING,     name, desc, flags | LC_FLAG_PARAM, LC_ERR_VALID, .data.strParam  = { NULL, def, 0, NULL} }
#define LCT_BOOLEAN(name, desc, flags, def)       { LC_TYPE_BOOLEAN,    name, desc, flags | LC_FLAG_PARAM, LC_ERR_VALID, .data.boolParam = { 0, def} }

#define LC_INT_LIST(name, desc, flags, def, min, max)  { LC_TYPE_INTEGER_LIST, name, desc, flags | LC_FLAG_PARAM, LC_ERR_VALID, .data.intParam = {0, def, min, max, NULL, 0, NULL} }
#define LC_DBL_LIST(name, desc, flags, def, min, max)  { LC_TYPE_DOUBLE_LIST,  name, desc, flags | LC_FLAG_PARAM, LC_ERR_VALID, .data.dblParam = {0, def, min, max, NULL, 0, NULL} }
#define LC_STR_LIST(name, desc, flags, def)            { LC_TYPE_STRING_LIST,  name, desc, flags | LC_FLAG_PARAM, LC_ERR_VALID, .data.strParam = {NULL, def, 0, NULL} }

#define LC_TABLE(name, params)       { LC_TYPE_TABLE,      name, NULL, LC_FLAG_PARAM, LC_ERR_VALID, .data.tableParam = {params}}
#define LC_TABLE_LIST(name, params)  { LC_TYPE_TABLE_LIST, name, NULL, LC_FLAG_PARAM, LC_ERR_VALID, .data.tableParam = {params}}

#define LC_ARG_INT()      { LC_TYPE_INTEGER,      "", NULL, LC_FLAG_ARG, LC_ERR_VALID }
#define LC_ARG_DBL()      { LC_TYPE_DOUBLE,       "", NULL, LC_FLAG_ARG, LC_ERR_VALID }
#define LC_ARG_STR()      { LC_TYPE_STRING,       "", NULL, LC_FLAG_ARG, LC_ERR_VALID }
#define LC_ARG_INT_LIST() { LC_TYPE_INTEGER_LIST, "", NULL, LC_FLAG_ARG, LC_ERR_VALID }
#define LC_ARG_DBL_LIST() { LC_TYPE_DOUBLE_LIST,  "", NULL, LC_FLAG_ARG, LC_ERR_VALID }
#define LC_ARG_STR_LIST() { LC_TYPE_STRING_LIST,  "", NULL, LC_FLAG_ARG, LC_ERR_VALID }
#define LC_ARG_TABLE(tbl) { LC_TYPE_TABLE,        "", NULL, LC_FLAG_ARG, LC_ERR_VALID, .data.tableParam = {tbl, 0, NULL} }

#define LC_RET_INT()      { LC_TYPE_INTEGER,          NULL, NULL, 0, LC_ERR_VALID }

#define LCT_INTEGER_CONST(name, val) { LC_TYPE_INTEGER_CONST, name, NULL, 0, LC_ERR_VALID, .data.intParam={val, 0, 0, 0, NULL, 0, NULL} }
#define LCT_DOUBLE_CONST(name, val)  { LC_TYPE_DOUBLE_CONST,  name, NULL, 0, LC_ERR_VALID, .data.dblParam={val, 0, 0, 0, NULL,0, NULL} }
#define LCT_STRING_CONST(name, val)  { LC_TYPE_STRING_CONST,  name, NULL, 0, LC_ERR_VALID, .data.strParam={val, "", 0, NULL} }

#define LC_GLOBAL_INT(name)     { LC_TYPE_INTEGER, name, NULL, LC_FLAG_PUSH|LC_FLAG_PULL, LC_ERR_VALID, .data.intParam  = {0,0,0,0,0 }    }
#define LC_GLOBAL_DBL(name)     { LC_TYPE_DOUBLE,  name, NULL, LC_FLAG_PUSH|LC_FLAG_PULL, LC_ERR_VALID, .data.dblParam  = {0,0,0,0,0 }    }
#define LC_GLOBAL_STR(name)     { LC_TYPE_STRING,  name, NULL, LC_FLAG_PUSH|LC_FLAG_PULL, LC_ERR_VALID, .data.strParam  = {NULL,NULL,0,NULL} }
#define LC_GLOBAL_BOOLEAN(name) { LC_TYPE_BOOLEAN, name, NULL, LC_FLAG_PUSH|LC_FLAG_PULL, LC_ERR_VALID, .data.boolParam = {0,0} }

#define LCT_FUNCTION(name, params, returns)   { LC_TYPE_FUNCTION, name, NULL, 0, LC_ERR_VALID, .data.function={params, returns, 0, 0} }
#define LCT_API(name, params, function)       { LC_TYPE_API,      name, NULL, 0, LC_ERR_VALID, .data.api = {params, function} }

#define LCT_COMMENT(cmt)  {LC_TYPE_COMMENT, cmt}
#define LC_LAST()  {LC_TYPE_LAST}

#define LC_IS_REQUIRED(param)    (param->flags & LC_FLAG_REQUIRED)

#define PARAM_IS_INVALID(param)  (param->err  == LC_ERR_INVALID)
#define PARAM_IS_VALID(param)    (param->err  == LC_ERR_VALID)
#define PARAM_IS_COMMENT(param)  (param->type == LC_TYPE_COMMENT)
#define PARAM_IS_FUNCTION(param) (param->type == LC_TYPE_FUNCTION)
#define PARAM_IS_ARG(param)      (param->flags & LC_FLAG_ARG)
#define PARAM_IS_MISSING(param)  (param->err  == LC_ERR_MISSING)
#define IS_PARAM(param)          (param->flags & LC_FLAG_PARAM)


// Typedefs ---------------------------------------------------------------

typedef enum {
    LC_FLAG_REQUIRED = 0x0001,  // This parameter is required
    LC_FLAG_VALIDATE = 0x0002,  // Indicates if parameter should be validated
    LC_FLAG_PUSH     = 0x0004,  // Push global variable from c space to lua space
    LC_FLAG_PULL     = 0x0008,  // Pull global variable  from lua space to c space
    LC_FLAG_ARG      = 0x0010,  // Argument flag
    LC_FLAG_PARAM    = 0x0020,  // Argument flag

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

    LC_TYPE_TABLE,
    LC_TYPE_TABLE_LIST,
    LC_TYPE_COMMENT,

    LC_TYPE_FUNCTION,
    LC_TYPE_API,

    // Global variable types
    LC_TYPE_GLOBAL_INTEGER,
    LC_TYPE_GLOBAL_DOUBLE,
    LC_TYPE_GLOBAL_STRING,
    LC_TYPE_GLOBAL_BOOLEAN,


    LC_TYPE_LAST,
} LC_TYPES;


typedef struct luaConf luaConf;

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
    uint32_t length;     // Size of list
    LCT_STR *list;       // list of valid values of parameter
} LUACONF_DATA_STRING;

typedef struct {
    LCT_BOOL val;         // parameter value
    LCT_BOOL default_val; // parameter value
} LUACONF_DATA_BOOLEAN;

typedef struct {
	luaConf *params;
    uint32_t length;
    void *list;
} LUACONF_DATA_TABLE;


typedef struct {
    luaConf *params;         // call parameters
    luaConf *returns;        // return values
    int p;                // nr of parameters
    int r;                // nr of returns
} LUACONF_DATA_FUNCTION;


typedef struct {
	luaConf *params;
    int (*function)(lua_State *);
} LUACONF_DATA_API;

typedef void (*intArgGet)(int *);


struct luaConf {
    LC_TYPES     type;                     // parameter type
    char         name[LCT_NAME_LENGTH];    // parameter name
    char         *desc;                    // parameter description
    uint16_t     flags;                    // parameter control flags
    LC_ERR       err;
    union {
        LUACONF_DATA_INTEGER     intParam;
        LUACONF_DATA_DOUBLE      dblParam;
        LUACONF_DATA_STRING      strParam;
        LUACONF_DATA_BOOLEAN     boolParam;
        LUACONF_DATA_TABLE       tableParam;
        LUACONF_DATA_FUNCTION    function;
        LUACONF_DATA_API         api;
    } data;
    void *valPtr;                          // pointer to parameter value
};

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

void LCT_Init(luaConf *params);

luaConf *LCT_Find(luaConf *params, char *name);

void LCT_CallFunction(LCT *lct, luaConf *param);


//void *LCT_GetValue(luaConf *param);
//
//void *LCT_GetList(luaConf *param, int *len);
//
//LCT_INT  LCT_GetInt(luaConf *param);
//LCT_DBL  LCT_GetDbl(luaConf *param);
//LCT_STR  LCT_GetStr(luaConf *param);
//LCT_BOOL LCT_GetBool(luaConf *param);

void LC_Test(void);

#ifdef __cplusplus
} //end brace for extern "C"
#endif
#endif

