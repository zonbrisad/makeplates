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
 * - value validation
 * - custom datatype
 *
 * https://www.lua.org/pil/25.html
 */

// Macros -----------------------------------------------------------------

// Variables --------------------------------------------------------------

char *lct_trueList[]  = { "ON",  "On",  "on",  "YES", "Yes", "yes", "TRUE",  "True",  "true",   NULL };
char *lct_falseList[] = { "OFF", "Off", "off", "NO",  "No",  "no",  "FALSE", "False", "false",  NULL };


int2str type2string[] = {
    {LC_TYPE_INTEGER,       "Integer"},
    {LC_TYPE_DOUBLE,        "Double"},
    {LC_TYPE_STRING,        "String"},
    {LC_TYPE_BOOLEAN,       "Boolean"},
    {LC_TYPE_INTEGER_LIST,  "Integer List"},
    {LC_TYPE_DOUBLE_LIST,   "Double List"},
    {LC_TYPE_INTEGER_CONST, "Integer constant"},
    {LC_TYPE_DOUBLE_CONST,  "Double constant"},
    {LC_TYPE_STRING_CONST,  "String constant"},
    {LC_TYPE_INTEGER_PL,    "Integer pick list"},
    {LC_TYPE_INTEGER_NL,    "Integer name list"},
    {LC_TYPE_DOUBLE_PL,     "Double pick list"},
    {LC_TYPE_DOUBLE_NL,     "Double name list"},
    {LC_TYPE_COMMENT,       "Comment"},
    {LC_TYPE_LAST,          NULL}
};

int2str error2string[] = {
    {LC_ERR_VALID,      "Valid"},
    {LC_ERR_INVALID,    "Invalid"},
    {LC_ERR_OUTOFBOUND, "OutOfBound"},
    {LC_ERR_MISSING,    "Missing"},
};


// Prototypes -------------------------------------------------------------

// Code -------------------------------------------------------------------



char *int2string(int2str *i2s, LC_TYPES type) {
    int i;
    i = 0;

    while (i2s[i].type != type) {
        i++;

        if (i2s[i].type == LC_TYPE_LAST) {
            return NULL;
        }
    }

    return i2s[i].name;
}

char *intList2string(LCT_INT ints[]) {

}

char *val2string(luaConf *param) {
    static char buf[2048];
    char *bp;
    int i;

    if (!PARAM_IS_VALID(param)) {
        return "";
    }

    switch (param->type) {
        case LC_TYPE_BOOLEAN:
            sprintf(buf, "%d",    param->data.boolParam.val);
            break;

        case LC_TYPE_INTEGER:
            sprintf(buf, "%d",    param->data.intParam.val);
            break;

        case LC_TYPE_DOUBLE:
            sprintf(buf, "%8.2f", param->data.dblParam.val);
            break;

        case LC_TYPE_STRING:
            return param->data.strParam.val;

        case LC_TYPE_INTEGER_LIST:
            bp = buf;

            for (i = 0; i < param->data.intParam.length; i++) {
                //printf("%d ", param->data.intParam.list[i]);
                sprintf(bp, "%d ", param->data.intParam.list[i]);
                bp += strlen(bp);
            }

            break;

        case LC_TYPE_DOUBLE_LIST:
            bp = buf;

            for (i = 0; i < param->data.dblParam.length; i++) {
                sprintf(bp, "%.2lf ", param->data.dblParam.list[i]);
                bp += strlen(bp);
            }

            break;

        default:
            return "";
    }

    return buf;
}

#define IS_PARAM(param)  ((param->type >= LC_TYPE_FIRST) && ((param->type < LC_TYPE_LAST_PARAMETER)))

char *LCT_paramLimits(luaConf *param) {
    static char buf[1024];
    int i;
    char *p;

    switch (param->type) {
        case LC_TYPE_INTEGER:
            if (param->data.intParam.min == param->data.intParam.max) {
                sprintf(buf, "no limit");
            } else {
                sprintf(buf, "%d %d", param->data.intParam.min, param->data.intParam.max);
            }

            break;

        case LC_TYPE_DOUBLE:
            if (param->data.dblParam.min == param->data.dblParam.max) {
                sprintf(buf, "no limit");
            } else {
                sprintf(buf, "%0.2f %0.2f", param->data.dblParam.min, param->data.dblParam.max);
            }

            break;

        case LC_TYPE_INTEGER_PL:
            i = 0;
            p = buf;

            while (param->data.intParam.validList[i] != LCT_INT_MAX) {
                sprintf(p, "%d ", param->data.intParam.validList[i]);
                p += strlen(p);
                i++;
            }

            break;

        case LC_TYPE_DOUBLE_PL:
            i = 0;
            p = buf;

            while (param->data.dblParam.validList[i] != LCT_DBL_MAX) {
                sprintf(p, "%.2f ", param->data.dblParam.validList[i]);
                p += strlen(p);
                i++;
            }

            break;

        default:
            return NULL;
            //sprintf(buf, "");
    }


    return buf;
}

