
#pragma once

#include "EventListener.h"

#include "DLL_DEF.h"

union SDL_Event;


namespace ge {

   class EventController;

   class GEDLL InputGamepad : public EventListener
   {
   public:
      enum ButtonType {
         Button_None  = -2,
         Button_Any   = -1,
         Button_Count = 8
      };

   private:
      std::array<bool, Button_Count> currButtons;
      std::array<bool, Button_Count> prevButtons;

      bool OnEvent (const SDL_Event& event) override;

   public:
      InputGamepad (EventController* eventCtrl);
      virtual ~InputGamepad ();

      void Update () override;

      bool Button (int btn = Button_Any);
      bool ButtonPressed (int btn = Button_Any);
      bool ButtonReleased (int btn = Button_Any);
   };

}

