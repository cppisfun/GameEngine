
#pragma once

#include "EventListener.h"

#include "DLL_DEF.h"

union SDL_Event;


namespace ge {

   class EventController;

   class GEDLL InputKeyboard : public EventListener
   {
   public:
      enum KeyType {
         Key_None  =  -2,
         Key_Any   =  -1,
         Key_Count = 512 // according to SDL
      };

   private:
      std::array<bool, Key_Count> currKeys;
      std::array<bool, Key_Count> prevKeys;

      bool OnEvent (const SDL_Event& event) override;

   public:
      InputKeyboard (EventController* eventCtrl);
      virtual ~InputKeyboard ();

      void Update () override;

      bool Key (int key = Key_Any) const;
      bool KeyPressed (int key = Key_Any) const;
      bool KeyReleased (int key = Key_Any) const;
   };

}