char *LCT_printProblem(luaConf *param) {
    static char msg[256];

    if (!IS_PARAM(param)) {
        sprintf(msg, "");
        return msg;
    }

    if (PARAM_IS_VALID(param)) {
        sprintf(msg, "Parameter %s has a valid value.", param->name);
    }

    switch (param->err) {
        case LC_ERR_OUTOFBOUND:
            sprintf(msg, "Parameter %s is out of bound. [ %s ]", param->name, LCT_paramLimits(param));
            break;

        case LC_ERR_INVALID:
            sprintf(msg, "Parameter %s has a invalid value.", param->name);
            break;

        case LC_ERR_MISSING:
            sprintf(msg, "Parameter %s is missing.", param->name);
            break;

        default:
            sprintf(msg, "");
            break;
    }

    return msg;
}


void printParam(luaConf *param) {
    printf("Name: %s\n", param->name);
    printf("Desc: %s\n", param->desc);
    printf("Type: %s\n", LC_TYPE2STR(param->type));
    printf("Val:  %s\n", val2string(param));
}

void printParams(luaConf *conf) {
    int i;
    i = 0;

    while (conf[i].type != LC_TYPE_LAST) {
        printParam(&conf[i]);
        printf("\n");
//    printf("%20s %s\n", conf[i].varName, conf[i].desc);
        i++;
    }
}

void LC_File(luaConf *conf) {
    int i;

    i = 0;

    while (conf[i].type != LC_TYPE_LAST) {
        printf("-- %s\n", conf[i].desc);
        printf("%s = %s\n\n", conf[i].name, val2string(&conf[i]));
        i++;
    }
}

void LC_validate(luaConf *param) {
    int i;

    switch (param->type) {
        case LC_TYPE_BOOLEAN:
            break;

        case LC_TYPE_INTEGER:

            // check if value is within limits
            if (param->data.intParam.min != param->data.intParam.max) {
                if (!((param->data.intParam.val >= param->data.intParam.min) && (param->data.intParam.val <= param->data.intParam.max))) {
                    param->err = LC_ERR_OUTOFBOUND;
                }
            }

            if (param->data.intParam.validList != NULL) {
                param->err = LC_ERR_INVALID;
                i = 0;

                while (param->data.intParam.validList[i] != LCT_INT_MAX) {
                    if (param->data.intParam.val == param->data.intParam.validList[i]) {
                        param->err = LC_ERR_VALID;
                    }

                    i++;
                }
            }

            break;

        case LC_TYPE_DOUBLE:

            // check if value is within limits
            if (param->data.dblParam.min != param->data.dblParam.max) {
                if (!((param->data.dblParam.val >= param->data.dblParam.min) && (param->data.dblParam.val <= param->data.dblParam.max))) {
                    param->err = LC_ERR_OUTOFBOUND;
                }
            }

            if (param->data.dblParam.validList != NULL) {
                param->err = LC_ERR_INVALID;
                i = 0;

                while (param->data.dblParam.validList[i] != LCT_DBL_MAX) {
                    if (param->data.dblParam.val == param->data.dblParam.validList[i]) {
                        param->err = LC_ERR_VALID;
                    }

                    i++;
                }
            }

            break;

        case LC_TYPE_STRING:
            break;

        default:
            break;
    }
}

void LCT_Constants(lua_State *L, luaConf *conf) {
    int i;
    static char buf[512];

    i = 0;

    while (lct_falseList[i] != NULL) {
        sprintf(buf, "%s=1", lct_falseList[i]);
        luaL_dostring(L, buf);
        i++;
    }

    i = 0;

    while (lct_trueList[i] != NULL) {
        sprintf(buf, "%s=1", lct_trueList[i]);
        printf("%s\n", buf);
        luaL_dostring(L, buf);
        i++;
    }


    i = 0;

    while (conf[i].type != LC_TYPE_LAST) {
        switch (conf[i].type) {
            case LC_TYPE_INTEGER_CONST:
                sprintf(buf, "%s=%d", conf[i].name, conf[i].data.intParam.val);
                luaL_dostring(L, buf);
                break;

            case LC_TYPE_DOUBLE_CONST:
                sprintf(buf, "%s=%f", conf[i].name, conf[i].data.dblParam.val);
                luaL_dostring(L, buf);
                break;

            case LC_TYPE_STRING_CONST:
                sprintf(buf, "%s=\"%s\"", conf[i].name, conf[i].data.strParam.val);
                luaL_dostring(L, buf);
                break;

            default:
                break;
        }

        i++;
    }
}

