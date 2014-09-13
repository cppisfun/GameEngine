
#include "Precomp.h"

#include "Convert.h"
#include "String.h"
#include "Numeric.h"
#include "Error.h"

#include "Constants.h"


namespace base {

   bool AsBool (int val)         { return (val != 0); }
   bool AsBool (long val)        { return (val != 0L); }
   bool AsBool (long long val)   { return (val != 0LL); }
   bool AsBool (float val)       { return (val != 0.0f); }
   bool AsBool (double val)      { return (val != 0.0); }
   bool AsBool (const char* val) { return AsBool(std::string(val)); }

   int AsInt (bool val)        { return (val) ? 1 : 0; }
   int AsInt (long val)        { return boost::numeric_cast<int>(val); }
   int AsInt (long long val)   { return boost::numeric_cast<int>(val); }
   int AsInt (float val)       { return boost::numeric_cast<int>(val); }
   int AsInt (double val)      { return boost::numeric_cast<int>(val); }
   int AsInt (const char* val) { return AsInt(std::string(val)); }

   long AsLong (bool val)        { return (val) ? 1L : 0L; }
   long AsLong (int val)         { return boost::numeric_cast<long>(val); }
   long AsLong (long long val)   { return boost::numeric_cast<long>(val); }
   long AsLong (float val)       { return boost::numeric_cast<long>(val); }
   long AsLong (double val)      { return boost::numeric_cast<long>(val); }
   long AsLong (const char* val) { return AsLong(std::string(val)); }

   long long AsLongLong (bool val)        { return (val) ? 1LL : 0LL; }
   long long AsLongLong (int val)         { return boost::numeric_cast<long long>(val); }
   long long AsLongLong (long val)        { return boost::numeric_cast<long long>(val); }
   long long AsLongLong (float val)       { return boost::numeric_cast<long long>(val); }
   long long AsLongLong (double val)      { return boost::numeric_cast<long long>(val); }
   long long AsLongLong (const char* val) { return AsLongLong(std::string(val)); }

   double AsDouble (bool val)        { return (val) ? 1.0 : 0.0; }
   double AsDouble (int val)         { return boost::numeric_cast<double>(val); }
   double AsDouble (long val)        { return boost::numeric_cast<double>(val); }
   double AsDouble (long long val)   { return boost::numeric_cast<double>(val); }
   double AsDouble (float val)       { return boost::numeric_cast<double>(val); }
   double AsDouble (const char* val) { return AsDouble(std::string(val)); }

   float AsFloat (const std::string& val) { return static_cast<float>(AsDouble(val)); }
   float AsFloat (bool val)               { return (val) ? 1.0f : 0.0f; }
   float AsFloat (int val)                { return boost::numeric_cast<float>(val); }
   float AsFloat (long val)               { return boost::numeric_cast<float>(val); }
   float AsFloat (long long val)          { return boost::numeric_cast<float>(val); }
   float AsFloat (double val)             { return boost::numeric_cast<float>(val); }
   float AsFloat (const char* val)        { return AsFloat(std::string(val)); }

   const std::string AsString (bool val) { return (val) ? "True" : "False"; }

   bool AsBool (const std::string& val)
   {
      if (val.empty()) return false;

      const std::string tester(UpperCopy(val));
      const auto& checklist = constants::checkBool;

      return std::any_of(checklist.begin(), checklist.end(), [&tester] (const std::string& check) { return (tester == check); });
   }

   int AsInt (const std::string& val)
   {
      if (val.empty()) return 0;

      size_t pos = 0;
      while (pos < val.size() && ((val[pos] >= '0' && val[pos] <= '9') || (pos == 0 && val[pos] == '-'))) ++pos;

      if (pos == 0 || (pos == 1 && val[0] == '-')) return 0;
      return boost::lexical_cast<int>(val.substr(0, pos));
   }

   long AsLong (const std::string& val)
   {
      if (val.empty()) return 0L;

      size_t pos = 0;
      while (pos < val.size() && ((val[pos] >= '0' && val[pos] <= '9') || (pos == 0 && val[pos] == '-'))) ++pos;

      if (pos == 0 || (pos == 1 && val[0] == '-')) return 0L;
      return boost::lexical_cast<long>(val.substr(0, pos));
   }

   long long AsLongLong (const std::string& val)
   {
      if (val.empty()) return 0LL;

      size_t pos = 0;
      while (pos < val.size() && ((val[pos] >= '0' && val[pos] <= '9') || (pos == 0 && val[pos] == '-'))) ++pos;

      if (pos == 0 || (pos == 1 && val[0] == '-')) return 0LL;
      return boost::lexical_cast<long long>(val.substr(0, pos));
   }

