
#include "Precomp.h"

#include "Misc.h"
#include "Error.h"


namespace base {

   float Fraction (float val)   { return std::abs(val - boost::numeric_cast<float>(boost::numeric_cast<int>(val))); }
   double Fraction (double val) { return std::abs(val - boost::numeric_cast<double>(boost::numeric_cast<int>(val))); }

   const std::string LTrim (const std::string& val)
   {
      if (val.empty()) return "";

      std::string ret(val);
      while (!ret.empty() && ret[0] == ' ') ret.erase(ret.begin());

      return ret;
   }

   const std::string RTrim (const std::string& val)
   {
      if (val.empty()) return "";

      std::string ret(val);
      while (!ret.empty() && ret[ret.size() - 1] == ' ') ret.erase(ret.end() - 1);

      return ret;
   }

   const std::string Trim (const std::string& val)
   {
      return RTrim(LTrim(val));
   }

   const std::string LFill (const std::string& val, int length, const std::string& filling)
   {
      size_t len(length);
      if (len <= val.size()) return val;

      std::string ret(val);
      while (ret.size() < len) ret = filling + ret;

      return ret.substr(0, len);
   }

   const std::string RFill (const std::string& val, int length, const std::string& filling)
   {
      size_t len(length);
      if (len < val.size()) return val;

      std::string ret(val);
      while (ret.size() < len) ret += filling;

      return ret.substr(0, len);
   }

   const std::string Left (const std::string& val, int length)
   {
      if (length <= 0) return "";

      size_t len(length);
      if (val.size() <= len) return val;

      return val.substr(0, len);
   }

   const std::string Right (const std::string& val, int length)
   {
      if (length <= 0) return "";

      size_t len(length);
      if (val.size() <= len) return val;

      return val.substr(val.size() - len, len);
   }

   const std::string Upper (const std::string& val)
   {
      if (val.empty()) return "";

      std::string ret(val);

      for (size_t i = 0; i < ret.size(); ++i) {
         if (ret[i] >= 'a' && ret[i] <= 'z') ret[i] -= 32;
         else if (ret[i] == 'ä')             ret[i] = 'Ä';
         else if (ret[i] == 'ö')             ret[i] = 'Ö';
         else if (ret[i] == 'ü')             ret[i] = 'Ü';
      }

      return ret;
   }

   const std::string Lower (const std::string& val)
   {
      if (val.empty()) return "";

      std::string ret(val);

      for (size_t i = 0; i < ret.size(); ++i) {
         if (ret[i] >= 'A' && ret[i] <= 'Z') ret[i] += 32;
         else if (ret[i] == 'Ä')             ret[i] = 'ä';
         else if (ret[i] == 'Ö')             ret[i] = 'ö';
         else if (ret[i] == 'Ü')             ret[i] = 'ü';
      }

      return ret;
   }

   const std::string Letters (const std::string& val)
   {
      if (val.empty()) return "";

      std::string ret;

      std::for_each(val.begin(), val.end(), [&ret] (const char& ch) {
         if ((ch >= 'A' && ch <= 'Z') ||
             (ch >= 'a' && ch <= 'z') ||
             ch == 'Ä' || ch == 'Ö' || ch == 'Ü' ||
             ch == 'ä' || ch == 'ö' || ch == 'ü' ||
             ch == 'ß') ret += ch;
      });

      return ret;
   }

   const std::string Digits (const std::string& val)
   {
      if (val.empty()) return "";

      std::string ret;

      std::for_each(val.begin(), val.end(), [&ret] (const char& ch) {
         if (ch >= '0' && ch <= '9') ret += ch;
      });

      return ret;
   }

   const std::string LettersDigits (const std::string& val)
   {
      if (val.empty()) return "";

      std::string ret;

      std::for_each(val.begin(), val.end(), [&ret] (const char& ch) {
         if ((ch >= 'A' && ch <= 'Z') ||
             (ch >= 'a' && ch <= 'z') ||
             (ch >= '0' && ch <= '9') ||
             ch == 'Ä' || ch == 'Ö' || ch == 'Ü' ||
             ch == 'ä' || ch == 'ö' || ch == 'ü' ||
             ch == 'ß') ret += ch;
      });

      return ret;
   }

   const std::string Replace (const std::string& src, const std::string& what, const std::string& with)
   {
      if (src.empty()) return "";
      else if (what.empty()) throw error::InvalidParam("No search string specified for replacement!", __FUNCTION__);

      std::string ret(src);
      size_t pos = ret.find(what);

      while (pos != std::string::npos) {
         ret.replace(pos, what.size(), with);
         pos = ret.find(what);
      }

      return ret;
   }

}