void LC_read(luaConf *params, char *confFile) {
    lua_State *L;
    int i, j, l;
    int isnum;
    const char *s;

    L = luaL_newstate();
    luaL_openlibs(L);

    LCT_Constants(L, params);

    luaL_dofile(L, confFile);

    isnum = 1;
    i = 0;

    while (params[i].type != LC_TYPE_LAST) {
        //DEBUGPRINT("i=%d name=%s\n", i, conf[i].name);

        if (!PARAM_IS_COMMENT(params[i])) {

            // push identifier onto stack
            lua_getglobal(L, params[i].name);

            // check if identifier exists
            if (lua_isnil(L, -1)) {
                params[i].err = LC_ERR_MISSING;
            } else {

                switch (params[i].type) {
                    case LC_TYPE_BOOLEAN:
                        params[i].data.boolParam.val = (LCT_BOOL) lua_tonumberx(L, -1, &isnum);

                        if (!isnum) {
                            params[i].err = LC_ERR_INVALID;
                        }

                        break;

                    case LC_TYPE_INTEGER:
                    case LC_TYPE_INTEGER_PL:
                    case LC_TYPE_INTEGER_NL:
                        params[i].data.intParam.val = (LCT_INT) lua_tonumberx(L, -1, &isnum);

                        if (!isnum) {
                            params[i].err = LC_ERR_INVALID;
                        }

                        break;

                    case LC_TYPE_DOUBLE:
                    case LC_TYPE_DOUBLE_PL:
                    case LC_TYPE_DOUBLE_NL:
                        params[i].data.dblParam.val = (LCT_DBL) lua_tonumberx(L, -1, &isnum);

                        if (!isnum) {
                            params[i].err = LC_ERR_INVALID;
                        }

                        break;

                    case LC_TYPE_STRING:
                        if (!lua_isstring(L, -1)) {
                            params[i].err = LC_ERR_INVALID;
                            break;
                        }

                        lua_tonumberx(L, -1, &isnum);

                        if (isnum) {
                            params[i].err = LC_ERR_INVALID;
                            break;
                        }

                        s = lua_tostring(L, -1);

                        if (s == NULL) {
                            params[i].err = LC_ERR_INVALID;
                            break;
                        }

                        //printf("String: %s\n",s);
                        params[i].data.strParam.val = malloc(  strlen(s) + 10 );
                        params[i].data.strParam.val[0] = '\0';
                        strcpy(params[i].data.strParam.val, s);
                        break;

                    case LC_TYPE_INTEGER_LIST:

                        // check if value is a table
                        if (!lua_istable(L, -1)) {
                            params[i].err = LC_ERR_INVALID;
                            break;
                        }

                        // get length of list
                        l = lua_rawlen(L, -1);

                        params[i].data.intParam.list = malloc( sizeof(LCT_INT) * l);
                        params[i].data.intParam.length = l;

                        for (j = 1; j <= l; j++) {
                            lua_rawgeti(L, -1, j);
                            //printf("Int List %d\n", (LCT_INT) lua_tonumberx(L, -1, &isnum));
                            params[i].data.intParam.list[j - 1] = (LCT_INT) lua_tonumberx(L, -1, &isnum);
                            lua_pop(L, 1);
                        }

                        break;

                    case LC_TYPE_DOUBLE_LIST:

                        // check if value is a table
                        if (!lua_istable(L, -1)) {
                            params[i].err = LC_ERR_INVALID;
                            break;
                        }

                        // get length of list
                        l = lua_rawlen(L, -1);
                        params[i].data.dblParam.list = malloc( sizeof(LCT_DBL) * l);
                        params[i].data.dblParam.length = l;

                        for (j = 1; j <= l; j++) {
                            lua_rawgeti(L, -1, j);
                            //printf("Dbl List %f\n", (LCT_DBL) lua_tonumberx(L, -1, &isnum));
                            params[i].data.dblParam.list[j - 1] = (LCT_DBL) lua_tonumberx(L, -1, &isnum);
                            lua_pop(L, 1);
                        }

                        break;
                    case LC_TYPE_CUSTOM:
                    	  if (!lua_istable(L, -1)) {
                    		  params[i].err = LC_ERR_INVALID;
                    		  break;
                    	  }

                    	break;

                    default:
                        break;
                }

                LC_validate(&params[i]);

            }
        }

        printf("%-20s %-18s %-10s  %10s [ %s ]\n", params[i].name, LC_TYPE2STR(params[i].type), LC_ERROR2STR(params[i].err), val2string(&params[i]), LCT_paramLimits(&params[i]));
        i++;
    }

    lua_close(L);
}



