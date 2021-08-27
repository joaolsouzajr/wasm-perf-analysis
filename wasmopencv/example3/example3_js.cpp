#include <emscripten/bind.h>
#include "example3.hpp"

namespace myappjs
{
  emscripten::val minus(myapp::MyCalc& mycalc, int a, int b)
  {
    return emscripten::val(mycalc.minus(a, b));
  }
}

EMSCRIPTEN_BINDINGS(myappjs)
{
  emscripten::class_<myapp::MyCalc>("MyCalc")
    .constructor<>()
    .function("plus", &myapp::MyCalc::plus)
    .function("minus", &myappjs::minus);
}
