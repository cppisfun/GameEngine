
#pragma once

#include "Precomp.h"

#include "DLL_DEF.h"


namespace base {

   class BASEDLL ScopeGuard
   {
      std::function<void()> releaser;

   public:
      ScopeGuard (const std::function<void()>& releaser) : releaser(releaser) { }
      ~ScopeGuard () { Release(); }

      void Releaser (const std::function<void()>& val) { releaser = val; }
      void Release ()                                  { if (releaser != nullptr) releaser(); Clear(); }
      void Clear ()                                    { releaser = nullptr; }
   };

}