// Test code ---------------------------------------------------------

LCT_INT_VLIST(validIntList,  5, 9, 12, 42, 193, 104, -4120);

LCT_DBL_VLIST(validDblList, 5.5, -9.23, 14.94, 42.42, -1401.43, 0);


luaConf confTest[] = {
    LCT_COMMENT("This is a comment"),
    LC_INT("IntParam1",        "Correct Integer parameter",       0, -42, 0, 0),
    LC_INT("IntParam2",        "Correct Integer parameter",       0, 0, 0, 0),
    LC_INT("IntParam3",        "Correct Integer parameter",       0, 0, 0, 0),
    LC_INT_PL("IntParam4",     "Int parameter pick list valid value", 0, 0,   validIntList),
    LC_INT_PL("IntParam5",     "Int parameter pick list invalid value", 0, 0, validIntList),
    LC_INT("IntParamInvalid1", "Integer parameter value invalid", 0, 0, 0, 0),
    LC_INT("IntParamInvalid2", "Integer parameter value to low",  0, 0, 0, 100),
    LC_INT("IntParamInvalid3", "Integer parameter value to high", 0, 0, 0, 100),
    LC_DBL("DblParam1",        "Correct Double parameter",        0, 0, 0, 0),
    LC_DBL("DblParam2",        "Correct Double parameter",        0, 0, 0, 0),
    LC_DBL("DblParam3",        "Correct Double parameter",        0, 0, 0, 0),
    LC_DBL("DblParamInvalid1", "Double parameter value invalid",  0, 0, 0, 0),
    LC_DBL("DblParamInvalid2", "Double parameter value to low",   0, 0, 1, 100),
    LC_DBL("DblParamInvalid3", "Double parameter value to high",  0, 0, 1, 100),
    LC_DBL_PL("DblParam4",     "Double parameter pick list valid values", 0, 0, validDblList),
    LC_DBL_PL("DblParam5",     "Double parameter pick list valid values", 0, 0, validDblList),
    LC_STR("StrParam1",        "Correct String parameter",        0, ""),
    LC_STR("StrParam2",        "Correct String parameter",        0, ""),
    LC_STR("StrParam3",        "Test of string constant parameter", 0, ""),
    LC_STR("StrParamInvalid1", "Invalid String parameter",        0, ""),
    LCT_BOOLEAN("BoolParam1",  "Boolean parameter",               0, 0),
    LCT_BOOLEAN("BoolParam2",  "Boolean parameter",               0, 0),
    LC_STR("BoolParamTrue",    "Test of all true parameters",     0, ""),
    LC_STR("BoolParamFalse",   "Test of all false parameters",    0, ""),
    LC_DBL("MissingParam",     "Missing parameter",               0, 0, 0, 0),
    LC_INT_LIST("IntList",     "Integer List parameter",          0, 0, 0 , 0),
    LC_DBL_LIST("DblList",     "Double List parameter",           0, 0, 0 , 0),
    LC_INT_LIST("InvalidList", "Invalid Integer List",            0, 0, 0 , 0),
    LCT_INTEGER_CONST("IntConst", 32),
    LCT_DOUBLE_CONST("DblConst",  32.23),
    LCT_STRING_CONST("StrConst",  "A little string constant"),
    {LC_LAST()},

};


void LCT_PrintProblems(luaConf *params) {
    int i;
    i = 0;
    luaConf *param;

    while (params[i].type != LC_TYPE_LAST) {
        param = &params[i];

        if (IS_PARAM(param) && !PARAM_IS_VALID(param)) {
            printf("%s\n", LCT_printProblem(param));
        }

        i++;
    }
}

void LC_Test(void) {

    LC_File(confTest);

    LC_read(confTest, "conftest.lua");

    LCT_PrintProblems(confTest);

    exit(0);

}


