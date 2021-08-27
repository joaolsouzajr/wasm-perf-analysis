#ifndef MYCALC_HPP // include guard
#define MYCALC_HPP

namespace myapp
{

  class MyCalc
  {
    public:
      MyCalc();

      /**
       * Addition
       *
       * @return a + b
       */
      int plus(int a, int b);

      /**
       * Subtraction
       *
       * @return
       */
      int minus(int a, int b);

      /**
       * Division
       *
       * @return a / b
       */
      int div(int a, int b);

      /**
       * Multiplication
       *
       * @return a * b
       */
      int mult(int a, int b);

      void range(unsigned char* mat, int size=255);

      // void apply(uint8_t* values, uint8_t factor);

      // void copyByRef(uint8_t& matrixA, uint8_t& matrixB, int size);
  };

}

#endif /* MYCALC_HPP */

