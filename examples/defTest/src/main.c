/**
 *---------------------------------------------------------------------------
 * @brief   Makeplates main example file.
 *
 * @file    main.c
 * @author  Peter Malmberg <peter.malmberg@gmail.com>
 * @date    2016-10-24
 * @licence GPLv2
 *
 *---------------------------------------------------------------------------
 */

// Includes ---------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#include "def.h"
#include "pmutil.h"

// Defines ----------------------------------------------------------------

#define PROGNAME "makeplate"

// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------
void sigInt(int sig);
void sigHup(int sig);

// Code -------------------------------------------------------------------


void escapeFilter(char *str) {
    int i;
    int len;
    len = strlen(str);
}

S2S fgColors[] = {
    { E_BLACK,      "Black"    },
    { E_RED,        "Red"      },
    { E_GREEN,      "Green"    },
    { E_YELLOW,     "Yellow"   },
    { E_BLUE ,      "Blue"     },
    { E_MAGENTA,    "Magenta"  },
    { E_CYAN,       "Cyan"     },
    { E_GRAY,       "Gray"     },
    { E_DARKGRAY,   "Darkgray" },
    { E_BR_RED,     "Br Red"     },
    { E_BR_GREEN,   "Br Green"   },
    { E_BR_YELLOW,  "Br Yellow"  },
    { E_BR_BLUE,    "Br Blue"    },
    { E_BR_MAGENTA, "Br Magenta" },
    { E_BR_CYAN,    "Br Cyan"    },
    { E_WHITE,      "White"          },
    { S2S_END }
};

S2S bgColors[] = {
    { E_ON_BLACK,   "Black"   },
    { E_ON_RED,     "Red"     },
    { E_ON_GREEN,   "Green"   },
    { E_ON_YELLOW,  "Yellow"  },
    { E_ON_BLUE,    "Blue"    },
    { E_ON_MAGENTA, "Magenta" },
    { E_ON_CYAN,    "Cyan"    },
    { E_ON_WHITE,   "White"   },
    { S2S_END }
};


void colorTest(void) {
    int i, j;


    for (j = 0; j < S2S_len(bgColors); j++) {
        for (i = 0; i < S2S_len(fgColors); i++) {
            printf("%s%s %s "E_END, bgColors[j].key, fgColors[i].key, fgColors[i].val);
        }

        printf("\n");
    }

    printf("\n");
    printf(E_ATTR_BOLD"Bolt text\n"E_END);
    printf(E_ATTR_LOWI"Low intensity text\n"E_END);
    printf(E_ATTR_UNDERLINE"Underline text\n"E_END);
    printf(E_ATTR_REVERSE"Reverse text\n"E_END);

    printf("\n");
}

void sigInt(int sig) {
    UNUSED(sig);

    printf("\nExiting program\n");
    exit(0);
}

void sigHup(int sig) {
    UNUSED(sig);
    printf("Sighup\n");
}


#include "unity.h"

I2S numbersDb[] = {
    { 1, "First"  },
    { 2, "Second" },
    { 3, "Third"  },
    { 4, "Last"   },
    { I2S_END     },
};

//I2S tDb[] = numbersDb;
 
void setUp(void) {
}

void tearDown(void) {
}


void I2S_tests() {
	int i;
	TEST_ASSERT_EQUAL_INT(4, I2S_len(numbersDb));
	TEST_ASSERT_EQUAL_STRING("Last", I2S_getString(numbersDb, 4));
	TEST_ASSERT_EQUAL_INT(2, I2S_findIdx(numbersDb, 3));
	TEST_ASSERT_EQUAL_INT(2, I2S_findIdxStr(numbersDb, "Third"));
	
	I2S_setString(numbersDb, 4, "Nisse");
	TEST_ASSERT_EQUAL_STRING("Nisse", I2S_getString(numbersDb, 4));
}

int ia[] = { 12, 33, 54, 11, 412, -443 };

int ix[] = { 44, 33, 54, 11, 412, -443 };

void S2S_tests() {
	TEST_ASSERT_EQUAL_INT(12,12);
	ia[0] = 44;
	TEST_ASSERT_EQUAL_INT_ARRAY( ix,  ia, 6);

}

void defTests() {
	TEST_ASSERT_EQUAL_INT(10, MAX( 10,   5));
	TEST_ASSERT_EQUAL_INT(10, MAX(  5,  10));
	TEST_ASSERT_EQUAL_INT( 5, MAX(  5, -10));
	TEST_ASSERT_EQUAL_INT( 5, MAX(-10,   5));

	TEST_ASSERT_EQUAL_INT(  5, MIN( 10,   5));
	TEST_ASSERT_EQUAL_INT(  5, MIN(  5,  10));
	TEST_ASSERT_EQUAL_INT(-10, MIN(  5, -10));
	TEST_ASSERT_EQUAL_INT(-10, MIN(-10,   5));

	TEST_ASSERT_EQUAL_INT(485,  ABS( 485));
	TEST_ASSERT_EQUAL_INT(485,  ABS(-485));
	
	TEST_ASSERT_EQUAL_INT( 42, CLAMP( 42, -100, 100));
	TEST_ASSERT_EQUAL_INT( 32, CLAMP( 42, -100,  32));
	TEST_ASSERT_EQUAL_INT(-42, CLAMP(-42, -100, 100));
	TEST_ASSERT_EQUAL_INT(-32, CLAMP(-42, - 32, 100));

	
	TEST_ASSERT_EQUAL_INT(0xFF00, Swap16(0x00FF));

}


void unitTest(void) {
	
	printf("Swap %X\n", Swap16(0xFF00));
	
	UNITY_BEGIN();
	RUN_TEST(I2S_tests);
	RUN_TEST(S2S_tests);
	RUN_TEST(defTests);
	return UNITY_END();
	

}


//#define SOMETEXT  This_is_some_text

void defTest(void) {
	int unusedVariable;
	
	UNUSED(unusedVariable);
	//printf("MACRO to text: %s\n", STRINGIFY(SOMETEXT));
	
}


int main(int argc, char *argv[]) {
    int i;

	unitTest();
	exit(0);
	
    UNUSED(argc);
    UNUSED(argv);

    signal(SIGINT, sigInt);
    signal(SIGHUP, sigHup);


    printf("\nMakeplate linux C example.\n\n\n");

    colorTest();

    INFOPRINT("Information printout\n");

    DEBUGPRINT("Debug printout\n");

    WARNINGPRINT("Warning printout\n");

    ERRORPRINT("Error printout\n");

    DEBUG_DO(printf("Debug do\n"));

    i = 0;

    printf("Var i = %2x\n", i);
    BIT_SET(i, 4);
    printf("Var i = %2x\n", i);
    BIT_SET(i, 2);
    printf("Var i = %2x\n", i);
    BIT_CLEAR(i, 4);
    printf("Var i = %2x\n", i);

    printf("Size of I2S db = %d\n", I2S_len(numbersDb));

    for (i = 1; i <= 4; i++) {
        printf("I2S test %d  =  %s\n", i, I2S_getString(numbersDb, i));
    }

    I2S_setString(numbersDb, 4, "Fourth");
    printf("I2S test %d  =  %s\n", 4, I2S_getString(numbersDb, 4));

    return 0;
}
