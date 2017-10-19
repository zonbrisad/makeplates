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
 * - Constants
 * - API
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
#define LCT_TINT  int32_t
#define LCT_TDBL  double
#define LCT_TSTR  char*
#define LCT_TBOOL int

#define LCT_INT_MAX INT32_MAX
#define LCT_DBL_MAX DBL_MAX

#define LCT_INT_LIST_END LCT_INT_MAX
#define LCT_DBL_LIST_END LCT_DBL_MAX

#define LCT_INT_VLIST(...) {__VA_ARGS__, LCT_INT_MAX}
#define LCT_DBL_VLIST(...) {__VA_ARGS__, LCT_DBL_MAX}

#define LCT_TYPE2STR(type) LCT_int2string(type2string, type)
#define LCT_ERROR2STR(err) LCT_int2string(error2string, err)

#define LCT_INT(name, desc, flags, def, min, max)  { LCT_TYPE_INTEGER,    name, desc, flags | LCT_FLAG_PARAM, LCT_ERR_VALID, .data.intParam  = { 0, def, min, max, NULL, 0, NULL} }
#define LCT_INT_PL(name, desc, flags, def, vl)     { LCT_TYPE_INTEGER_PL, name, desc, flags | LCT_FLAG_PARAM, LCT_ERR_VALID, .data.intParam  = { 0, def, 0, 0, vl, 0, NULL } }
#define LCT_DBL(name, desc, flags, def, min, max)  { LCT_TYPE_DOUBLE,     name, desc, flags | LCT_FLAG_PARAM, LCT_ERR_VALID, .data.dblParam  = { 0, def, min, max, NULL, 0, NULL} }
#define LCT_DBL_PL(name, desc, flags, def, vl)     { LCT_TYPE_DOUBLE_PL,  name, desc, flags | LCT_FLAG_PARAM, LCT_ERR_VALID, .data.dblParam  = { 0, def, 0, 0, vl, 0, NULL} }
#define LCT_STR(name, desc, flags, def)            { LCT_TYPE_STRING,     name, desc, flags | LCT_FLAG_PARAM, LCT_ERR_VALID, .data.strParam  = { NULL, def, 0, NULL} }
#define LCT_BOOLEAN(name, desc, flags, def)        { LCT_TYPE_BOOLEAN,    name, desc, flags | LCT_FLAG_PARAM, LCT_ERR_VALID, .data.boolParam = { 0, def} }

#define LCT_INT_LIST(name, desc, flags, def, min, max)  { LCT_TYPE_INTEGER_LIST, name, desc, flags | LCT_FLAG_PARAM, LCT_ERR_VALID, .data.intParam = {0, def, min, max, NULL, 0, NULL} }
#define LCT_DBL_LIST(name, desc, flags, def, min, max)  { LCT_TYPE_DOUBLE_LIST,  name, desc, flags | LCT_FLAG_PARAM, LCT_ERR_VALID, .data.dblParam = {0, def, min, max, NULL, 0, NULL} }
#define LCT_STR_LIST(name, desc, flags, def)            { LCT_TYPE_STRING_LIST,  name, desc, flags | LCT_FLAG_PARAM, LCT_ERR_VALID, .data.strParam = {NULL, def, 0, NULL} }

#define LCT_TABLE(name, desc, params)       { LCT_TYPE_TABLE,      name, desc, LCT_FLAG_PARAM, LCT_ERR_VALID, .data.tableParam = {params}}
#define LCT_TABLE_LIST(name, desc, params)  { LCT_TYPE_TABLE_LIST, name, desc, LCT_FLAG_PARAM, LCT_ERR_VALID, .data.tableParam = {params}}

