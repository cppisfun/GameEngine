
#pragma once

#include "DLL_DEF.h"


namespace base {

   BASEDLL void LTrim (std::string& val);
   BASEDLL void RTrim (std::string& val);
   BASEDLL void Trim (std::string& val);
   BASEDLL void Upper (std::string& val);
   BASEDLL void Lower (std::string& val);
   BASEDLL void Replace (std::string& src, const std::string& what, const std::string& with);
   BASEDLL void Left (std::string& val, int length);
   BASEDLL void Right (std::string& val, int length);
   BASEDLL void LFill (std::string& val, int length, const std::string& filling = " ");
   BASEDLL void RFill (std::string& val, int length, const std::string& filling = " ");

   BASEDLL std::string LTrimCopy (const std::string& val);
   BASEDLL std::string RTrimCopy (const std::string& val);
   BASEDLL std::string TrimCopy (const std::string& val);
   BASEDLL std::string UpperCopy (const std::string& val);
   BASEDLL std::string LowerCopy (const std::string& val);
   BASEDLL std::string ReplaceCopy (const std::string& src, const std::string& what, const std::string& with);
   BASEDLL std::string LeftCopy (const std::string& val, int length);
   BASEDLL std::string RightCopy (const std::string& val, int length);
   BASEDLL std::string LFillCopy (const std::string& val, int length, const std::string& filling = " ");
   BASEDLL std::string RFillCopy (const std::string& val, int length, const std::string& filling = " ");

   BASEDLL std::string Letters (const std::string& val);
   BASEDLL std::string Digits (const std::string& val);
   BASEDLL std::string LettersDigits (const std::string& val);

   BASEDLL std::vector<std::string> Split (const std::string& val, const std::string& seperator = "\n");
   BASEDLL std::string Join (const std::vector<std::string>& vals, const std::string& seperator = "\n");

}

