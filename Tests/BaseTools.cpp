
#include "Precomp.h"

#include "../Base/Tools.h"

using namespace base;


SUITE (BaseTools)
{

   TEST (ScopeGuard)
   {
      int test;

      {
         test = 1;
         ScopeGuard guard([&test] () { test = 0; });
      }

      CHECK_EQUAL(0, test);

      {
         test = 2;
         ScopeGuard guard([&test] () { test = 0; });
         guard.Clear();
      }

      CHECK_EQUAL(2, test);

      {
         test = 3;
         ScopeGuard guard([&test] () { test = 0; });
         guard.Release();

         CHECK_EQUAL(0, test);

         test = 3;
         guard.Releaser([&test] () { test = 0; });
      }

      CHECK_EQUAL(0, test);
   }

}

