
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

   TEST(AsInt)
   {
      CHECK_EQUAL(1234567890,  AsInt("1234567890"));
      CHECK_EQUAL(-1234567890, AsInt("-1234567890"));
      CHECK_EQUAL(789,         AsInt("789IgnoreMe23"));
      CHECK_EQUAL(0,           AsInt("theregoes789"));
      CHECK_EQUAL(0,           AsInt(""));

      CHECK_EQUAL(0,           AsInt(false));
      CHECK_EQUAL(1,           AsInt(true));

      CHECK_EQUAL(1234567890,  AsInt(1234567890L));
      CHECK_EQUAL(-1234567890, AsInt(-1234567890L));
      CHECK_EQUAL(0,           AsInt(0L));

      CHECK_EQUAL(1234567890,  AsInt(1234567890LL));
      CHECK_EQUAL(-1234567890, AsInt(-1234567890LL));
      CHECK_EQUAL(0,           AsInt(0LL));

      CHECK_EQUAL(1234567936,  AsInt(1234567890.0f));    // hmm, do sth.?
      CHECK_EQUAL(-1234567936, AsInt(-1234567890.0f));   // dito
      CHECK_EQUAL(0,           AsInt(0.0f));
      CHECK_EQUAL(0,           AsInt(0.123f));
      CHECK_EQUAL(0,           AsInt(0.987f));
      CHECK_EQUAL(0,           AsInt(-0.123f));
      CHECK_EQUAL(0,           AsInt(-0.987f));

      CHECK_EQUAL(1234567890,  AsInt(1234567890.0));
      CHECK_EQUAL(-1234567890, AsInt(-1234567890.0));
      CHECK_EQUAL(0,           AsInt(0.0));
      CHECK_EQUAL(0,           AsInt(0.123));
      CHECK_EQUAL(0,           AsInt(0.987));
      CHECK_EQUAL(0,           AsInt(-0.123));
      CHECK_EQUAL(0,           AsInt(-0.987));
   }

   TEST(AsLong)
   {
      CHECK_EQUAL(1234567890L,  AsLong("1234567890"));
      CHECK_EQUAL(-1234567890L, AsLong("-1234567890"));
      CHECK_EQUAL(789L,         AsInt("789IgnoreMe23"));
      CHECK_EQUAL(0L,           AsLong("theregoes789"));
      CHECK_EQUAL(0L,           AsLong(""));

      CHECK_EQUAL(0L,           AsLong(false));
      CHECK_EQUAL(1L,           AsLong(true));

      CHECK_EQUAL(1234567890L,  AsLong(1234567890));
      CHECK_EQUAL(-1234567890L, AsLong(-1234567890));
      CHECK_EQUAL(0L,           AsLong(0));

      CHECK_EQUAL(1234567890L,  AsLong(1234567890LL));
      CHECK_EQUAL(-1234567890L, AsLong(-1234567890LL));
      CHECK_EQUAL(0L,           AsLong(0LL));

      CHECK_EQUAL(1234567936L,  AsLong(1234567890.0f));  // hmm, do sth.?
      CHECK_EQUAL(-1234567936L, AsLong(-1234567890.0f)); // dito
      CHECK_EQUAL(0L,           AsLong(0.0f));
      CHECK_EQUAL(0L,           AsLong(0.123f));
      CHECK_EQUAL(0L,           AsLong(0.987f));
      CHECK_EQUAL(0L,           AsLong(-0.123f));
      CHECK_EQUAL(0L,           AsLong(-0.987f));

      CHECK_EQUAL(1234567890L,  AsLong(1234567890.0));
      CHECK_EQUAL(-1234567890L, AsLong(-1234567890.0));
      CHECK_EQUAL(0L,           AsLong(0.0));
      CHECK_EQUAL(0L,           AsLong(0.123));
      CHECK_EQUAL(0L,           AsLong(0.987));
      CHECK_EQUAL(0L,           AsLong(-0.123));
      CHECK_EQUAL(0L,           AsLong(-0.987));
   }

   TEST(AsLongLong)
   {
      CHECK_EQUAL(1234567890LL,  AsLong("1234567890"));
      CHECK_EQUAL(-1234567890LL, AsLong("-1234567890"));
      CHECK_EQUAL(789LL,         AsInt("789IgnoreMe23"));
      CHECK_EQUAL(0LL,           AsLong("theregoes789"));
      CHECK_EQUAL(0LL,           AsLong(""));

      CHECK_EQUAL(0LL,           AsLong(false));
      CHECK_EQUAL(1LL,           AsLong(true));

      CHECK_EQUAL(1234567890LL,  AsLong(1234567890));
      CHECK_EQUAL(-1234567890LL, AsLong(-1234567890));
      CHECK_EQUAL(0LL,           AsLong(0));

      CHECK_EQUAL(1234567890LL,  AsLong(1234567890L));
      CHECK_EQUAL(-1234567890LL, AsLong(-1234567890L));
      CHECK_EQUAL(0LL,           AsLong(0L));

      CHECK_EQUAL(1234567936LL,  AsLong(1234567890.0f));  // hmm, do sth.?
      CHECK_EQUAL(-1234567936LL, AsLong(-1234567890.0f)); // dito
      CHECK_EQUAL(0LL,           AsLong(0.0f));
      CHECK_EQUAL(0LL,           AsLong(0.123f));
      CHECK_EQUAL(0LL,           AsLong(0.987f));
      CHECK_EQUAL(0LL,           AsLong(-0.123f));
      CHECK_EQUAL(0LL,           AsLong(-0.987f));

      CHECK_EQUAL(1234567890LL,  AsLong(1234567890.0));
      CHECK_EQUAL(-1234567890LL, AsLong(-1234567890.0));
      CHECK_EQUAL(0LL,           AsLong(0.0));
      CHECK_EQUAL(0LL,           AsLong(0.123));
      CHECK_EQUAL(0LL,           AsLong(0.987));
      CHECK_EQUAL(0LL,           AsLong(-0.123));
      CHECK_EQUAL(0LL,           AsLong(-0.987));
   }

}

