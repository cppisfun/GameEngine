
#include "Precomp.h"

#include "../Base/Convert.h"

using namespace base;


SUITE (BaseConvert)
{

   TEST (AsBool)
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

   TEST (AsInt)
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

      CHECK_CLOSE(1234567890,  AsInt(1234567890.0f),  50);
      CHECK_CLOSE(-1234567890, AsInt(-1234567890.0f), 50);
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

   TEST (AsLong)
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

      CHECK_CLOSE(1234567890L,  AsLong(1234567890.0f),  50L);
      CHECK_CLOSE(-1234567890L, AsLong(-1234567890.0f), 50L);
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

   TEST (AsLongLong)
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

      CHECK_CLOSE(1234567890LL,  AsLong(1234567890.0f),  50LL);
      CHECK_CLOSE(-1234567890LL, AsLong(-1234567890.0f), 50LL);
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

   TEST (AsDouble)
   {
      CHECK_EQUAL(1234567890.0,  AsDouble("1234567890"));
      CHECK_EQUAL(-1234567890.0, AsDouble("-1234567890"));
      CHECK_EQUAL(789.0,         AsDouble("789IgnoreMe23"));
      CHECK_EQUAL(0.0,           AsDouble("theregoes789"));
      CHECK_EQUAL(0.0,           AsDouble(""));
      CHECK_EQUAL(123.45,        AsDouble("123.45"));
      CHECK_EQUAL(123.45,        AsDouble("123.45000"));
      CHECK_EQUAL(-567.89,       AsDouble("-567.89"));
      CHECK_EQUAL(-567.89,       AsDouble("-567.89000"));

      CHECK_EQUAL(0.0,           AsDouble(false));
      CHECK_EQUAL(1.0,           AsDouble(true));

      CHECK_EQUAL(1234567890.0,  AsDouble(1234567890));
      CHECK_EQUAL(-1234567890.0, AsDouble(-1234567890));
      CHECK_EQUAL(0.0,           AsDouble(0));

      CHECK_EQUAL(1234567890.0,  AsDouble(1234567890L));
      CHECK_EQUAL(-1234567890.0, AsDouble(-1234567890L));
      CHECK_EQUAL(0.0,           AsDouble(0L));

      CHECK_EQUAL(1234567890.0,  AsDouble(1234567890LL));
      CHECK_EQUAL(-1234567890.0, AsDouble(-1234567890LL));
      CHECK_EQUAL(0.0,           AsDouble(0LL));

      CHECK_CLOSE(1234567890.0,  AsDouble(1234567890.0f),  50);
      CHECK_CLOSE(-1234567890.0, AsDouble(-1234567890.0f), 50);
      CHECK_EQUAL(0.0,           AsDouble(0.0f));
      CHECK_CLOSE(123.45,        AsDouble(123.45f),  0.0001);
      CHECK_CLOSE(-567.89,       AsDouble(-567.89f), 0.0001);
   }

   TEST (AsFloat)
   {
      CHECK_EQUAL(1234567890.0f,  AsFloat("1234567890"));
      CHECK_EQUAL(-1234567890.0f, AsFloat("-1234567890"));
      CHECK_EQUAL(789.0f,         AsFloat("789IgnoreMe23"));
      CHECK_EQUAL(0.0f,           AsFloat("theregoes789"));
      CHECK_EQUAL(0.0f,           AsFloat(""));
      CHECK_EQUAL(123.45f,        AsFloat("123.45"));
      CHECK_EQUAL(123.45f,        AsFloat("123.45000"));
      CHECK_EQUAL(-567.89f,       AsFloat("-567.89"));
      CHECK_EQUAL(-567.89f,       AsFloat("-567.89000"));

      CHECK_EQUAL(0.0f,           AsFloat(false));
      CHECK_EQUAL(1.0f,           AsFloat(true));

      CHECK_EQUAL(1234567890.0f,  AsFloat(1234567890));
      CHECK_EQUAL(-1234567890.0f, AsFloat(-1234567890));
      CHECK_EQUAL(0.0f,           AsFloat(0));

      CHECK_EQUAL(1234567890.0f,  AsFloat(1234567890L));
      CHECK_EQUAL(-1234567890.0f, AsFloat(-1234567890L));
      CHECK_EQUAL(0.0f,           AsFloat(0L));

      CHECK_EQUAL(1234567890.0f,  AsFloat(1234567890LL));
      CHECK_EQUAL(-1234567890.0f, AsFloat(-1234567890LL));
      CHECK_EQUAL(0.0f,           AsFloat(0LL));

      CHECK_EQUAL(1234567890.0f,  AsFloat(1234567890.0));
      CHECK_EQUAL(-1234567890.0f, AsFloat(-1234567890.0));
      CHECK_EQUAL(0.0f,           AsFloat(0.0));
      CHECK_EQUAL(123.45f,        AsFloat(123.45));
      CHECK_EQUAL(-567.89f,       AsFloat(-567.89));
   }

   TEST (AsString)
   {
      CHECK_EQUAL("True",  AsString(true));
      CHECK_EQUAL("False", AsString(false));

      CHECK_EQUAL("1234567890",       AsString(1234567890, false));
      CHECK_EQUAL("-1234567890",      AsString(-1234567890, false));
      CHECK_EQUAL("0",                AsString(0, false));
      CHECK_EQUAL("1.234.567.890",    AsString(1234567890));
      CHECK_EQUAL("-1.234.567.890",   AsString(-1234567890));
      CHECK_EQUAL("0",                AsString(0));

      CHECK_EQUAL("1234567890",       AsString(1234567890L, false));
      CHECK_EQUAL("-1234567890",      AsString(-1234567890L, false));
      CHECK_EQUAL("0",                AsString(0L, false));
      CHECK_EQUAL("1.234.567.890",    AsString(1234567890L));
      CHECK_EQUAL("-1.234.567.890",   AsString(-1234567890L));
      CHECK_EQUAL("0",                AsString(0L));

      CHECK_EQUAL("1234567890",       AsString(1234567890LL, false));
      CHECK_EQUAL("-1234567890",      AsString(-1234567890LL, false));
      CHECK_EQUAL("0",                AsString(0LL, false));
      CHECK_EQUAL("1.234.567.890",    AsString(1234567890LL));
      CHECK_EQUAL("-1.234.567.890",   AsString(-1234567890LL));
      CHECK_EQUAL("0",                AsString(0LL));

      CHECK_EQUAL("1234567936.0",     AsString(1234567890.0f, 1, false));
      CHECK_EQUAL("-1234567936.0",    AsString(-1234567890.0f, 1, false));
      CHECK_EQUAL("123.44",           AsString(123.45f, 2, false));
      CHECK_EQUAL("123.456",          AsString(123.456789f, 3, false));
      CHECK_EQUAL("-123.44",          AsString(-123.45f, 2, false));
      CHECK_EQUAL("-123.456",         AsString(-123.456789f, 3, false));
      CHECK_EQUAL("123.44999",        AsString(123.45f, 5, false));
      CHECK_EQUAL("-123.44999",       AsString(-123.45f, 5, false));

      CHECK_EQUAL("1.234.567.936,0",  AsString(1234567890.0f, 1));
      CHECK_EQUAL("-1.234.567.936,0", AsString(-1234567890.0f, 1));
      CHECK_EQUAL("123,44",           AsString(123.45f));
      CHECK_EQUAL("123,456",          AsString(123.456789f, 3));
      CHECK_EQUAL("-123,44",          AsString(-123.45f));
      CHECK_EQUAL("-123,456",         AsString(-123.456789f, 3));
      CHECK_EQUAL("123,44999",        AsString(123.45f, 5));
      CHECK_EQUAL("-123,44999",       AsString(-123.45f, 5));

      CHECK_EQUAL("1234567890.0",     AsString(1234567890.0, 1, false));
      CHECK_EQUAL("-1234567890.0",    AsString(-1234567890.0, 1, false));
      CHECK_EQUAL("123.45",           AsString(123.45, 2, false));
      CHECK_EQUAL("123.456",          AsString(123.456789, 3, false));
      CHECK_EQUAL("-123.45",          AsString(-123.45, 2, false));
      CHECK_EQUAL("-123.456",         AsString(-123.456789, 3, false));
      CHECK_EQUAL("123.45000",        AsString(123.45, 5, false));
      CHECK_EQUAL("-123.45000",       AsString(-123.45, 5, false));

      CHECK_EQUAL("1.234.567.890,0",  AsString(1234567890.0, 1));
      CHECK_EQUAL("-1.234.567.890,0", AsString(-1234567890.0, 1));
      CHECK_EQUAL("123,45",           AsString(123.45));
      CHECK_EQUAL("123,456",          AsString(123.456789, 3));
      CHECK_EQUAL("-123,45",          AsString(-123.45));
      CHECK_EQUAL("-123,456",         AsString(-123.456789, 3));
      CHECK_EQUAL("123,45000",        AsString(123.45, 5));
      CHECK_EQUAL("-123,45000",       AsString(-123.45, 5));
   }

   TEST (StringBinary)
   {
      std::vector<char> binary;
      binary.push_back('T'); binary.push_back('e'); binary.push_back('s'); binary.push_back('t'); binary.push_back(' ');
      binary.push_back('T'); binary.push_back('E'); binary.push_back('S'); binary.push_back('T'); binary.push_back(' ');
      binary.push_back('t'); binary.push_back('e'); binary.push_back('s'); binary.push_back('t');

      CHECK_EQUAL("Test TEST test", AsString(binary));

      binary.clear();

      const std::string stdString = "Test TEST test";
      binary                      = AsBinary(stdString);

      CHECK_EQUAL(stdString.size(), binary.size());

      if (stdString.size() == binary.size()) {
         for (size_t i = 0; i < stdString.size(); ++i) {
            CHECK_EQUAL(stdString[i], binary[i]);
         }
      }
   }

}

