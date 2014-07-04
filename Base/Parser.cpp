
#include "Precomp.h"

#include "Parser.h"
#include "String.h"
#include "Error.h"


namespace base {

   Parser::Parser (const std::string& source) : source(source), position(0)
   {
      textToParse = UpperCopy(source);
      Replace(textToParse, "\n", " ");
      Trim(textToParse);
   }

   void Parser::SkipSpaces () { while (position < textToParse.size() && textToParse[position] == ' ') ++position; }

   bool Parser::IsLetter (char ch) const { return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'); }
   bool Parser::IsDigit (char ch) const  { return ch >= '0' && ch <= '9'; }

   std::string Parser::NextWord ()
   {
      std::string word;
      SkipSpaces();

      while (position < textToParse.size() && (IsLetter(textToParse[position]) || IsDigit(textToParse[position]))) {
         word += source[position];
         ++position;
      }

      return word;
   }

   bool Parser::NextWordIs (const std::string& word)
   {
      if (word.empty()) throw error::InvalidParam("No word specified to be expected by parser!", ERROR_LOCATION);
      else if (std::any_of(word.begin(), word.end(), [] (char ch) {
         return ch == ' ' || ch == '\n';
      })) {
         throw error::InvalidParam("Characters ' ' and '\\n' cannot used for this parser due to internal use!", ERROR_LOCATION);
      }

      return UpperCopy(NextWord()) == UpperCopy(word);
   }

}