#define LCT_ARG_INT()      { LCT_TYPE_INTEGER,      "", NULL, LCT_FLAG_ARG, LCT_ERR_VALID, .data.boolParam = {0,0} }
#define LCT_ARG_DBL()      { LCT_TYPE_DOUBLE,       "", NULL, LCT_FLAG_ARG, LCT_ERR_VALID, .data.boolParam = {0,0} }
#define LCT_ARG_STR()      { LCT_TYPE_STRING,       "", NULL, LCT_FLAG_ARG, LCT_ERR_VALID, .data.boolParam = {0,0} }
#define LCT_ARG_INT_LIST() { LCT_TYPE_INTEGER_LIST, "", NULL, LCT_FLAG_ARG, LCT_ERR_VALID, .data.boolParam = {0,0} }
#define LCT_ARG_DBL_LIST() { LCT_TYPE_DOUBLE_LIST,  "", NULL, LCT_FLAG_ARG, LCT_ERR_VALID, .data.boolParam = {0,0} }
#define LCT_ARG_STR_LIST() { LCT_TYPE_STRING_LIST,  "", NULL, LCT_FLAG_ARG, LCT_ERR_VALID, .data.boolParam = {0,0} }
#define LCT_ARG_TABLE(tbl) { LCT_TYPE_TABLE,        "", NULL, LCT_FLAG_ARG, LCT_ERR_VALID, .data.tableParam = {tbl, 0, NULL} }

#define LCT_RET_INT()      { LCT_TYPE_INTEGER,          NULL, NULL, 0, LCT_ERR_VALID }

#define LCT_INTEGER_CONST(name, val) { LCT_TYPE_INTEGER_CONST, name, NULL, 0, LCT_ERR_VALID, .data.intParam={val, 0, 0, 0, NULL, 0, NULL} }
#define LCT_DOUBLE_CONST(name, val)  { LCT_TYPE_DOUBLE_CONST,  name, NULL, 0, LCT_ERR_VALID, .data.dblParam={val, 0, 0, 0, NULL,0, NULL} }
#define LCT_STRING_CONST(name, val)  { LCT_TYPE_STRING_CONST,  name, NULL, 0, LCT_ERR_VALID, .data.strParam={val, "", 0, NULL} }

#define LCT_GLOBAL_INT(name)     { LCT_TYPE_INTEGER, name, NULL, LCT_FLAG_PUSH|LCT_FLAG_PULL, LCT_ERR_VALID, .data.intParam  = {0,0,0,0,0 }    }
#define LCT_GLOBAL_DBL(name)     { LCT_TYPE_DOUBLE,  name, NULL, LCT_FLAG_PUSH|LCT_FLAG_PULL, LCT_ERR_VALID, .data.dblParam  = {0,0,0,0,0 }    }
#define LCT_GLOBAL_STR(name)     { LCT_TYPE_STRING,  name, NULL, LCT_FLAG_PUSH|LCT_FLAG_PULL, LCT_ERR_VALID, .data.strParam  = {NULL,NULL,0,NULL} }
#define LCT_GLOBAL_BOOLEAN(name) { LCT_TYPE_BOOLEAN, name, NULL, LCT_FLAG_PUSH|LCT_FLAG_PULL, LCT_ERR_VALID, .data.boolParam = {0,0} }

#define LCT_FUNCTION(name, params, returns)   { LCT_TYPE_FUNCTION, name, NULL, 0, LCT_ERR_VALID, .data.function={params, returns, 0, 0} }
#define LCT_API(name, params, function)       { LCT_TYPE_API,      name, NULL, 0, LCT_ERR_VALID, .data.api = {params, function} }

#define LCT_COMMENT(cmt)   {LCT_TYPE_COMMENT, "", cmt,  0, LCT_ERR_VALID, .data.boolParam = {0,0} }
#define LCT_LAST()         {LCT_TYPE_LAST,    "", NULL, 0, LCT_ERR_VALID, .data.boolParam = {0,0} }



#define LCT_IS_REQUIRED(param)    (param->flags & LCT_FLAG_REQUIRED)

#define PARAM_IS_INVALID(param)  (param->err  == LCT_ERR_INVALID)
#define PARAM_IS_VALID(param)    (param->err  == LCT_ERR_VALID)
#define PARAM_IS_COMMENT(param)  (param->type == LCT_TYPE_COMMENT)
#define PARAM_IS_FUNCTION(param) (param->type == LCT_TYPE_FUNCTION)
#define PARAM_IS_ARG(param)      (param->flags & LCT_FLAG_ARG)
#define PARAM_IS_MISSING(param)  (param->err  == LCT_ERR_MISSING)
#define IS_PARAM(param)          (param->flags & LCT_FLAG_PARAM)


