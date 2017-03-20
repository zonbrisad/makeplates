/**
 *---------------------------------------------------------------------------
 * @brief   A simple test class.
 *
 * @file    MyClass.cpp
 * @author  Your Name <your.name@yourdomain.org>
 * @date    2017-03-17
 * @licence GPLv2
 *
 *---------------------------------------------------------------------------
 */

// Includes ---------------------------------------------------------------

#include <stdio.h>
#include "MyClass.h"


// Macros -----------------------------------------------------------------

// Variables --------------------------------------------------------------

// Prototypes -------------------------------------------------------------

// Code -------------------------------------------------------------------

MyClass::MyClass() {
    printf("MyClass Constructor\n");
}

MyClass::MyClass(int x) {
    printf("MyClass Constructor %d\n", x);
}

void MyClass::Do(int i) {
    printf("MyClass::Do %d\n", i * 2);
}

void MyClass::Nisse(int kalle) {
}

void MyClass::Arne() {
}

void MyClass::Bertil() {
}


void MyClass::Kalle(int sss) {
}

int MyClass::Lisa(char *str) {
}

int MyClass::getA() const {
    return a;
}

void MyClass::setA(int a) {
    this->a = a;
}

int MyClass::getB() const {
    return b;
}

void MyClass::setB(int b) {
    this->b = b;
}
