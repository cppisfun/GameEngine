
#include "Precomp.h"

#include "../Base/Parser.h"

using namespace base;


SUITE (BaseParser)
{

   TEST (Parser)
   {
      Parser parser("HaLlO Welt!");
      CHECK_EQUAL(true, parser.NextWordIs("hAlLo"));
      CHECK_EQUAL(true, parser.NextWordIs("WELT"));
   }

}

