#include <emscripten/bind.h>
#include "mycalc.hpp"

using namespace myapp;

namespace  myappjs
{
  emscripten::val plus(MyCalc& mycalc, int a, int b)
  {
    return emscripten::val(mycalc.plus(a, b));
  }

  emscripten::val minus(MyCalc& mycalc, int a, int b)
  {
    return emscripten::val(mycalc.minus(a, b));
  }

  emscripten::val div(MyCalc& mycalc, int a, int b)
  {
    if(b == 0)
    {
       return emscripten::val::undefined();
    }
    else
    {
       return emscripten::val(mycalc.div(a, b));
    }
  }

  emscripten::val mult(MyCalc& mycalc, int a, int b)
  {
    return emscripten::val(mycalc.mult(a, b));
  }

  emscripten::val range(MyCalc& mycalc, intptr_t data, int size)
  {
    mycalc.range(reinterpret_cast<unsigned char*>(data), size);
    return emscripten::val::undefined();
  }
}

EMSCRIPTEN_BINDINGS(myappjs)
{
  emscripten::class_<MyCalc>("MyCalc")
    .constructor<>()
    .function("plus", &myappjs::plus)
    .function("minus", &myappjs::minus)
    .function("div", &myappjs::div)
    .function("mult", &myappjs::mult)
    .function("range", &myappjs::range, emscripten::allow_raw_pointers());
}
