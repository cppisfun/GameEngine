
#include "Precomp.h"

#include "../Base/LimitedValue.h"

using namespace misc;


SUITE (MiscLimitedValue)
{

   TEST (Cyclic)
   {
      LimitedInt var(1, 10, true, 1);     CHECK_EQUAL(1,  var.Value());
      var.Value(5);                       CHECK_EQUAL(5,  var.Value());
      var.Value(15);                      CHECK_EQUAL(5,  var.Value());
      var.Value(0);                       CHECK_EQUAL(10, var.Value());
      var++;                              CHECK_EQUAL(1,  var.Value());
      ++var;                              CHECK_EQUAL(2,  var.Value());
      var += 7;                           CHECK_EQUAL(9,  var.Value());
      var--;                              CHECK_EQUAL(8,  var.Value());
      --var;                              CHECK_EQUAL(7,  var.Value());
      var -= 2;                           CHECK_EQUAL(5,  var.Value());
      var *= 2;                           CHECK_EQUAL(10, var.Value());
      var /= 2;                           CHECK_EQUAL(5,  var.Value());

      CHECK_EQUAL(false, var == 9);
      CHECK_EQUAL(true,  var != 9);
      CHECK_EQUAL(true, var <  9);
      CHECK_EQUAL(true, var <= 9);
      CHECK_EQUAL(false,  var >  9);
      CHECK_EQUAL(false,  var >= 9);


      LimitedInt other(var);
      other.Value(2);

      var += other;     CHECK_EQUAL(7,  var.Value());
      var -= other;     CHECK_EQUAL(5,  var.Value());
      var *= other;     CHECK_EQUAL(10, var.Value());
      var /= other;     CHECK_EQUAL(5,  var.Value());

      CHECK_EQUAL(false, var == other);
      CHECK_EQUAL(true,  var != other);
      CHECK_EQUAL(false, var <  other);
      CHECK_EQUAL(false, var <= other);
      CHECK_EQUAL(true,  var >  other);
      CHECK_EQUAL(true,  var >= other);
   }

   TEST (NotCyclic)
   {
      LimitedInt var(1, 10, false, 1);    CHECK_EQUAL(1,  var.Value());
      var.Value(5);                       CHECK_EQUAL(5,  var.Value());
      var.Value(15);                      CHECK_EQUAL(10, var.Value());
      var.Value(0);                       CHECK_EQUAL(1,  var.Value());
      var++;                              CHECK_EQUAL(2,  var.Value());
      ++var;                              CHECK_EQUAL(3,  var.Value());
      var += 3;                           CHECK_EQUAL(6,  var.Value());
      var--;                              CHECK_EQUAL(5,  var.Value());
      --var;                              CHECK_EQUAL(4,  var.Value());
      var -= 2;                           CHECK_EQUAL(2,  var.Value());
      var *= 2;                           CHECK_EQUAL(4,  var.Value());
      var /= 2;                           CHECK_EQUAL(2,  var.Value());

      CHECK_EQUAL(false, var == 1);
      CHECK_EQUAL(true,  var != 1);
      CHECK_EQUAL(false, var <  1);
      CHECK_EQUAL(false, var <= 1);
      CHECK_EQUAL(true,  var >  1);
      CHECK_EQUAL(true,  var >= 1);


      LimitedInt other(var);
      other.Value(5);

      var += other;     CHECK_EQUAL(7,  var.Value());
      var -= other;     CHECK_EQUAL(2,  var.Value());
      var *= other;     CHECK_EQUAL(10, var.Value());
      var /= other;     CHECK_EQUAL(2,  var.Value());

      CHECK_EQUAL(false, var == other);
      CHECK_EQUAL(true,  var != other);
      CHECK_EQUAL(true,  var <  other);
      CHECK_EQUAL(true,  var <= other);
      CHECK_EQUAL(false, var >  other);
      CHECK_EQUAL(false, var >= other);
   }

}

