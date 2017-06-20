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
#include "def_util.h"

// Defines ----------------------------------------------------------------

#define PROGNAME "makeplate"

// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------
void sigInt(int sig);
void sigHup(int sig);

void colorTest(void);
void I2S_tests(void);
void S2S_tests(void);
void defTest(void);
void unitTest(void);

// Code -------------------------------------------------------------------


void escapeFilter(char *str) {
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
 
void setUp(void) {
}

void tearDown(void) {
}

	
void I2S_tests() {
	I2S *db;

	db = I2S_copy(numbersDb);
	TEST_ASSERT_EQUAL_INT(2, I2S_findIdxStr(db, "Third"));

	TEST_ASSERT_EQUAL_INT(4, I2S_len(numbersDb));
	TEST_ASSERT_EQUAL_STRING("Last", I2S_getValue(numbersDb, 4));
	TEST_ASSERT_EQUAL_INT(2, I2S_findIdx(numbersDb, 3));
	TEST_ASSERT_EQUAL_INT(2, I2S_findIdxStr(numbersDb, "Third"));
	
	I2S_setValue(numbersDb, 4, "Nisse");
	TEST_ASSERT_EQUAL_STRING("Nisse", I2S_getValue(numbersDb, 4));

	I2S_setKeyValue(numbersDb, 0, 22, "kv22");
	TEST_ASSERT_EQUAL_INT(0, I2S_findIdx(numbersDb, 22));
	TEST_ASSERT_EQUAL_STRING("kv22", I2S_getValue(numbersDb, 22));

}

int ia[] = { 12, 33, 54, 11, 412, -443 };

int ix[] = { 44, 33, 54, 11, 412, -443 };

void S2S_tests() {
	TEST_ASSERT_EQUAL_INT(12,12);
	ia[0] = 44;
	TEST_ASSERT_EQUAL_INT_ARRAY( ix,  ia, 6);

	TEST_ASSERT_TRUE(  isWithin(  5, -10, 10));
	TEST_ASSERT_TRUE(  isWithin( -5, -10, 10));
	TEST_ASSERT_FALSE( isWithin( 11, -10, 10));
	TEST_ASSERT_FALSE( isWithin(-11, -10, 10));
	
	TEST_ASSERT_TRUE( isOutside( 15, -10, 10));
	TEST_ASSERT_TRUE( isOutside(-15, -10, 10));

	TEST_ASSERT_FALSE( isOutside(-5, -10, 10));
	TEST_ASSERT_FALSE( isOutside( 5, -10, 10));

}

void defTests() {
	TEST_ASSERT_EQUAL_INT(10, Max( 10,   5));
	TEST_ASSERT_EQUAL_INT(10, Max(  5,  10));
	TEST_ASSERT_EQUAL_INT( 5, Max(  5, -10));
	TEST_ASSERT_EQUAL_INT( 5, Max(-10,   5));

	TEST_ASSERT_EQUAL_INT(  5, Min( 10,   5));
	TEST_ASSERT_EQUAL_INT(  5, Min(  5,  10));
	TEST_ASSERT_EQUAL_INT(-10, Min(  5, -10));
	TEST_ASSERT_EQUAL_INT(-10, Min(-10,   5));

	TEST_ASSERT_EQUAL_INT(485,  Abs( 485));
	TEST_ASSERT_EQUAL_INT(485,  Abs(-485));
	
	TEST_ASSERT_EQUAL_INT( 42, Clamp( 42, -100, 100));
	TEST_ASSERT_EQUAL_INT( 32, Clamp( 42, -100,  32));
	TEST_ASSERT_EQUAL_INT(-42, Clamp(-42, -100, 100));
	TEST_ASSERT_EQUAL_INT(-32, Clamp(-42, - 32, 100));

	
	TEST_ASSERT_EQUAL_INT(0xF100,             Swap16(0x00F1));
	TEST_ASSERT_EQUAL_INT(0xCDAB0000,         Swap32(0x0000ABCD));
	TEST_ASSERT_EQUAL_INT(0xDDCCBBAA00000000, Swap64(0x00000000AABBCCDD));

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
	int x;

	UNUSED(argc);
	UNUSED(argv);
	
	unitTest();

	printf("Binary %s\n", int2bin(0xAA, 8));
	printf("Binary %s\n", int2bin(0xFF, 8));
	printf("Binary %s\n", int2bin(0xAAAA,16));
	printf("Binary %s\n", int2bin(0xAAFFAAFF,32));
	printf("Binary %s\n", int2bin(0xAAFFAAFF,48));
	
/*
	printf("|||||||+--\n");
	printf("||||||+---\n");
	printf("|||||+----\n");
	printf("||||+-----\n");
	printf("|||+------\n");
	printf("||+-------\n");
	printf("|+--------\n");
	printf("+---------\n");
	*/


	x = 0;
	printf("x = %s\n", int2bin(x, 8));
  Set_bits(x, 0x2);
	printf("x = %s\n", int2bin(x, 8));

	Set_bits(x, 0xF0);
	printf("x = %s\n", int2bin(x, 8));

	Clr_bits(x, 0xA0);
	printf("x = %s\n", int2bin(x, 8));

	Tgl_bits(x, 0x8);
	printf("x = %s\n", int2bin(x, 8));

//	x = bit_reverse8(x);
//	printf("x = %s\n", int2bin(x, 8));
	
	
	
	return 0;
}
