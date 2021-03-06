/**
 *---------------------------------------------------------------------------
 * @brief   Makeplates main example file.
 *
 * @file    main.cpp
 * @author  Peter Malmberg <peter.malmberg@gmail.com>
 * @date    2016-10-24
 * @license GPLv2
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
#include <vector>
#include <array>
#include <string>

#include "MyClass.h"

#include "def.h"

using namespace std;

// Defines ----------------------------------------------------------------

#define PROGNAME "makeplate"

// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------
void sigInt(int sig);
void sigHup(int sig);

// Code -------------------------------------------------------------------

class Kalle {
  private:
    int a;

  public:
    Kalle() {
        a = 1;
    }

    void Do(void) {
        printf("Do %d\n", a);
    }
};


void sigInt(int sig) {
    UNUSED(sig);

    printf("\nExiting program\n");
    exit(0);
}

void sigHup(int sig) {
    UNUSED(sig);
    printf("Sighup\n");
}


int main(int argc, char *argv[]) {
    int i;
    MyClass a, *b;
    vector<MyClass *> mcList;
    string str;
    Kalle *k;

    UNUSED(argc);
    UNUSED(argv);

    signal(SIGINT, sigInt);
    signal(SIGHUP, sigHup);

    printf("\nMakeplate linux C++ example.\n\n\n");

    a.Do(1);

    b = new MyClass;

    b->Do(10);

    for (i = 0; i < 10; i++) {
        b = new MyClass(i);
        mcList.push_back(b);
    }

    for (i = 0; i < mcList.size(); i++) {
        mcList[i]->Do(i);
    }

    k = new Kalle;
    k->Do();

    return 0;
}
