/**
 *---------------------------------------------------------------------------
 * @brief   A simple lua configuration file library.
 *
 * @file    luaConf.c
 * @author  Peter Malmberg <peter.malmberg@gmail.com>
 * @date    2016-12-21
 * @license LGPLv2
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
 * - Add function api feature
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
    {LC_TYPE_STRING_LIST,   "String List"},
    {LC_TYPE_INTEGER_CONST, "Integer constant"},
    {LC_TYPE_DOUBLE_CONST,  "Double constant"},
    {LC_TYPE_STRING_CONST,  "String constant"},
    {LC_TYPE_INTEGER_PL,    "Integer pick list"},
    {LC_TYPE_INTEGER_NL,    "Integer name list"},
    {LC_TYPE_DOUBLE_PL,     "Double pick list"},
    {LC_TYPE_DOUBLE_NL,     "Double name list"},
    {LC_TYPE_COMMENT,       "Comment"},
    {LC_TYPE_TABLE,         "Table"},
    {LC_TYPE_TABLE_LIST,    "Table list"},
    {LC_TYPE_FUNCTION,      "Function"},
    {LC_TYPE_API,           "API"},
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


int LCT_Params(luaConf *params) {
    int i;

    if (params == NULL) {
        return 0;
    }

    i = 0;

    while ( params[i].type != LC_TYPE_LAST ) {
        i++;
    }

    return i;
}

luaConf *LCT_Find(luaConf *params, char *name) {
    int i;
    i = 0;

    while ( params[i].type != LC_TYPE_LAST ) {
        if (!strcmp(params[i].name, name)) {
            return &params[i];
        }

        i++;
    }

    return NULL;
}


luaConf *LCT_FindFunction(LCT *lct, char *name) {
    return LCT_Find(lct->params, name);
}


int LCT_IntListLen(int *list) {
    int i;
    i = 0;

    if (list == NULL) {
        return 0;
    }

    while (list[i] != LCT_INT_MAX) {
        i++;
    }

    return i;
}

int LCT_DblListLen(double *list) {
    int i;
    i = 0;

    if (list == NULL) {
        return 0;
    }

    while (list[i] != LCT_DBL_MAX) {
        i++;
    }

    return i;
}

int LCT_ListLen(luaConf *param) {
    switch (param->type) {
        case LC_TYPE_INTEGER_LIST:
            return param->data.intParam.length;
            break;

        case LC_TYPE_DOUBLE_LIST:
            return param->data.dblParam.length;
            break;

        case LC_TYPE_STRING_LIST:
            return param->data.strParam.length;
            break;

        default:
            return 0;

    }
}

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

//        case LC_TYPE_INTEGER_LIST:
//            bp = buf;
//
//            for (i = 0; i < param->data.intParam.length; i++) {
//                //printf("%d ", param->data.intParam.list[i]);
//                sprintf(bp, "%d ", param->data.intParam.list[i]);
//                bp += strlen(bp);
//            }
//
//            break;
//
//        case LC_TYPE_DOUBLE_LIST:
//            bp = buf;
//
//            for (i = 0; i < param->data.dblParam.length; i++) {
//                sprintf(bp, "%.2lf ", param->data.dblParam.list[i]);
//                bp += strlen(bp);
//            }
//
//            break;


        default:
            return "";
    }

    return buf;
}

char *LCT_Default2String(luaConf *param) {

}

char *LCT_paramLimits(luaConf *param) {
    static char buf[1024];
    int i;
    char *p;

    switch (param->type) {
        case LC_TYPE_INTEGER:
            if (param->data.intParam.min == param->data.intParam.max) {
                sprintf(buf, "[ no limit ]");
            } else {
                sprintf(buf, "[ %d %d ]", param->data.intParam.min, param->data.intParam.max);
            }

            break;

        case LC_TYPE_DOUBLE:
            if (param->data.dblParam.min == param->data.dblParam.max) {
                sprintf(buf, "[ no limit ]");
            } else {
                sprintf(buf, "[ %0.2f %0.2f ]", param->data.dblParam.min, param->data.dblParam.max);
            }

            break;

        case LC_TYPE_INTEGER_PL:
            i = 0;
            p = buf;

            p += sprintf(p, "[ ");

            while (param->data.intParam.validList[i] != LCT_INT_MAX) {
                sprintf(p, "%d ", param->data.intParam.validList[i]);
                p += strlen(p);
                i++;
            }

            sprintf(p, " ]");

            break;

        case LC_TYPE_DOUBLE_PL:
            i = 0;
            p = buf;

            p += sprintf(p, "[ ");

            while (param->data.dblParam.validList[i] != LCT_DBL_MAX) {
                sprintf(p, "%.2f ", param->data.dblParam.validList[i]);
                p += strlen(p);
                i++;
            }

            sprintf(p, " ]");
            break;

        default:
            return "";
            break;
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


//void printParam(luaConf *param) {
//    printf("Name: %s\n", param->name);
//    printf("Desc: %s\n", param->desc);
//    printf("Type: %s\n", LC_TYPE2STR(param->type));
//    printf("Val:  %s\n", val2string(param));
//}
void LC_PrintParams(luaConf *conf);

void LC_PrintParam(luaConf *param) {
    int i;
    printf("%-20s %-18s %-10s  %10s  %s \n", param->name, LC_TYPE2STR(param->type), LC_ERROR2STR(param->err), val2string(param), LCT_paramLimits(param));

    switch (param->type) {
        case LC_TYPE_INTEGER_LIST:
            for (i = 0; i < LCT_ListLen(param); i++) {
                printf("                                                    %5d\n", param->data.intParam.list[i]);
            }

            break;

        case LC_TYPE_DOUBLE_LIST:
            for (i = 0; i < LCT_ListLen(param); i++) {
                printf("                                                    %5.2f\n", param->data.dblParam.list[i]);
            }

            break;

        case LC_TYPE_STRING_LIST:
            for (i = 0; i < LCT_ListLen(param); i++) {
                printf("                          %s\n", param->data.strParam.list[i]);
            }

            break;

        case LC_TYPE_TABLE:
            LC_PrintParams(param->data.tableParam.params);
            break;

        default:
            break;
    }
}


void LC_PrintParams(luaConf *conf) {
    int i;
    i = 0;

    while (conf[i].type != LC_TYPE_LAST) {
        LC_PrintParam(&conf[i]);
        i++;
    }
}


void LC_SetDefault(luaConf *param) {
    switch (param->type) {
        case LC_TYPE_INTEGER:
        case LC_TYPE_INTEGER_PL:
        case LC_TYPE_INTEGER_NL:
        	*(LCT_INT *) param->valPtr = param->data.intParam.default_val;
            break;

        case LC_TYPE_DOUBLE:
        case LC_TYPE_DOUBLE_PL:
        case LC_TYPE_DOUBLE_NL:
        	*(LCT_DBL *)param->valPtr = param->data.dblParam.default_val;
            break;

//        case LC_TYPE_STRING:
//            param->data.strParam.val = malloc( strlen(param->data.strParam.default_val + 1) );
//            strcpy(param->data.strParam.val, param->data.strParam.default_val);
//            break;

        case LC_TYPE_BOOLEAN:
            *(LCT_BOOL *)param->valPtr = param->data.boolParam.default_val;
            break;

        case LC_TYPE_INTEGER_LIST:
        case LC_TYPE_DOUBLE_LIST:
        case LC_TYPE_STRING_LIST:
        case LC_TYPE_BOOLEAN_LIST:

        default:
            break;
    }
}

void LCT_SetDefaults(luaConf *params) {
    int i;
    i = 0;

    while (params[i].type != LC_TYPE_LAST) {
        LC_SetDefault(&params[i]);
        i++;
    }
}

int list[] = {
    LC_TYPE_INTEGER,
    LC_TYPE_DOUBLE,
    LC_TYPE_STRING,
    LC_TYPE_BOOLEAN,

    LC_TYPE_INTEGER_PL,
    LC_TYPE_DOUBLE_PL,

    LC_TYPE_INTEGER_NL,
    LC_TYPE_DOUBLE_NL,

    LC_TYPE_INTEGER_LIST,
    LC_TYPE_DOUBLE_LIST,
    LC_TYPE_STRING_LIST,
    LC_TYPE_BOOLEAN_LIST,
    LC_TYPE_BYTE_LIST,

    LC_TYPE_TABLE,
    LC_TYPE_TABLE_LIST,
    LC_TYPE_COMMENT,
    LC_TYPE_LAST
};

int LCT_IsParam(int p) {
    int i;
    i = 0;

    while (list[i] != LC_TYPE_LAST) {
        if (list[i] == p) {
            return 1;
        }

        i++;
    }

    return 0;
}

void LC_PrintParamFile(luaConf *param, FILE *f) {

    if (!IS_PARAM(param)) {
        return;
    }

    switch (param->type) {
        case LC_TYPE_COMMENT:
            fprintf(f, "%s\n", param->name);
            break;

        default:
        	fprintf(f, "--\n");
            fprintf(f, "-- %s\n", param->desc);
            fprintf(f, "-- %s\n", LCT_paramLimits(param));
        	fprintf(f, "--\n");
            fprintf(f, "%s = %s\n\n", param->name, val2string(param));
            break;
    }

}

void LCT_File(luaConf *conf) {
    int i;

    i = 0;

    while (conf[i].type != LC_TYPE_LAST) {
        LC_PrintParamFile(&conf[i], stdout);
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

void LCT_PullParameter(LCT *lct, luaConf *param) {
    int isnum;
    int stackPos = -1;
    int j, l;
    char *s, *s2;
    luaConf *p;

    if (!PARAM_IS_COMMENT(param)) {

        // check if identifier exists
        if (lua_isnil(lct->L, -1)) {
            param->err = LC_ERR_MISSING;
        } else {

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
                    *(LCT_INT *) param->valPtr = (LCT_INT) lua_tonumberx(lct->L, stackPos, &isnum);


                    if (!isnum) {
                        param->err = LC_ERR_INVALID;
                    }


                    break;

                case LC_TYPE_DOUBLE:
                case LC_TYPE_DOUBLE_PL:
                case LC_TYPE_DOUBLE_NL:
                    *(LCT_DBL *) param->valPtr = (LCT_DBL) lua_tonumberx(lct->L, stackPos, &isnum);

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

                    s = (char *) lua_tostring(lct->L, stackPos);

                    if (s == NULL) {
                        param->err = LC_ERR_INVALID;
                        break;
                    }

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
                        param->data.dblParam.list[j - 1] = (LCT_DBL) lua_tonumberx(lct->L, stackPos, &isnum);
                        lua_pop(lct->L, 1);
                    }

                    break;

                case LC_TYPE_STRING_LIST:

                    // check if value is a table
                    if (!lua_istable(lct->L, -1)) {
                        param->err = LC_ERR_INVALID;
                        break;
                    }

                    // get length of list
                    l = lua_rawlen(lct->L, -1);
                    param->data.strParam.list = malloc( sizeof(LCT_STR) * l);
                    param->data.strParam.length = l;

                    for (j = 1; j <= l; j++) {
                        lua_rawgeti(lct->L, -1, j);


                        lua_tonumberx(lct->L, -1, &isnum);

                        if (isnum) {
                            param->err = LC_ERR_INVALID;
                            break;
                        }

                        s = (char *) lua_tostring(lct->L, -1);

                        if (s == NULL) {
                            param->err = LC_ERR_INVALID;
                            break;
                        }


                        s2 = malloc( strlen(s) + 1);
                        strcpy(s2, s);
                        param->data.strParam.list[j - 1] = s2;

                        lua_pop(lct->L, 1);
                    }

                    break;


                //                case LC_TYPE_TABLE_LIST:
                //                    if (!lua_istable(lct->L, -1)) {
                //                        params[i].err = LC_ERR_INVALID;
                //                        break;
                //                    }
                //
                //                    // get length of list
                //                    l = lua_rawlen(lct->L, -1);
                //                    p = &params[i];
                //                    luaConf *pp;
                //                    p->data.tableParam.list = malloc( sizeof(luaConf) * l);
                //
                //                    for (j = 1; j <= l; j++) {
                //                        pp = (luaConf *) p->data.tableParam.list;
                //                        pp[j - 1] = *p;
                //
                //                        lua_rawgeti(lct->L, -1, j);
                //                        //LC_GetValue(lct, &pp[j - 1], -1);
                //                        LCT_PullParameter(lct, &params[i]);
                //                        lua_pop(lct->L, 1);
                //                    }
                //
                //                    break;

                case LC_TYPE_TABLE_LIST:
                    if (!lua_istable(lct->L, -1)) {
                        param->err = LC_ERR_INVALID;
                        break;
                    }

                    // get length of list
                    l = lua_rawlen(lct->L, -1);
                    p = param;
                    luaConf *pp;

                    p->data.tableParam.list = malloc( sizeof(luaConf) * l);

                    for (j = 1; j <= l; j++) {
                        pp = (luaConf *) p->data.tableParam.list;
                        pp[j - 1] = *p;

                        //param->data.tableParam.li
                        lua_rawgeti(lct->L, -1, j);

                        param->type = LC_TYPE_TABLE;
                        LCT_PullParameter(lct, param);
                        LC_PrintParam(param);
                        lua_pop(lct->L, 1);
                    }

                    break;

                case LC_TYPE_TABLE:
                    if (!lua_istable(lct->L, -1)) {
                        param->err = LC_ERR_INVALID;
                        break;
                    }

                    //printf("Table %s\n", param->name);
                    p = param->data.tableParam.params;
                    j = 0;

                    while (p[j].type != LC_TYPE_LAST ) {
                        //printf("T element %s\n", p[j].name);
                        lua_pushstring(lct->L, p[j].name); // push the table key name
                        lua_gettable(lct->L, -2);          // get key value
                        //stackDump(lct->L);
                        LCT_PullParameter(lct, &p[j]);
                        lua_pop(lct->L, 1);
                        j++;
                    }

                    break;

                default:
                    break;
            }
        }
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
    int i;
    luaConf *param;

    luaConf *params = lct->params;

    LCT_Constants(lct->L, params);

    luaL_dofile(lct->L, confFile);

    i = 0;

    while (params[i].type != LC_TYPE_LAST) {
        param = &params[i];

        if (!PARAM_IS_COMMENT(param)) {

            // push identifier onto stack
            lua_getglobal(lct->L, params[i].name);

            // pull parameter from stack
            LCT_PullParameter(lct, &params[i]);

            // Validate the parameter
            LC_validate(&params[i]);
        }

        lua_pop(lct->L, 1);
        i++;
    }
}


void LCT_SetValuePtr(luaConf *params, char *name, void *valPtr) {
    luaConf *param;
    param = LCT_Find(params, name);

    if (param) {
        param->valPtr = valPtr;
    }
}

void LCT_InitAPI(LCT *lct) {
    int i;
    i = 0;

    while (lct->params[i].type != LC_TYPE_LAST) {
        if (lct->params[i].type == LC_TYPE_API) {
            lua_pushcfunction(lct->L, lct->params[i].data.api.function);
            lua_setglobal(lct->L, lct->params[i].name);
        }

        i++;
    }
}


void LCT_InitParam(luaConf *param) {
    if (param == NULL) {
        return;
    }

    switch (param->type) {

        case LC_TYPE_INTEGER:
        case LC_TYPE_INTEGER_PL:
        case LC_TYPE_INTEGER_NL:
        case LC_TYPE_INTEGER_CONST:
            param->valPtr = &param->data.intParam.val;
            break;

        case LC_TYPE_DOUBLE:
        case LC_TYPE_DOUBLE_PL:
        case LC_TYPE_DOUBLE_NL:
        case LC_TYPE_DOUBLE_CONST:
            param->valPtr = &param->data.dblParam.val;
            break;

        case LC_TYPE_STRING:
        case LC_TYPE_STRING_CONST:
            param->valPtr = param->data.strParam.val;
            break;

        case LC_TYPE_BOOLEAN:
            param->valPtr = &param->data.boolParam.val;
            break;

        case LC_TYPE_INTEGER_LIST:
        case LC_TYPE_DOUBLE_LIST:
        case LC_TYPE_STRING_LIST:
        case LC_TYPE_BOOLEAN_LIST:
        case LC_TYPE_BYTE_LIST:
            break;

        case LC_TYPE_TABLE:
            LCT_Init(param->data.tableParam.params);
            break;

        case LC_TYPE_TABLE_LIST:
            break;

        case LC_TYPE_COMMENT:
            break;

        case LC_TYPE_FUNCTION:
            LCT_Init(param->data.function.params);
            LCT_Init(param->data.function.returns);
            param->data.function.p = LCT_Params(param->data.function.params);
            param->data.function.r = LCT_Params(param->data.function.returns);
            break;

        case LC_TYPE_GLOBAL_INTEGER:
        case LC_TYPE_GLOBAL_DOUBLE:
        case LC_TYPE_GLOBAL_STRING:
        case LC_TYPE_GLOBAL_BOOLEAN:
            break;

        default:
            break;
    }
}

void LCT_Init(luaConf *params) {
    int i;
    i = 0;

    if (params == NULL) {
        return;
    }

    while (params[i].type != LC_TYPE_LAST) {
        LCT_InitParam(&params[i]);
        i++;
    }
}



LCT *LCT_New(luaConf *params) {
    LCT *lct;

    lct = malloc( sizeof(LCT) );
    lct->params = params;

    LCT_Init(lct->params);

    lct->L = luaL_newstate();
    luaL_openlibs(lct->L);

    LCT_InitAPI(lct);

    return lct;
}

void LCT_Free(LCT *lct) {
    lua_close(lct->L);

    // @todo remove lists, strings etc.
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

void LCT_PushIntArray(LCT *lct, LCT_INT v[], int len) {
    int i;
    lua_newtable(lct->L);

    for (i = 0; i < len; i++) {
        lua_pushinteger(lct->L, v[i]);
        lua_rawseti(lct->L, -2, i + 1);
    }
}

void LCT_PushDblArray(LCT *lct, LCT_DBL v[], int len) {
    int i;
    lua_newtable(lct->L);

    for (i = 0; i < len; i++) {
        lua_pushnumber(lct->L, v[i]);
        lua_rawseti(lct->L, -2, i + 1);
    }
}

void LCT_PushStrArray(LCT *lct, LCT_STR v[], int len) {
    int i;
    lua_newtable(lct->L);

    for (i = 0; i < len; i++) {
        lua_pushstring(lct->L, v[i]);
        lua_rawseti(lct->L, -2, i + 1);
    }
}



void LCT_PushParameter(LCT *lct, luaConf *param, void *value) {
    int i = 0;
    luaConf *params;

    switch (param->type) {
        case LC_TYPE_INTEGER:
            lua_pushinteger(lct->L, *(LCT_INT *) param->valPtr);
            break;

        case LC_TYPE_DOUBLE:
            lua_pushnumber(lct->L, *(LCT_DBL *) param->valPtr);
            break;

        case LC_TYPE_STRING:
            lua_pushstring(lct->L, param->valPtr);
            break;

        case LC_TYPE_BOOLEAN:
            lua_pushinteger(lct->L, *(LCT_BOOL *) param->valPtr);
            break;

        case LC_TYPE_INTEGER_LIST:
            LCT_PushIntArray(lct, param->data.intParam.list, LCT_IntListLen(param->data.intParam.list));
            break;

        case LC_TYPE_DOUBLE_LIST:
            LCT_PushDblArray(lct, param->data.dblParam.list, LCT_DblListLen(param->data.dblParam.list));
            break;

//
//        case LC_TYPE_ARG_STRING_LIST:
//            break;

        case LC_TYPE_TABLE:
            params = param->data.tableParam.params;

            if (params == NULL) {
                return;
            }

            lua_newtable(lct->L);

            while (params[i].type != LC_TYPE_LAST) {
                lua_pushstring(lct->L, params[i].name);
                LCT_PushParameter(lct, &params[i], NULL);

                lua_settable(lct->L, -3);
                i++;
            }

            break;

        default:
            lua_pushstring(lct->L, "Blaha");
            break;
    }

    if (param->flags & (LC_FLAG_PUSH | LC_FLAG_PULL)) {
        lua_setglobal(lct->L, param->name);
    }
}


void LCT_PushTable(LCT *lct, luaConf *table) {
    int i;
    i = 0;

    if (table == NULL) {
        return;
    }

    lua_newtable(lct->L);

    while (table[i].type != LC_TYPE_LAST) {
        lua_pushstring(lct->L, table[i].name);
        LCT_PushParameter(lct, &table[i], NULL);

        lua_settable(lct->L, -3);
        i++;
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
            LCT_PushParameter(lct, &params[i], NULL);
            i++;
        }
    }

    lua_call(lct->L, i, 0);
}






void LCT_PushGlobalVars(LCT *lct) {
    int i;
    i = 0;

    while (lct->params[i].type != LC_TYPE_LAST) {
        if (lct->params[i].flags & LC_FLAG_PUSH) {
            LCT_PushParameter(lct, &lct->params[i], NULL);
        }

        i++;
    }
}

void LCT_PullGlobalVars(LCT *lct) {
    int i;
    i = 0;

    while (lct->params[i].type != LC_TYPE_LAST) {
        if (lct->params[i].flags & LC_FLAG_PULL) {

            // push identifier onto stack
            lua_getglobal(lct->L, lct->params[i].name);

            // pull parameter from stack
            LCT_PullParameter(lct, &lct->params[i]);

        }

        i++;
    }
}


luaConf *LCT_PullReturns(LCT *lct, luaConf *func) {
    int i;
    i = 0;

    if (func->data.function.returns == NULL) {
        return NULL;
    }

    //stackDump(lct->L);

    for (i = func->data.function.r - 1; i >= 0; i--) {

        LCT_PullParameter(lct, &func->data.function.returns[i]);

        lua_pop(lct->L, 1);

    }

    return func->data.function.returns;
}


luaConf *LCT_FCallSimple(LCT *lct, char *funcName, ...) {
    int i, p;
    int *iPtr;
    int l;
    double *dPtr;
    char *sPtr;
    luaConf *func;
    va_list ap;
    luaConf *params;
    luaConf *table;
    luaConf *rets;

    func = LCT_FindFunction(lct, funcName);

    if ((func == NULL) || PARAM_IS_MISSING(func)) {
        return NULL;
    }

    LCT_PushGlobalVars(lct);

    lua_getglobal(lct->L, func->name);

    i = 0;

    p = func->data.function.p;
    va_start(ap, p);

    for (i = 0; i < p; i++) {
        params = func->data.function.params;

        //if (params[i].flags & LC_FLAG_ARG) {
        switch (params[i].type) {
            case LC_TYPE_INTEGER:
                LCT_PushInt(lct, va_arg(ap, LCT_INT));
                break;

            case LC_TYPE_DOUBLE:
                LCT_PushDbl(lct, va_arg(ap, LCT_DBL));
                break;

            case LC_TYPE_STRING:
                LCT_PushStr(lct, va_arg(ap, char *));
                break;

            case LC_TYPE_INTEGER_LIST:
                iPtr = va_arg(ap, int *);
                l    = va_arg(ap, int);
                LCT_PushIntArray(lct, iPtr , l);
                break;

            case LC_TYPE_DOUBLE_LIST:
                dPtr = va_arg(ap, double *);
                l    = va_arg(ap, int);
                LCT_PushDblArray(lct, dPtr , l);
                break;

            case LC_TYPE_STRING_LIST:
                sPtr = va_arg(ap, char *);
                l    = va_arg(ap, int);
                LCT_PushStrArray(lct, sPtr , l);
                break;

            case LC_TYPE_TABLE:
                table = va_arg(ap, luaConf *);
                //LCT_PushTable(lct, table->data.customParam.params);
                LCT_PushTable(lct, table);
                break;

            default:
                break;
        }

    }

    va_end(ap);

    lua_call(lct->L, func->data.function.p, func->data.function.r);

    rets = LCT_PullReturns(lct, func);

    LCT_PullGlobalVars(lct);

    return rets;
}


void LCT_FCallSimple2(LCT *lct, char *funcName, char *format, ...) {
    int i, p;
    int *iPtr;
    int l;
    double *dPtr;
    char *sPtr;
    va_list ap;

    lua_getglobal(lct->L, funcName);

    i = 0;

    va_start(ap, p);

    while (format[i] != '\0') {

        switch (format[i]) {
            case 'i':
                LCT_PushInt(lct, va_arg(ap, LCT_INT));
                break;

            case 'd':
                LCT_PushDbl(lct, va_arg(ap, LCT_DBL));
                break;

            case 's':
                LCT_PushStr(lct, va_arg(ap, char *));
                break;

            case 'I':
                iPtr = va_arg(ap, int *);
                l    = va_arg(ap, int);
                LCT_PushIntArray(lct, iPtr , l);
                break;

            case 'D':
                dPtr = va_arg(ap, double *);
                l    = va_arg(ap, int);
                LCT_PushDblArray(lct, dPtr , l);
                break;

            case 'S':
                sPtr = va_arg(ap, char *);
                l    = va_arg(ap, int);
                LCT_PushStrArray(lct, sPtr , l);
                break;

//            case LC_TYPE_TABLE:
//                table = va_arg(ap, luaConf *);
//                //LCT_PushTable(lct, table->data.customParam.params);
//                LCT_PushTable(lct, table);
//                break;

            default:
                break;
        }

        i++;

    }

    va_end(ap);

    lua_call(lct->L, i, 0);
}


// Test code ---------------------------------------------------------

LCT_INT  globalInt;
LCT_DBL  globalDbl;
char     globalStr[64] = "Min globala sträng";
LCT_BOOL globalBool;

LCT_INT validIntList[] = LCT_INT_VLIST( 5, 9, 12, 42, 193, 104, -4120);

LCT_DBL validDblList[] = LCT_DBL_VLIST( 5.5, -9.23, 14.94, 42.42, -1401.43, 0);

char *myStrings[] = { "Kalle", "Arne", "Nisse", "Lisa", "Bertil", "Lena" };

luaConf tableParams[] = {
    LC_INT("a", "", 0, 1, 0, 0),
    LC_DBL("b", "", 0, 0 , 0 , 0),
    LC_STR("c", "", 0, ""),
//   LC_INT_LIST("d", "", 0, 0, 0, 0),
    LC_LAST(),
};

luaConf funIntArg[] = {
    LC_ARG_INT(),
    LC_LAST(),
};

luaConf funDblArg[] = {
    LC_ARG_DBL(),
    LC_LAST(),
};

luaConf funStrArg[] = {
    LC_ARG_STR(),
    LC_LAST(),
};

luaConf funMultiArg[] = {
    LC_ARG_INT(),
    LC_ARG_DBL(),
    LC_ARG_STR(),
    LC_LAST(),
};

luaConf funIntListArg[] = {
    LC_ARG_INT_LIST(),
    LC_LAST(),
};

luaConf funDblListArg[] = {
    LC_ARG_DBL_LIST(),
    LC_LAST(),
};

luaConf funStrListArg[] = {
    LC_ARG_STR_LIST(),
    LC_LAST(),
};

luaConf funTableArg[] = {
    LC_ARG_TABLE(tableParams),
    LC_LAST(),
};

luaConf intReturn[] = {
    LC_ARG_INT(),
    LC_ARG_STR(),
    LC_LAST()
};

int *cFunction(lua_State *L) {
    printf("My c function\n");
    return 0;
}

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

    // LCT list parameters
    LC_INT_LIST("IntList",     "Integer List parameter",          0, 0, 0, 0),
    LC_DBL_LIST("DblList",     "Double List parameter",           0, 0, 0, 0),
    LC_INT_LIST("InvalidList", "Invalid Integer List",            0, 0, 0, 0),

    LC_STR_LIST("StrList",     "String list parameter",           0, NULL),

    LC_TABLE("TableParam",          tableParams),
    LC_TABLE_LIST("TableParamList", tableParams),

    // LCT constants
    LCT_INTEGER_CONST("IntConst", 32),
    LCT_DOUBLE_CONST("DblConst",  32.23),
    LCT_STRING_CONST("StrConst",  "A little string constant"),

    // LCT functions
    LCT_FUNCTION("MyFunction",      NULL, intReturn),
    LCT_FUNCTION("FunIntArg",       funIntArg, NULL),
    LCT_FUNCTION("FunDblArg",       funDblArg, NULL),
    LCT_FUNCTION("FunStrArg",       funStrArg, NULL),
    LCT_FUNCTION("FunMultiArg",     funMultiArg, NULL),
    LCT_FUNCTION("FunIntListArg",   funIntListArg, NULL),
    LCT_FUNCTION("FunDblListArg",   funDblListArg, NULL),
    LCT_FUNCTION("FunStrListArg",   funStrListArg, NULL),
    LCT_FUNCTION("FunTableArg",     funTableArg, NULL),
    LCT_FUNCTION("MissingFunction", NULL, NULL),

    LCT_FUNCTION("FunGlobalVarsToLua",   NULL, NULL),
    LCT_FUNCTION("FunGlobalVarsFromLua", NULL, NULL),


    // Global variables
    LC_GLOBAL_INT("GlobalInt"),
    LC_GLOBAL_DBL("GlobalDbl"),
    LC_GLOBAL_STR("GlobalStr"),
    LC_GLOBAL_BOOLEAN("GlobalBool"),

    // API test
    LCT_API("cFunction", NULL, cFunction),
    LCT_FUNCTION("TestCFunction",    NULL, NULL),

    // end
    LC_LAST(),
};

luaConf custom[] = {
    LC_INT("CInt1",        "Correct Integer parameter",       0, -42, 0, 0),
    LC_INT("CInt2",        "Correct Integer parameter",       0, -42, 0, 0),
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
    LCT     *lct;
    luaConf *ret;
    int i;

    lct = LCT_New(confTest);

    LCT_SetValuePtr(lct->params, "GlobalInt", &globalInt);
    LCT_SetValuePtr(lct->params, "GlobalDbl", &globalDbl);
    LCT_SetValuePtr(lct->params, "GlobalStr", globalStr);

    LCT_SetDefaults(confTest);

    LC_PrintParams(confTest);

    LCT_ReadFile(lct, "conftest.lua");

    LC_PrintParams(confTest);

    // Test of simple function call interface
    ret = LCT_FCallSimple(lct, "MyFunction");
    LC_PrintParams(ret);

    LCT_FCallSimple(lct, "FunIntArg", 43);
    LCT_FCallSimple(lct, "FunDblArg", 43.44);
    LCT_FCallSimple(lct, "FunStrArg", "Fun String");

    LCT_FCallSimple(lct, "FunIntListArg", validIntList, 7);
    LCT_FCallSimple(lct, "FunDblListArg", validDblList, 6);
    LCT_FCallSimple(lct, "FunStrListArg", myStrings,    6);
    //LCT_FCallSimple(lct, "FunTableArg",   funTableArg);
    //LCT_Init(tableParams);
    LCT_FCallSimple(lct, "FunTableArg",   tableParams);


    LCT_FCallSimple(lct, "FunMultiArg",   44, 45.45, "Fun String");
    LCT_FCallSimple(lct, "TestCFunction");

    LCT_FCallSimple(lct, "MissingFunction");



    for (i = 0; i < 10; i++) {
        globalInt = i;
        globalDbl = 2.22 * i;
        LCT_FCallSimple(lct, "FunGlobalVarsToLua");
    };

    for (i = 0; i < 10; i++) {
        globalInt = i;
        globalDbl = i;
        LCT_FCallSimple(lct, "FunGlobalVarsFromLua");
        printf("GlobalDbl=%2.2f  GlobalInt=%2d  i=%2d\n", globalDbl, globalInt, i);
    };



    LCT_File(confTest);

    //LCT_PrintProblems(confTest);

//    LCT_FCallSimple2(lct, "SimpleTest", "i", 23);
//    LCT_FCallSimple2(lct, "SimpleTest", "d", 43.68);
//    LCT_FCallSimple2(lct, "SimpleTest", "s", "En liten string");
//    LCT_FCallSimple2(lct, "SimpleTest", "ii", 23, 32);
    //LCT_FCallSimple2(lct, "SimpleTest", "I", *(int){1,2,3,66,8,99}, 3);

    exit(0);

}

void LC_UnitTest(void) {

}


