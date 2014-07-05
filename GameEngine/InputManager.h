
#pragma once

#include "EventController.h"

#include "InputKeyboard.h"
#include "InputMouse.h"
#include "InputGamepad.h"

#include "DLL_DEF.h"


namespace ge {

   class GEDLL InputManager
   {
   public:
      enum What {
         NoInterface       = 0,
         KeyboardInterface = 1,
         MouseInterface    = 2,
         GamepadInterface  = 4,
         AllInterfaces     = 7
      };

   private:
      EventController* eventController;

      std::unique_ptr<InputKeyboard> keyboard;
      std::unique_ptr<InputMouse>    mouse;
      std::unique_ptr<InputGamepad>  gamepad;

   public:
      InputManager (EventController* eventCtrl);
      virtual ~InputManager ();

      void Update ();

      InputManager& Reset (const What& what);
      InputManager& ShutDown (const What& what);

      InputKeyboard* Keyboard () { if (keyboard == nullptr) Reset(KeyboardInterface); return keyboard.get(); }
      InputMouse* Mouse ()       { if (mouse == nullptr) Reset(MouseInterface); return mouse.get(); }
      InputGamepad* Gamepad ()   { if (gamepad == nullptr) Reset(GamepadInterface); return gamepad.get(); }
   };

}

