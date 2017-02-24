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
    return NULL;
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

        case LC_TYPE_INTEGER_CONST:
        case LC_TYPE_INTEGER_PL:
        case LC_TYPE_INTEGER:
            sprintf(buf, "%d",    param->data.intParam.val);
            break;

        case LC_TYPE_DOUBLE_CONST:
        case LC_TYPE_DOUBLE_PL:
        case LC_TYPE_DOUBLE:
            sprintf(buf, "%8.2f", param->data.dblParam.val);
            break;

        case LC_TYPE_STRING_CONST:
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
        msg[0] = '\0';
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
            msg[0] = '\0';
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

void LC_PrintParam(luaConf *param) {
    printf("%-20s %-18s %-10s  %10s [ %s ]\n", param->name, LC_TYPE2STR(param->type), LC_ERROR2STR(param->err), val2string(param), LCT_paramLimits(param));
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

            break;

        case LC_TYPE_INTEGER_PL:

            if (param->data.intParam.validList != NULL) {
                param->err = LC_ERR_OUTOFBOUND;
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
            if (param->data.dblParam.min != param->data.dblParam.max)  {
                if (!((param->data.dblParam.val >= param->data.dblParam.min) && (param->data.dblParam.val <= param->data.dblParam.max))) {
                    param->err = LC_ERR_OUTOFBOUND;
                }
            }

            break;

        case LC_TYPE_DOUBLE_PL:
            if (param->data.dblParam.validList != NULL) {
                param->err = LC_ERR_OUTOFBOUND;
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


void LC_GetValue(LCT *lct, luaConf *param, int stackPos) {
    int isnum;
    int j, l;
    const char *s;
    luaConf *p;

    switch (param->type) {
        case LC_TYPE_BOOLEAN:
            param->data.boolParam.val = (LCT_BOOL) lua_tonumberx(lct->L, stackPos, &isnum);

            if (!isnum) {
                param->err = LC_ERR_INVALID;
            }

            break;

        case LC_TYPE_INTEGER:
        case LC_TYPE_INTEGER_PL:
        case LC_TYPE_INTEGER_NL:
            param->data.intParam.val = (LCT_INT) lua_tonumberx(lct->L, stackPos, &isnum);

            if (!isnum) {
                param->err = LC_ERR_INVALID;
            }

            break;

        case LC_TYPE_DOUBLE:
        case LC_TYPE_DOUBLE_PL:
        case LC_TYPE_DOUBLE_NL:
            param->data.dblParam.val = (LCT_DBL) lua_tonumberx(lct->L, stackPos, &isnum);

            if (!isnum) {
                param->err = LC_ERR_INVALID;
            }

            break;

        case LC_TYPE_STRING:
            if (!lua_isstring(lct->L, stackPos)) {
                param->err = LC_ERR_INVALID;
                break;
            }

            lua_tonumberx(lct->L, stackPos, &isnum);

            if (isnum) {
                param->err = LC_ERR_INVALID;
                break;
            }

            s = lua_tostring(lct->L, stackPos);

            if (s == NULL) {
                param->err = LC_ERR_INVALID;
                break;
            }

            //printf("String: %s\n",s);
            param->data.strParam.val = malloc(  strlen(s) + 10 );
            param->data.strParam.val[0] = '\0';
            strcpy(param->data.strParam.val, s);
            break;

        case LC_TYPE_INTEGER_LIST:

            // check if value is a table
            if (!lua_istable(lct->L, stackPos)) {
                param->err = LC_ERR_INVALID;
                break;
            }

            // get length of list
            l = lua_rawlen(lct->L, -1);

            param->data.intParam.list = malloc( sizeof(LCT_INT) * l);
            param->data.intParam.length = l;

            for (j = 1; j <= l; j++) {
                lua_rawgeti(lct->L, -1, j);
                //printf("Int List %d\n", (LCT_INT) lua_tonumberx(L, -1, &isnum));
                param->data.intParam.list[j - 1] = (LCT_INT) lua_tonumberx(lct->L, stackPos, &isnum);
                lua_pop(lct->L, 1);
            }

            break;

        case LC_TYPE_DOUBLE_LIST:

            // check if value is a table
            if (!lua_istable(lct->L, -1)) {
                param->err = LC_ERR_INVALID;
                break;
            }

            // get length of list
            l = lua_rawlen(lct->L, -1);
            param->data.dblParam.list = malloc( sizeof(LCT_DBL) * l);
            param->data.dblParam.length = l;

            for (j = 1; j <= l; j++) {
                lua_rawgeti(lct->L, -1, j);
                //printf("Dbl List %f\n", (LCT_DBL) lua_tonumberx(L, -1, &isnum));
                param->data.dblParam.list[j - 1] = (LCT_DBL) lua_tonumberx(lct->L, stackPos, &isnum);
                lua_pop(lct->L, 1);
            }

            break;

        case LC_TYPE_CUSTOM_LIST:
        case LC_TYPE_CUSTOM:
            if (!lua_istable(lct->L, -1)) {
                param->err = LC_ERR_INVALID;
                break;
            }

            p = param->data.customParam.params;
            j = 0;

            while (p[j].type != LC_TYPE_LAST ) {
                //printf("Custom name %s, %d\n", p[j])
                lua_pushstring(lct->L, p[j].name); // push the table key name
                lua_gettable(lct->L, -2);          // get key value
                LC_GetValue(lct, &p[j], -1);
                lua_pop(lct->L, 1);
                LC_PrintParam(&p[j]);
                j++;
            }

            break;

        default:
            break;
    }

}


void stackDump(lua_State *l) {
    int i;
    int top = lua_gettop(l);

    printf("total in stack %d\n", top);

    for (i = 1; i <= top; i++) {
        /* repeat for each level */
        int t = lua_type(l, i);

        switch (t) {
            case LUA_TSTRING:  /* strings */
                printf("string: '%s'\n", lua_tostring(l, i));
                break;

            case LUA_TBOOLEAN:  /* booleans */
                printf("boolean %s\n", lua_toboolean(l, i) ? "true" : "false");
                break;

            case LUA_TNUMBER:  /* numbers */
                printf("number: %g\n", lua_tonumber(l, i));
                break;

            default:  /* other values */
                printf("%s\n", lua_typename(l, t));
                break;
        }

        printf("  ");  /* put a separator */
    }

    printf("\n");  /* end the listing */
}

void LC_read(LCT *lct, char *confFile) {
    int i, j, l;
    int isnum;
    const char *s;
    luaConf *p;

    luaConf *params = lct->params;

    LCT_Constants(lct->L, params);

    luaL_dofile(lct->L, confFile);

    isnum = 1;
    i = 0;

    //stackDump(L);

    while (params[i].type != LC_TYPE_LAST) {
        //DEBUGPRINT("i=%d name=%s\n", i, conf[i].name);

        if (!PARAM_IS_COMMENT(params[i])) {

            // push identifier onto stack
            lua_getglobal(lct->L, params[i].name);

            // check if identifier exists
            if (lua_isnil(lct->L, -1)) {
                params[i].err = LC_ERR_MISSING;
            } else {

                switch (params[i].type) {
                    case LC_TYPE_BOOLEAN:
                        params[i].data.boolParam.val = (LCT_BOOL) lua_tonumberx(lct->L, -1, &isnum);

                        if (!isnum) {
                            params[i].err = LC_ERR_INVALID;
                        }

                        break;

                    case LC_TYPE_INTEGER:
                    case LC_TYPE_INTEGER_PL:
                    case LC_TYPE_INTEGER_NL:
                        LC_GetValue(lct, &params[i], -1);
                        break;

                    case LC_TYPE_DOUBLE:
                    case LC_TYPE_DOUBLE_PL:
                    case LC_TYPE_DOUBLE_NL:
                        LC_GetValue(lct, &params[i], -1);

                        break;
                        params[i].data.dblParam.val = (LCT_DBL) lua_tonumberx(lct->L, -1, &isnum);

                        if (!isnum) {
                            params[i].err = LC_ERR_INVALID;
                        }

                        break;

                    case LC_TYPE_STRING:
                        if (!lua_isstring(lct->L, -1)) {
                            params[i].err = LC_ERR_INVALID;
                            break;
                        }

                        lua_tonumberx(lct->L, -1, &isnum);

                        if (isnum) {
                            params[i].err = LC_ERR_INVALID;
                            break;
                        }

                        s = lua_tostring(lct->L, -1);

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
                        if (!lua_istable(lct->L, -1)) {
                            params[i].err = LC_ERR_INVALID;
                            break;
                        }

                        // get length of list
                        l = lua_rawlen(lct->L, -1);

                        params[i].data.intParam.list = malloc( sizeof(LCT_INT) * l);
                        params[i].data.intParam.length = l;

                        for (j = 1; j <= l; j++) {
                            lua_rawgeti(lct->L, -1, j);
                            //printf("Int List %d\n", (LCT_INT) lua_tonumberx(L, -1, &isnum));
                            params[i].data.intParam.list[j - 1] = (LCT_INT) lua_tonumberx(lct->L, -1, &isnum);
                            lua_pop(lct->L, 1);
                        }

                        break;

                    case LC_TYPE_DOUBLE_LIST:

                        // check if value is a table
                        if (!lua_istable(lct->L, -1)) {
                            params[i].err = LC_ERR_INVALID;
                            break;
                        }

                        // get length of list
                        l = lua_rawlen(lct->L, -1);
                        params[i].data.dblParam.list = malloc( sizeof(LCT_DBL) * l);
                        params[i].data.dblParam.length = l;

                        for (j = 1; j <= l; j++) {
                            lua_rawgeti(lct->L, -1, j);
                            //printf("Dbl List %f\n", (LCT_DBL) lua_tonumberx(L, -1, &isnum));
                            params[i].data.dblParam.list[j - 1] = (LCT_DBL) lua_tonumberx(lct->L, -1, &isnum);
                            lua_pop(lct->L, 1);
                        }

                        break;

                    case LC_TYPE_CUSTOM:
                        LC_GetValue(lct, &params[i], -1);
                        break;

                    case LC_TYPE_CUSTOM_LIST:
                        if (!lua_istable(lct->L, -1)) {
                            params[i].err = LC_ERR_INVALID;
                            break;
                        }

                        // get length of list
                        l = lua_rawlen(lct->L, -1);
                        p = &params[i];
                        luaConf *pp;
                        p->data.customParam.list = malloc( sizeof(luaConf) * l);

                        //params[i].data.customParam.list = malloc( sizeof(luaConf) * l);

                        for (j = 1; j <= l; j++) {
                            //params[i].data.customParam.list[j-1] = (luaConf) params[i];
                            pp = (luaConf *) p->data.customParam.list;
                            pp[j - 1] = *p;
                            //(luaConf) p->data.customParam.list[j-1] =   p;

                            lua_rawgeti(lct->L, -1, j);
                            //LC_GetValue(&params[i].data.customParam.list[j-1], -1);
                            LC_GetValue(lct, &pp[j - 1], -1);
                            //LC_GetValue(&params[i], -1);
                            lua_pop(lct->L, 1);
                        }

                        break;


                    default:
                        LC_GetValue(lct, &params[i], -1);
                        break;
                }

                LC_validate(&params[i]);

            }

            lua_pop(lct->L, 1);
        }

        printf("%-20s %-18s %-10s  %10s [ %s ]\n", params[i].name, LC_TYPE2STR(params[i].type), LC_ERROR2STR(params[i].err), val2string(&params[i]), LCT_paramLimits(&params[i]));
        i++;
    }


//    lua_getglobal(lct->L, "MyFunction");
//    lua_call(lct->L, 0, 0);
//
//    lua_getglobal(lct->L, "FunIntArg");
//    lua_pushnumber(lct->L, 23);
//    lua_call(lct->L, 1, 0);


    //lua_close(lct->L);
}


LCT *LCT_New(luaConf *params) {
    LCT *lct;

    lct = malloc( sizeof(LCT) );
    lct->params = params;
    lct->L = luaL_newstate();
    luaL_openlibs(lct->L);

    return lct;
}

void LCT_Free(LCT *lct) {
    lua_close(lct->L);
    free(lct);
}

void LCT_ReadFile(LCT *lct, char *fileName) {
    LC_read(lct, fileName);
}


void LCT_PushInt(LCT *lct, LCT_INT v) {
    lua_pushnumber(lct->L, v);
}

void LCT_PushDbl(LCT *lct, LCT_DBL v) {
    lua_pushnumber(lct->L, v);
}

void LCT_PushStr(LCT *lct, LCT_STR v) {
    lua_pushstring(lct->L, v);
}


void LCT_PushParameter(LCT *lct, luaConf *param) {
    switch (param->type) {
        case LC_TYPE_ARG_INTEGER:
            lua_pushnumber(lct->L, param->data.intArg.val);
            break;

        case LC_TYPE_ARG_DOUBLE:
            lua_pushnumber(lct->L, param->data.dblArg.val);
            break;

        case LC_TYPE_ARG_STRING:
            lua_pushstring(lct->L, param->data.strArg.val);
            break;

        case LC_TYPE_ARG_INTEGER_LIST:
            break;

        case LC_TYPE_ARG_DOUBLE_LIST:
            break;

        case LC_TYPE_ARG_STRING_LIST:
            break;

        default:
            break;
    }
}



void LCT_CallFunction(LCT *lct, luaConf *param) {
    int i;
    luaConf *params;

    if (param == NULL) {
        return;
    }

    lua_getglobal(lct->L, param->name);

    i = 0;
    params = param->data.function.params;

    if (params != NULL) {

        while (params[i].type != LC_TYPE_LAST) {
            LCT_PushParameter(lct, &params[i]);
            i++;
        }
    }

    lua_call(lct->L, i, 0);
}


luaConf *LCT_FindFunction(LCT *lct, char *name) {
    int i;
    i = 0;

    while ( lct->params[i].type != LC_TYPE_LAST ) {
        if (!strcmp(lct->params[i].name, name)) {
            return &lct->params[i];
        }

        i++;
    }

    return NULL;
}

void LCT_FCallSimple(LCT *lct, char *funcName, ...) {
    int i;
    luaConf *func;
    va_list ap;

    func = LCT_FindFunction(lct, funcName);

    if (func == NULL) {
        return;
    }

    i = 0;
//
//    while ( func->data.function.params[i].type != LC_TYPE_LAST ) {
////      switch ( )
////      LCT_PushParameter(lct, &func->data.function.params[i], )
//        i++;
//    }

//    va_start(ap, num_args);
//
//    for (i = 0; i < num_args; i++) {
//        val += va_arg(ap, int);
//    }
//
//    va_end(ap);

    lua_getglobal(lct->L, func->name);
    lua_call(lct->L, i, 0);
}



// Test code ---------------------------------------------------------

LCT_INT validIntList[] = LCT_INT_VLIST( 5, 9, 12, 42, 193, 104, -4120);

LCT_DBL validDblList[] = LCT_DBL_VLIST( 5.5, -9.23, 14.94, 42.42, -1401.43, 0);

luaConf tableParams[] = {
    LC_INT("a", "", 0, 1, 0, 0),
    LC_DBL("b", "", 0, 0 , 0 , 0),
    LC_STR("c", "", 0, ""),
    LC_INT_LIST("d", "", 0, 0, 0, 0),
    LC_LAST(),
};

luaConf funIntArg[] = {
    LC_ARG_INT(),
    LC_LAST(),
};

luaConf confTest[] = {
    LCT_COMMENT("This is a comment"),
    LC_INT("IntParam1",        "Correct Integer parameter",       0, -42, 0, 0),
    LC_INT("IntParam2",        "Correct Integer parameter",       0, 0, 0, 0),
    LC_INT("IntParam3",        "Correct Integer parameter",       0, 0, 0, 0),
    LC_INT_PL("IntParam4",     "Int parameter pick list valid value", 0, 0, validIntList),
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
    LC_INT_LIST("IntList",     "Integer List parameter",          0, 0, 0, 0),
    LC_DBL_LIST("DblList",     "Double List parameter",           0, 0, 0, 0),
    LC_INT_LIST("InvalidList", "Invalid Integer List",            0, 0, 0, 0),
    LC_CUSTOM("TableParam", tableParams),
    LC_CUSTOM_LIST("TableParamList", tableParams),
    LCT_INTEGER_CONST("IntConst", 32),
    LCT_DOUBLE_CONST("DblConst",  32.23),
    LCT_STRING_CONST("StrConst",  "A little string constant"),
    LCT_FUNCTION("MyFunction", NULL),
    LCT_FUNCTION("FunIntArg", funIntArg),
    LC_LAST(),
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
    //lua_State *L;
    LCT *lct;
    luaConf *myFunc;
    luaConf *FunIntArg;

    lct = LCT_New(confTest);

    LCT_ReadFile(lct, "conftest.lua");

    LCT_FCallSimple(lct, "MyFunction");

    myFunc = LCT_FindFunction(lct, "MyFunction");
    LCT_CallFunction(lct, myFunc);

    FunIntArg = LCT_FindFunction(lct, "FunIntArg");
    LCT_CallFunction(lct, FunIntArg);


    printf("Counter %d\n", __COUNTER__);
    printf("Counter %d\n", __COUNTER__);
    printf("Counter %d\n", __COUNTER__);
    //L = luaL_newstate();
    //luaL_openlibs(L);
    //LC_File(confTest);

    //LC_read(L, confTest, "conftest.lua");

    //LCT_PrintProblems(confTest);

    exit(0);

}


