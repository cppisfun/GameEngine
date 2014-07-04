
#pragma once

#include "DLL_DEF.h"


namespace base {

   class BASEDLL Parser
   {
      std::string source;
      std::string textToParse;
      size_t      position;

      void SkipSpaces ();

      bool IsLetter (char ch) const;
      bool IsDigit (char ch) const;

   public:
      Parser (const std::string& source);

      std::string NextWord ();
      bool NextWordIs (const std::string& word);

      const std::string& Source () const { return source; }
   };

}

