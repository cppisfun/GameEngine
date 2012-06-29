
#pragma once

#include "DLL_DEF.h"


namespace base {

   BASEDLL float Fraction (float val);
   BASEDLL double Fraction (double val);

   BASEDLL const std::string LTrim (const std::string& val); // TODO: parameter for characters to be trimmed
   BASEDLL const std::string RTrim (const std::string& val);
   BASEDLL const std::string Trim (const std::string& val);

   BASEDLL const std::string LFill (const std::string& val, int length, const std::string& filling = " ");
   BASEDLL const std::string RFill (const std::string& val, int length, const std::string& filling = " ");

   BASEDLL const std::string Left (const std::string& val, int length);
   BASEDLL const std::string Right (const std::string& val, int length);

   BASEDLL const std::string Upper (const std::string& val);
   BASEDLL const std::string Lower (const std::string& val);

   BASEDLL const std::string Letters (const std::string& val); // TODO: parameter for exceptional characters
   BASEDLL const std::string Digits (const std::string& val);
   BASEDLL const std::string LettersDigits (const std::string& val);

   BASEDLL const std::string Replace (const std::string& src, const std::string& what, const std::string& with);

}

