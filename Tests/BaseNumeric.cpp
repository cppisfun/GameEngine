
#include "Precomp.h"

#include "../Base/Numeric.h"

using namespace base;


SUITE (BaseNumeric)
{

   TEST (Fraction)
   {
      CHECK_EQUAL(0.0f,         Fraction(0.0f));
      CHECK_EQUAL(0.0f,         Fraction(1234567890.0f));
      CHECK_EQUAL(0.0f,         Fraction(-1234567890.0f));
      CHECK_EQUAL(0.789001f,    Fraction(456.789f));        // hmm, do sth.?
      CHECK_EQUAL(0.789001f,    Fraction(-456.789f));       // dito
      CHECK_EQUAL(0.123456789f, Fraction(0.123456789f));
      CHECK_EQUAL(0.123456789f, Fraction(-0.123456789f));

      CHECK_EQUAL(0.0,          Fraction(0.0));
      CHECK_EQUAL(0.0,          Fraction(1234567890.0));
      CHECK_EQUAL(0.0,          Fraction(-1234567890.0));
      CHECK_EQUAL(0.789,        Fraction(456.789));
      CHECK_EQUAL(0.789,        Fraction(-456.789));
      CHECK_EQUAL(0.123456789,  Fraction(0.123456789));
      CHECK_EQUAL(0.123456789,  Fraction(-0.123456789));
   }

}

