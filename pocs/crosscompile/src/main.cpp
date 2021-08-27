#include <iostream>
#include <assert.h>
#include "mycalc.hpp"

using namespace myapp;

int main(int argc, char ** argv)
{
  std::cout << "helloc crosscompile with cmake" << std::endl;

  MyCalc calc;
  assert (2==calc.plus(1,1));
  // assert (1==calc.minus(2,1));
  // assert (1==calc.div(2,2));
  // assert (2==calc.mult(2,1));

  // unsigned char p[10];
  // calc.range(p, 10);
  // int i = 0;
  // for(;i<10;i++){
  //   assert (i==p[i]);
  // }

  return 0;
}