// Typedefs ---------------------------------------------------------------

typedef enum {
    LCT_FLAG_REQUIRED = 0x0001,  //!< This parameter is required
    LCT_FLAG_VALIDATE = 0x0002,  //!< Indicates if parameter should be validated
    LCT_FLAG_PUSH     = 0x0004,  //!< Push global variable from c space to lua space
    LCT_FLAG_PULL     = 0x0008,  //!< Pull global variable  from lua space to c space
    LCT_FLAG_ARG      = 0x0010,  //!< Argument flag
    LCT_FLAG_PARAM    = 0x0020,  //!<
   	LCT_FLAG_GLOBAL   = 0x0020,  //!< Parameter is a global variable

} LCT_FLAGS;

typedef enum {
    LCT_ERR_VALID = 0,           //!< parameter has valid value
    LCT_ERR_INVALID,             //!< parameter has invalid value
    LCT_ERR_OUTOFBOUND,          //!< parameter value out of bound
    LCT_ERR_MISSING              //!< required parameter is missing
} LCT_ERR;

/**
 * Types of configuration elements
 */
typedef enum {
    LCT_TYPE_FIRST   = 0,
    LCT_TYPE_INTEGER = 0,        //!< Integer parameter
    LCT_TYPE_DOUBLE,             //!< Double parameter
    LCT_TYPE_STRING,             //!< String parameter
    LCT_TYPE_BOOLEAN,            //!< Boolean parameter

    LCT_TYPE_INTEGER_PL,         //!< Integer parameter pick list
    LCT_TYPE_DOUBLE_PL,          //!< Double parameter pick list

    LCT_TYPE_INTEGER_NL,         //!< Integer parameter name list
    LCT_TYPE_DOUBLE_NL,          //!< Double parameter name list

    LCT_TYPE_INTEGER_LIST,
    LCT_TYPE_DOUBLE_LIST,
    LCT_TYPE_STRING_LIST,
    LCT_TYPE_BOOLEAN_LIST,
    LCT_TYPE_BYTE_LIST,

    LCT_TYPE_LAST_PARAMETER,    //!< indicates last parameter type

    LCT_TYPE_INTEGER_CONST,     //!< Integer constant
    LCT_TYPE_DOUBLE_CONST,      //!< Double constant
    LCT_TYPE_STRING_CONST,      //!< String constant

    LCT_TYPE_TABLE,
    LCT_TYPE_TABLE_LIST,
    LCT_TYPE_COMMENT,

    LCT_TYPE_FUNCTION,
    LCT_TYPE_API,

    // Global variable types
    LCT_TYPE_GLOBAL_INTEGER,
    LCT_TYPE_GLOBAL_DOUBLE,
    LCT_TYPE_GLOBAL_STRING,
    LCT_TYPE_GLOBAL_BOOLEAN,


    LCT_TYPE_LAST,
} LCT_TYPES;


typedef struct luaConf luaConf;

typedef struct {
    LCT_TINT val;         //!< parameter value
    LCT_TINT default_val; //!< default value
    LCT_TINT min;         //!< min value of parameter
    LCT_TINT max;         //!< max value of parameter
    LCT_TINT *validList;  //!< list of valid values
    uint32_t length;      //!< Size of list
    LCT_TINT *list;       //!< list of valid values of parameter
} LCT_DATA_INTEGER;

typedef struct {
    LCT_TDBL val;         //!< parameter value
    LCT_TDBL default_val; //!< default value
    LCT_TDBL min;         //!< min value of parameter
    LCT_TDBL max;         //!< max value of parameter
    LCT_TDBL *validList;  //!< list of valid values
    uint32_t length;      //!< Size of list
    LCT_TDBL *list;       //!< list of valid values of parameter
} LCT_DATA_DOUBLE;

typedef struct {
    LCT_TSTR val;         //!< parameter value
    LCT_TSTR default_val; //!< default value
    uint32_t length;      //!< Size of list
    LCT_TSTR *list;       //!< list of valid values of parameter
} LCT_DATA_STRING;

typedef struct {
    LCT_TBOOL val;         //!< parameter value
    LCT_TBOOL default_val; //!< parameter value
} LCT_DATA_BOOLEAN;

