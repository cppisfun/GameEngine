
#pragma once

#include "DLL_DEF.h"


namespace base {

   BASEDLL bool AsBool (const std::string& val);
   BASEDLL bool AsBool (int val);
   BASEDLL bool AsBool (long val);
   BASEDLL bool AsBool (long long val);
   BASEDLL bool AsBool (size_t val);
   BASEDLL bool AsBool (float val);
   BASEDLL bool AsBool (double val);
   BASEDLL bool AsBool (const char* val);

   BASEDLL int AsInt (const std::string& val);
   BASEDLL int AsInt (bool val);
   BASEDLL int AsInt (long val);
   BASEDLL int AsInt (long long val);
   BASEDLL int AsInt (size_t val);
   BASEDLL int AsInt (float val);
   BASEDLL int AsInt (double val);
   BASEDLL int AsInt (const char* val);

   BASEDLL long AsLong (const std::string& val);
   BASEDLL long AsLong (bool val);
   BASEDLL long AsLong (int val);
   BASEDLL long AsLong (long long val);
   BASEDLL long AsLong (size_t val);
   BASEDLL long AsLong (float val);
   BASEDLL long AsLong (double val);
   BASEDLL long AsLong (const char* val);

   BASEDLL long long AsLongLong (const std::string& val);
   BASEDLL long long AsLongLong (bool val);
   BASEDLL long long AsLongLong (int val);
   BASEDLL long long AsLongLong (long val);
   BASEDLL long long AsLongLong (size_t val);
   BASEDLL long long AsLongLong (float val);
   BASEDLL long long AsLongLong (double val);
   BASEDLL long long AsLongLong (const char* val);

   BASEDLL size_t AsUnsignedInt (const std::string& val);
   BASEDLL size_t AsUnsignedInt (bool val);
   BASEDLL size_t AsUnsignedInt (int val);
   BASEDLL size_t AsUnsignedInt (long val);
   BASEDLL size_t AsUnsignedInt (long long val);
   BASEDLL size_t AsUnsignedInt (float val);
   BASEDLL size_t AsUnsignedInt (double val);
   BASEDLL size_t AsUnsignedInt (const char* val);

   BASEDLL double AsDouble (const std::string& val);
   BASEDLL double AsDouble (bool val);
   BASEDLL double AsDouble (int val);
   BASEDLL double AsDouble (long val);
   BASEDLL double AsDouble (long long val);
   BASEDLL double AsDouble (size_t val);
   BASEDLL double AsDouble (float val);
   BASEDLL double AsDouble (const char* val);

   BASEDLL float AsFloat (const std::string& val);
   BASEDLL float AsFloat (bool val);
   BASEDLL float AsFloat (int val);
   BASEDLL float AsFloat (long val);
   BASEDLL float AsFloat (long long val);
   BASEDLL float AsFloat (size_t val);
   BASEDLL float AsFloat (double val);
   BASEDLL float AsFloat (const char* val);

   BASEDLL std::string AsString (bool val);
   BASEDLL std::string AsString (int val, bool pretty = true);
   BASEDLL std::string AsString (long val, bool pretty = true);
   BASEDLL std::string AsString (long long val, bool pretty = true);
   BASEDLL std::string AsString (size_t, bool pretty = true);
   BASEDLL std::string AsString (float val, int decimals = 2, bool pretty = true);
   BASEDLL std::string AsString (double val, int decimals = 2, bool pretty = true);

   BASEDLL std::string AsString (const Binary& val);
   BASEDLL Binary AsBinary (const std::string& val);
   BASEDLL std::wstring AsWString (const std::string& val);
}

