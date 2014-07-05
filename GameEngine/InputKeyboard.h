
#pragma once

#include "EventListener.h"

#include "DLL_DEF.h"


namespace ge {

   class EventController;

   class GEDLL InputKeyboard : public EventListener
   {
   public:
      enum KeyType {
         Key_None  =  -2,
         Key_Any   =  -1,
         Key_Count = 256
      };

   private:
      std::array<bool, Key_Count> currKeys;
      std::array<bool, Key_Count> prevKeys;

      bool OnEvent (/*const sf::Event& event*/) override;

   public:
      InputKeyboard (EventController* eventCtrl);
      virtual ~InputKeyboard ();

      void Update () override;

      bool Key (int key = Key_Any);
      bool KeyPressed (int key = Key_Any);
      bool KeyReleased (int key = Key_Any);
   };

}

