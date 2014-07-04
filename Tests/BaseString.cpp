
#include "Precomp.h"

#include "../Base/String.h"

using namespace base;


SUITE (BaseString)
{

   TEST (TrimFunctions)
   {
      CHECK_EQUAL("",         LTrimCopy(""));
      CHECK_EQUAL("",         LTrimCopy("   "));
      CHECK_EQUAL("test",     LTrimCopy("test"));
      CHECK_EQUAL("test",     LTrimCopy("   test"));
      CHECK_EQUAL("test   ",  LTrimCopy("test   "));
      CHECK_EQUAL("test   ",  LTrimCopy("   test   "));
      CHECK_EQUAL("t e s t ", LTrimCopy(" t e s t "));

      CHECK_EQUAL("",         RTrimCopy(""));
      CHECK_EQUAL("",         RTrimCopy("   "));
      CHECK_EQUAL("test",     RTrimCopy("test"));
      CHECK_EQUAL("   test",  RTrimCopy("   test"));
      CHECK_EQUAL("test",     RTrimCopy("test   "));
      CHECK_EQUAL("   test",  RTrimCopy("   test   "));
      CHECK_EQUAL(" t e s t", RTrimCopy(" t e s t "));

      CHECK_EQUAL("",         TrimCopy(""));
      CHECK_EQUAL("",         TrimCopy("   "));
      CHECK_EQUAL("test",     TrimCopy("test"));
      CHECK_EQUAL("test",     TrimCopy("   test"));
      CHECK_EQUAL("test",     TrimCopy("test   "));
      CHECK_EQUAL("test",     TrimCopy("   test   "));
      CHECK_EQUAL("t e s t",  TrimCopy(" t e s t "));
   }

   TEST (FillFunctions)
   {
      CHECK_EQUAL("",        LFillCopy("", -1, ""));
      CHECK_EQUAL("",        LFillCopy("", 0, ""));
      CHECK_EQUAL("",        LFillCopy("", 1, ""));
      CHECK_EQUAL("",        LFillCopy("", -1, "+"));
      CHECK_EQUAL("",        LFillCopy("", 0, "+"));
      CHECK_EQUAL("+",       LFillCopy("", 1, "+"));
      CHECK_EQUAL("123",     LFillCopy("123", 3, "+"));
      CHECK_EQUAL("+++123",  LFillCopy("123", 6, "+"));
      CHECK_EQUAL("test123", LFillCopy("123", 7, "test"));
      CHECK_EQUAL("test1",   LFillCopy("123", 5, "test"));

      CHECK_EQUAL("",        RFillCopy("", -1, ""));
      CHECK_EQUAL("",        RFillCopy("", 0, ""));
      CHECK_EQUAL("",        RFillCopy("", 1, ""));
      CHECK_EQUAL("",        RFillCopy("", -1, "+"));
      CHECK_EQUAL("",        RFillCopy("", 0, "+"));
      CHECK_EQUAL("+",       RFillCopy("", 1, "+"));
      CHECK_EQUAL("123",     RFillCopy("123", 3, "+"));
      CHECK_EQUAL("123+++",  RFillCopy("123", 6, "+"));
      CHECK_EQUAL("123test", RFillCopy("123", 7, "test"));
      CHECK_EQUAL("123te",   RFillCopy("123", 5, "test"));
   }

   TEST (SubstringFunctions)
   {
      CHECK_EQUAL("",     LeftCopy("", -1));
      CHECK_EQUAL("",     LeftCopy("", 0));
      CHECK_EQUAL("",     LeftCopy("", 1));
      CHECK_EQUAL("",     LeftCopy("test", -1));
      CHECK_EQUAL("",     LeftCopy("test", 0));
      CHECK_EQUAL("te",   LeftCopy("test", 2));
      CHECK_EQUAL("test", LeftCopy("test", 4));
      CHECK_EQUAL("test", LeftCopy("test", 5));

      CHECK_EQUAL("",     RightCopy("", -1));
      CHECK_EQUAL("",     RightCopy("", 0));
      CHECK_EQUAL("",     RightCopy("", 1));
      CHECK_EQUAL("",     RightCopy("test", -1));
      CHECK_EQUAL("",     RightCopy("test", 0));
      CHECK_EQUAL("st",   RightCopy("test", 2));
      CHECK_EQUAL("test", RightCopy("test", 4));
      CHECK_EQUAL("test", RightCopy("test", 5));
   }

   TEST (CaseFunctions)
   {
      CHECK_EQUAL("",          UpperCopy(""));
      CHECK_EQUAL("   ",       UpperCopy("   "));
      CHECK_EQUAL("ABC",       UpperCopy("abc"));
      CHECK_EQUAL("ABC",       UpperCopy("ABC"));
      CHECK_EQUAL("AABBCC",    UpperCopy("aAbBcC"));
      CHECK_EQUAL("123456789", UpperCopy("123456789"));
      CHECK_EQUAL("!$%&()=?*", UpperCopy("!$%&()=?*"));

      CHECK_EQUAL("",          LowerCopy(""));
      CHECK_EQUAL("   ",       LowerCopy("   "));
      CHECK_EQUAL("abc",       LowerCopy("abc"));
      CHECK_EQUAL("abc",       LowerCopy("ABC"));
      CHECK_EQUAL("aabbcc",    LowerCopy("aAbBcC"));
      CHECK_EQUAL("123456789", LowerCopy("123456789"));
      CHECK_EQUAL("!$%&()=?*", LowerCopy("!$%&()=?*"));
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
      CHECK_EQUAL("",    ReplaceCopy("", "", ""));
      CHECK_EQUAL("   ", ReplaceCopy("   ", "", ""));
      CHECK_EQUAL("",    ReplaceCopy("   ", "   ", ""));
      CHECK_EQUAL("   ", ReplaceCopy("   ", "", "   "));
      CHECK_EQUAL("   ", ReplaceCopy("   ", "   ", "   "));
      CHECK_EQUAL("123", ReplaceCopy("123", "", ""));
      CHECK_EQUAL("",    ReplaceCopy("123", "123", ""));
      CHECK_EQUAL("1--", ReplaceCopy("123", "23", "--"));
      CHECK_EQUAL("-2-", ReplaceCopy("-+-", "+", "2"));
      CHECK_EQUAL("--3", ReplaceCopy("123", "12", "--"));
      CHECK_EQUAL("ABC", ReplaceCopy("123", "123", "ABC"));
   }

}

