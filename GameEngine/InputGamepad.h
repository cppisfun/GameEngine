
#pragma once

#include "EventListener.h"

#include "DLL_DEF.h"


namespace ge {

   class EventController;

   class GEDLL InputGamepad : public EventListener
   {
      void Init (EventController* eventCtrl);

      void OnEvent (const irr::SEvent& event);

   public:
      InputGamepad (EventController* eventCtrl);
      virtual ~InputGamepad ();

      void Update ();
   };

}

