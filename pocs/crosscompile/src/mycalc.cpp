#include "mycalc.hpp"

namespace myapp
{
  MyCalc::MyCalc(){}

  int MyCalc::plus(int a, int b)
  {
    return a + b;
  }

  int MyCalc::minus(int a, int b)
  {
    return a - b;
  }

  int MyCalc::div(int a, int b)
  {
    return a / b;
  }

  int MyCalc::mult(int a, int b)
  {
    return a * b;
  }

  void MyCalc::range(unsigned char* p, int size)
  {
    if(size > 255){
      size = 255;
    }
    int i;
    p[0] = 0;
    for(i = 1; i < size; i++)
    {
      p[i] = p[i-1] + 1;
    }
  }

}