   double AsDouble (const std::string& val)
   {
      if (val.empty()) return 0.0;

      size_t pos    = 0;
      bool foundDot = false;

      while (pos < val.size() && ((val[pos] >= '0' && val[pos] <= '9') || (pos == 0 && val[pos] == '-') || (pos > 0 && !foundDot && val[pos] == '.'))) {
         if (val[pos] == '.') foundDot = true;
         ++pos;
      }

      if (pos == 0 || (pos == 1 && val[0] == '-')) return 0.0f;

      std::string prefix((val[0] == '.') ? "0" : "");
      std::string suffix((val[pos] == '.') ? "0" : "");

      return boost::lexical_cast<double>(prefix + val.substr(0, pos) + suffix);
   }

   const std::string AsString (int val, bool pretty)
   {
      bool negative = (val < 0);
      if (negative) val = -val;

      std::string ret(boost::lexical_cast<std::string>(val));

      if (pretty) {
         if (val >= 1000)       ret = ret.substr(0, ret.size() -  3) + "." + ret.substr(ret.size() - 3);
         if (val >= 1000000)    ret = ret.substr(0, ret.size() -  7) + "." + ret.substr(ret.size() - 7);
         if (val >= 1000000000) ret = ret.substr(0, ret.size() - 11) + "." + ret.substr(ret.size() - 11);
      }

      if (negative) ret = "-" + ret;
      return ret;
   }

   const std::string AsString (long val, bool pretty)
   {
      bool negative = (val < 0L);
      if (negative) val = -val;

      std::string ret(boost::lexical_cast<std::string>(val));

      if (pretty) {
         if (val >= 1000L)       ret = ret.substr(0, ret.size() -  3) + "." + ret.substr(ret.size() - 3);
         if (val >= 1000000L)    ret = ret.substr(0, ret.size() -  7) + "." + ret.substr(ret.size() - 7);
         if (val >= 1000000000L) ret = ret.substr(0, ret.size() - 11) + "." + ret.substr(ret.size() - 11);
      }

      if (negative) ret = "-" + ret;
      return ret;
   }

   const std::string AsString (long long val, bool pretty)
   {
      bool negative = (val < 0LL);
      if (negative) val = -val;

      std::string ret(boost::lexical_cast<std::string>(val));

      if (pretty) {
         if (val >= 1000LL)                ret = ret.substr(0, ret.size() -  3) + "." + ret.substr(ret.size() - 3);
         if (val >= 1000000LL)             ret = ret.substr(0, ret.size() -  7) + "." + ret.substr(ret.size() - 7);
         if (val >= 1000000000LL)          ret = ret.substr(0, ret.size() - 11) + "." + ret.substr(ret.size() - 11);
         if (val >= 1000000000000LL)       ret = ret.substr(0, ret.size() - 15) + "." + ret.substr(ret.size() - 15);
         if (val >= 1000000000000000LL)    ret = ret.substr(0, ret.size() - 19) + "." + ret.substr(ret.size() - 19);
         if (val >= 1000000000000000000LL) ret = ret.substr(0, ret.size() - 23) + "." + ret.substr(ret.size() - 23);
      }

      if (negative) ret = "-" + ret;
      return ret;
   }

   const std::string AsString (float val, int decimals, bool pretty)
   {
      std::string ret(AsString(boost::numeric_cast<int>(val), pretty));
      ret += (pretty) ? "," : ".";
      ret += RFillCopy(AsString(boost::numeric_cast<int>(Fraction(val) * std::pow(10.0f, boost::numeric_cast<float>(decimals))), false), decimals, "0");

      return ret;
   }

   const std::string AsString (double val, int decimals, bool pretty)
   {
      std::string ret(AsString(boost::numeric_cast<int>(val), pretty));
      ret += (pretty) ? "," : ".";
      ret += RFillCopy(AsString(boost::numeric_cast<int>(Fraction(val) * std::pow(10.0, boost::numeric_cast<double>(decimals))), false), decimals, "0");

      return ret;
   }

   const std::string AsString (const Binary& val)
   {
      return std::string(val.begin(), val.end());
   }

   const Binary AsBinary (const std::string& val)
   {
      return Binary(val.begin(), val.end());
   }

   const std::wstring AsWString (const std::string& val)
   {
      std::wstring ret;
      for (char ch : val) ret += static_cast<wchar_t>(ch);

      return ret;
   }

}

