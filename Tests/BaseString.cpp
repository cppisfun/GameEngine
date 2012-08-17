
#include "Precomp.h"

#include "../Base/String.h"

using namespace base;


SUITE (BaseString)
{

   TEST (TrimFunctions)
   {
      CHECK_EQUAL("",         LTrim(""));
      CHECK_EQUAL("",         LTrim("   "));
      CHECK_EQUAL("test",     LTrim("test"));
      CHECK_EQUAL("test",     LTrim("   test"));
      CHECK_EQUAL("test   ",  LTrim("test   "));
      CHECK_EQUAL("test   ",  LTrim("   test   "));
      CHECK_EQUAL("t e s t ", LTrim(" t e s t "));

      CHECK_EQUAL("",         RTrim(""));
      CHECK_EQUAL("",         RTrim("   "));
      CHECK_EQUAL("test",     RTrim("test"));
      CHECK_EQUAL("   test",  RTrim("   test"));
      CHECK_EQUAL("test",     RTrim("test   "));
      CHECK_EQUAL("   test",  RTrim("   test   "));
      CHECK_EQUAL(" t e s t", RTrim(" t e s t "));

      CHECK_EQUAL("",         Trim(""));
      CHECK_EQUAL("",         Trim("   "));
      CHECK_EQUAL("test",     Trim("test"));
      CHECK_EQUAL("test",     Trim("   test"));
      CHECK_EQUAL("test",     Trim("test   "));
      CHECK_EQUAL("test",     Trim("   test   "));
      CHECK_EQUAL("t e s t",  Trim(" t e s t "));
   }

   TEST (FillFunctions)
   {
      CHECK_EQUAL("",        LFill("", -1, ""));
      CHECK_EQUAL("",        LFill("", 0, ""));
      CHECK_EQUAL("",        LFill("", 1, ""));
      CHECK_EQUAL("",        LFill("", -1, "+"));
      CHECK_EQUAL("",        LFill("", 0, "+"));
      CHECK_EQUAL("+",       LFill("", 1, "+"));
      CHECK_EQUAL("123",     LFill("123", 3, "+"));
      CHECK_EQUAL("+++123",  LFill("123", 6, "+"));
      CHECK_EQUAL("test123", LFill("123", 7, "test"));
      CHECK_EQUAL("test1",   LFill("123", 5, "test"));

      CHECK_EQUAL("",        RFill("", -1, ""));
      CHECK_EQUAL("",        RFill("", 0, ""));
      CHECK_EQUAL("",        RFill("", 1, ""));
      CHECK_EQUAL("",        RFill("", -1, "+"));
      CHECK_EQUAL("",        RFill("", 0, "+"));
      CHECK_EQUAL("+",       RFill("", 1, "+"));
      CHECK_EQUAL("123",     RFill("123", 3, "+"));
      CHECK_EQUAL("123+++",  RFill("123", 6, "+"));
      CHECK_EQUAL("123test", RFill("123", 7, "test"));
      CHECK_EQUAL("123te",   RFill("123", 5, "test"));
   }

   TEST (SubstringFunctions)
   {
      CHECK_EQUAL("",     Left("", -1));
      CHECK_EQUAL("",     Left("", 0));
      CHECK_EQUAL("",     Left("", 1));
      CHECK_EQUAL("",     Left("test", -1));
      CHECK_EQUAL("",     Left("test", 0));
      CHECK_EQUAL("te",   Left("test", 2));
      CHECK_EQUAL("test", Left("test", 4));
      CHECK_EQUAL("test", Left("test", 5));

      CHECK_EQUAL("",     Right("", -1));
      CHECK_EQUAL("",     Right("", 0));
      CHECK_EQUAL("",     Right("", 1));
      CHECK_EQUAL("",     Right("test", -1));
      CHECK_EQUAL("",     Right("test", 0));
      CHECK_EQUAL("st",   Right("test", 2));
      CHECK_EQUAL("test", Right("test", 4));
      CHECK_EQUAL("test", Right("test", 5));
   }

   TEST (CaseFunctions)
   {
      CHECK_EQUAL("",          Upper(""));
      CHECK_EQUAL("   ",       Upper("   "));
      CHECK_EQUAL("ABC",       Upper("abc"));
      CHECK_EQUAL("ABC",       Upper("ABC"));
      CHECK_EQUAL("AABBCC",    Upper("aAbBcC"));
      CHECK_EQUAL("123456789", Upper("123456789"));
      CHECK_EQUAL("!$%&()=?*", Upper("!$%&()=?*"));

      CHECK_EQUAL("",          Lower(""));
      CHECK_EQUAL("   ",       Lower("   "));
      CHECK_EQUAL("abc",       Lower("abc"));
      CHECK_EQUAL("abc",       Lower("ABC"));
      CHECK_EQUAL("aabbcc",    Lower("aAbBcC"));
      CHECK_EQUAL("123456789", Lower("123456789"));
      CHECK_EQUAL("!$%&()=?*", Lower("!$%&()=?*"));
   }

   TEST (FilterFunctions)
   {
      CHECK_EQUAL("",     Letters(""));
      CHECK_EQUAL("",     Letters("   "));
      CHECK_EQUAL("",     Letters("123"));
      CHECK_EQUAL("abc",  Letters("abc"));
      CHECK_EQUAL("ABC",  Letters("ABC"));
      CHECK_EQUAL("",     Letters("!$?"));
      CHECK_EQUAL("",     Letters(" 1 2 3 "));
      CHECK_EQUAL("abc",  Letters(" a b c "));
      CHECK_EQUAL("ABC",  Letters(" A B C "));
      CHECK_EQUAL("",     Letters(" ! $ ? "));
      CHECK_EQUAL("aB",   Letters("a-1-B-2"));
      CHECK_EQUAL("Ba",   Letters("2-B-1-a"));

      CHECK_EQUAL("",     Digits(""));
      CHECK_EQUAL("",     Digits("   "));
      CHECK_EQUAL("123",  Digits("123"));
      CHECK_EQUAL("",     Digits("abc"));
      CHECK_EQUAL("",     Digits("ABC"));
      CHECK_EQUAL("",     Digits("!$?"));
      CHECK_EQUAL("123",  Digits(" 1 2 3 "));
      CHECK_EQUAL("",     Digits(" a b c "));
      CHECK_EQUAL("",     Digits(" A B C "));
      CHECK_EQUAL("",     Digits(" ! $ ? "));
      CHECK_EQUAL("12",   Digits("a-1-B-2"));
      CHECK_EQUAL("21",   Digits("2-B-1-a"));

      CHECK_EQUAL("",     LettersDigits(""));
      CHECK_EQUAL("",     LettersDigits("   "));
      CHECK_EQUAL("123",  LettersDigits("123"));
      CHECK_EQUAL("abc",  LettersDigits("abc"));
      CHECK_EQUAL("ABC",  LettersDigits("ABC"));
      CHECK_EQUAL("",     LettersDigits("!$?"));
      CHECK_EQUAL("123",  LettersDigits(" 1 2 3 "));
      CHECK_EQUAL("abc",  LettersDigits(" a b c "));
      CHECK_EQUAL("ABC",  LettersDigits(" A B C "));
      CHECK_EQUAL("",     LettersDigits(" ! $ ? "));
      CHECK_EQUAL("a1B2", LettersDigits("a-1-B-2"));
      CHECK_EQUAL("2B1a", LettersDigits("2-B-1-a"));
   }

   TEST (Replace)
   {
      CHECK_EQUAL("",    Replace("", "", ""));
      CHECK_EQUAL("   ", Replace("   ", "", ""));
      CHECK_EQUAL("",    Replace("   ", "   ", ""));
      CHECK_EQUAL("   ", Replace("   ", "", "   "));
      CHECK_EQUAL("   ", Replace("   ", "   ", "   "));
      CHECK_EQUAL("123", Replace("123", "", ""));
      CHECK_EQUAL("",    Replace("123", "123", ""));
      CHECK_EQUAL("1--", Replace("123", "23", "--"));
      CHECK_EQUAL("-2-", Replace("-+-", "+", "2"));
      CHECK_EQUAL("--3", Replace("123", "12", "--"));
      CHECK_EQUAL("ABC", Replace("123", "123", "ABC"));
   }

}

