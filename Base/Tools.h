
#pragma once

#include "Precomp.h"

#include "DLL_DEF.h"


namespace Base {

   class ScopeGuard
   {
      std::function<void()> releaser;

   public:
      ScopeGuard (const std::function<void()>& releaser) : releaser(releaser) { }
      ~ScopeGuard () { if (releaser != nullptr) releaser(); }

      void Releaser (const std::function<void()>& val) { releaser = val; }
      void Clear ()                                    { releaser = nullptr; }
   };

}

