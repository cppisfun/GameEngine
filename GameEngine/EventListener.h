
#pragma once

#include <IEventReceiver.h>

#include "DLL_DEF.h"


namespace ge {

   class GEDLL EventListener
   {
      bool enabled;

      virtual void OnEvent (const irr::SEvent& event) = 0;
      virtual void Update () = 0;

   public:
      EventListener () : enabled(true) { }
      virtual ~EventListener ()        { }

      void Enable (bool enable) { enabled = enable; }
      void Disable ()           { enabled = false; }

      bool Enabled () const { return enabled; }
   };

}