typedef struct {
	luaConf *params;
	uint32_t length;
	void *list;
} LCT_DATA_TABLE;


typedef struct {
    luaConf *params;         //!< call parameters
    luaConf *returns;        //!< return values
    int p;                   //!< nr of parameters
    int r;                   //!< nr of returns
} LCT_DATA_FUNCTION;


typedef struct {
	luaConf *params;
    int (*function)(lua_State *);
} LCT_DATA_API;

typedef void (*intArgGet)(int *);


struct luaConf {
    LCT_TYPES    type;                     //!< parameter type
    char         name[LCT_NAME_LENGTH];    //!< parameter name
    char         *desc;                    //!< parameter description
    uint16_t     flags;                    //!< parameter control flags
    LCT_ERR       err;
    union {
        LCT_DATA_INTEGER     intParam;
        LCT_DATA_DOUBLE      dblParam;
        LCT_DATA_STRING      strParam;
        LCT_DATA_BOOLEAN     boolParam;
        LCT_DATA_TABLE       tableParam;
        LCT_DATA_FUNCTION    function;
        LCT_DATA_API         api;
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

/**
 * Create new configuration.
 *
 * @param params parameter list
 * @return configuration
 */
LCT *LCT_New(luaConf *params);

/**
 * Release memory from configuration.
 *
 * @param lct
 */
void LCT_Free(LCT *lct);

/**
 * Find a resource in parameter list.
 *
 * @param params List of parameters
 * @param name   Name of resource
 * @return
 */
luaConf *LCT_Find(luaConf *params, char *name);

/**
 * Find a function by name.
 *
 * @param lct configuration
 * @param name Function to be found
 * @return pointer to function parameter
 */
luaConf *LCT_FindFunction(LCT *lct, char *name);


void LCT_CallFunction(LCT *lct, luaConf *param);


void LCT_SetDefault(luaConf *param);
void LCT_SetDefaults(luaConf *params);

//void *LCT_GetValue(luaConf *param);
//
//void *LCT_GetList(luaConf *param, int *len);
//
//LCT_INT  LCT_GetInt(luaConf *param);
//LCT_DBL  LCT_GetDbl(luaConf *param);
//LCT_STR  LCT_GetStr(luaConf *param);
//LCT_BOOL LCT_GetBool(luaConf *param);


/**
 * Determine nr of parameters in array.
 *
 * @param params array of parameters
 * @return nr of parameters in array
 */
int LCT_Params(luaConf *params);



char* LCT_int2string(int2str *i2s, LCT_TYPES type);
char* LCT_intList2string(LCT_TINT ints[]);

/**
 * Get string representation of parameter value.
 *
 * @param param Parameter
 * @return Parameter value as string
 */
char* LCT_val2string(luaConf *param);

char* LCT_printProblem(luaConf *param);


/**
 * Print information about single parameter. If parameter is a table
 * each value in table will be printed.
 *
 * @param param parameter to be printed
 */
void LCT_PrintParam(luaConf *param);

/**
 * Print information of list of parameters.
 *
 * @param conf list of parameters
 */
void LCT_PrintParams(luaConf *conf);

char* LCT_paramLimits(luaConf *param);

int LCT_IsParam(luaConf *param);

void LCT_PrintParamFile(luaConf *param, FILE *f);

	
void LCT_File(luaConf *conf);


void LCT_SetValuePtr(luaConf *params, char *name, void *valPtr);


void LCT_ReadFile(LCT *lct, char *fileName);
void LCT_read(LCT *lct, char *confFile);


/**
 * Simple interface to call a function in lua space.
 *
 * @param lct configuration
 * @param funcName function to call
 * @param ... List of parameters to function
 * @return
 */
luaConf *LCT_FCallSimple(LCT *lct, char *funcName, ...);


void LCT_FCallSimple2(LCT *lct, char *funcName, char *format, ...);

void LCT_PrintProblems(luaConf *params);


/**
 * Test function.
 */
void LCT_Test(void);


void LCT_UnitTest(void);


#ifdef __cplusplus
} //end brace for extern "C"
#endif
#endif

