
#include "Precomp.h"

#include "String.h"
#include "Error.h"


namespace base {

   void LTrim (std::string& val) { boost::trim_left(val); }
   void RTrim (std::string& val) { boost::trim_right(val); }
   void Trim (std::string& val)  { boost::trim(val); }
   void Upper (std::string& val) { boost::to_upper(val); }
   void Lower (std::string& val) { boost::to_lower(val); }

   void Replace (std::string& src, const std::string& what, const std::string& with) { boost::replace_all(src, what, with); }

   void Left (std::string& val, int length)
   {
      if (length <= 0) {
         val.clear();
         return;
      }

      size_t len(length);
      if (val.size() <= len) return;

      val = val.substr(0, len);
   }

   void Right (std::string& val, int length)
   {
      if (length <= 0) {
         val.clear();
         return;
      }

      size_t len(length);
      if (val.size() <= len) return;

      val = val.substr(val.size() - len, len);
   }

   void LFill (std::string& val, int length, const std::string& filling)
   {
      if (length <= 0 || filling.empty()) return;

      size_t len(length);
      if (len <= val.size()) return;

      while (val.size() < len) val = filling + val;
      val = val.substr(0, len);
   }

   void RFill (std::string& val, int length, const std::string& filling)
   {
      if (length <= 0 || filling.empty()) return;

      size_t len(length);
      if (len < val.size()) return;

      while (val.size() < len) val += filling;
      val = val.substr(0, len);
   }

   std::string LTrimCopy (const std::string& val) { return boost::trim_left_copy(val); }
   std::string RTrimCopy (const std::string& val) { return boost::trim_right_copy(val); }
   std::string TrimCopy (const std::string& val)  { return boost::trim_copy(val); }
   std::string UpperCopy (const std::string& val) { return boost::to_upper_copy(val); }
   std::string LowerCopy (const std::string& val) { return boost::to_lower_copy(val); }

   std::string ReplaceCopy (const std::string& src, const std::string& what, const std::string& with) { return boost::replace_all_copy(src, what, with); }

   std::string LeftCopy (const std::string& val, int length)
   {
      std::string ret(val);
      Left(ret, length);
      return ret;
   }

   std::string RightCopy (const std::string& val, int length)
   {
      std::string ret(val);
      Right(ret, length);
      return ret;
   }

   std::string LFillCopy (const std::string& val, int length, const std::string& filling)
   {
      std::string ret(val);
      LFill(ret, length, filling);
      return ret;
   }

   std::string RFillCopy (const std::string& val, int length, const std::string& filling)
   {
      std::string ret(val);
      RFill(ret, length, filling);
      return ret;
   }

   std::string Letters (const std::string& val)
   {
      if (val.empty()) return "";

      std::string ret;

      for (char ch : val) {
         if ((ch >= 'A' && ch <= 'Z') ||
             (ch >= 'a' && ch <= 'z') ||
             ch == 'Ä' || ch == 'Ö' || ch == 'Ü' ||
             ch == 'ä' || ch == 'ö' || ch == 'ü' ||
             ch == 'ß') ret += ch;
      }

      return ret;
   }

   std::string Digits (const std::string& val)
   {
      if (val.empty()) return "";

      std::string ret;
      for (char ch : val) if (ch >= '0' && ch <= '9') ret += ch;

      return ret;
   }

   std::string LettersDigits (const std::string& val)
   {
      if (val.empty()) return "";

      std::string ret;

      for (char ch : val) {
         if ((ch >= 'A' && ch <= 'Z') ||
             (ch >= 'a' && ch <= 'z') ||
             (ch >= '0' && ch <= '9') ||
             ch == 'Ä' || ch == 'Ö' || ch == 'Ü' ||
             ch == 'ä' || ch == 'ö' || ch == 'ü' ||
             ch == 'ß') ret += ch;
      }

      return ret;
   }

   std::vector<std::string> Split (const std::string& val, const std::string& seperator)
   {
      std::vector<std::string> ret;
      if (seperator.empty()) return ret;

      boost::split(ret, val, boost::is_any_of(seperator));
      return ret;
   }

   std::string Join (const std::vector<std::string>& vals, const std::string& seperator)
   {
      std::string ret;
      if (vals.empty()) return ret;

      boost::join(vals, seperator);
      return ret;
   }

}

