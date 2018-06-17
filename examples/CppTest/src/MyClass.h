/**
 *---------------------------------------------------------------------------
 * @brief   A simple test class.
 *
 * @file    MyClass.h
 * @author  Your Name <your.name@yourdomain.org>
 * @date    2017-03-17
 * @licence GPLv2
 *
 *---------------------------------------------------------------------------
 */

#ifndef MYCLASS_H
#define MYCLASS_H

// Includes ---------------------------------------------------------------

// Macros -----------------------------------------------------------------

// Typedefs ---------------------------------------------------------------

// Variables --------------------------------------------------------------

class MyClass {
  public:
    MyClass();
    MyClass(int x);
    void Do(int i);
    void Nisse(int kalle);
    void Arne();
    void Bertil();
    void Kalle(int sss);
    int Lisa(char *str);
    int getA() const;
    void setA(int a);
    int getB() const;
    void setB(int b);

  private:
    int a;
    int b;

};

#endif

