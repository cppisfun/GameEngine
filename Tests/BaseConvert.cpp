
#include "Precomp.h"

#include "../Base/Convert.h"

using namespace base;


SUITE(BaseConvert)
{

   TEST(AsBool)
   {
      CHECK_EQUAL(true,  AsBool("true"));
      CHECK_EQUAL(true,  AsBool("TRUE"));
      CHECK_EQUAL(true,  AsBool("True"));
      CHECK_EQUAL(false, AsBool(""));
      CHECK_EQUAL(false, AsBool(" true"));
      CHECK_EQUAL(false, AsBool("true1"));

      CHECK_EQUAL(false, AsBool(0));
      CHECK_EQUAL(true,  AsBool(1));
      CHECK_EQUAL(true,  AsBool(-1));

      CHECK_EQUAL(false, AsBool(0L));
      CHECK_EQUAL(true,  AsBool(1L));
      CHECK_EQUAL(true,  AsBool(-1L));

      CHECK_EQUAL(false, AsBool(0LL));
      CHECK_EQUAL(true,  AsBool(1LL));
      CHECK_EQUAL(true,  AsBool(-1LL));

      CHECK_EQUAL(false, AsBool(0.0f));
      CHECK_EQUAL(true,  AsBool(1.0f));
      CHECK_EQUAL(true,  AsBool(0.1f));
      CHECK_EQUAL(true,  AsBool(-0.1f));
      CHECK_EQUAL(true,  AsBool(-1.0f));

      CHECK_EQUAL(false, AsBool(0.0));
      CHECK_EQUAL(true,  AsBool(1.0));
      CHECK_EQUAL(true,  AsBool(0.1));
      CHECK_EQUAL(true,  AsBool(-0.1));
      CHECK_EQUAL(true,  AsBool(-1.0));
   }

}

