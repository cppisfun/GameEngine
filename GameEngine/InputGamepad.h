
#pragma once

#include "EventListener.h"

#include "DLL_DEF.h"


namespace ge {

   class EventController;

   class GEDLL InputGamepad : public EventListener
   {
      static const int buttonCount = 32;
      static const int axisCount   = 6;

      std::array<bool, buttonCount> currButtons;
      std::array<bool, buttonCount> prevButtons;

      void Init (EventController* eventCtrl);

      void OnEvent (const irr::SEvent& event);

   public:
      InputGamepad (EventController* eventCtrl);
      virtual ~InputGamepad ();

      void Update ();

      bool Button (int btn = ANY);
      bool ButtonPressed (int btn = ANY);
      bool ButtonReleased (int btn = ANY);
   };

}

