
#pragma once

#include "DLL_DEF.h"

union SDL_Event;


namespace ge {

   class GEDLL EventListener
   {
      bool enabled;

      virtual bool OnEvent (const SDL_Event& event) = 0;
      virtual void Update ()                        = 0;

   public:
      EventListener () : enabled(true) { }

      void Enable (bool enable = true) { enabled = enable; }
      void Disable ()                  { enabled = false; }
      bool Enabled () const            { return enabled; }
   };

}

