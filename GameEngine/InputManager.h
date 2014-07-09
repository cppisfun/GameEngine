
#pragma once

#include "EventController.h"

#include "InputKeyboard.h"
#include "InputMouse.h"
#include "InputGamepad.h"

#include "DLL_DEF.h"

struct SDL_Window;


namespace ge {

   class GEDLL InputManager
   {
   public:
      enum InterfaceType {
         NoInterface       = 0,
         KeyboardInterface = 1,
         MouseInterface    = 2,
         GamepadInterface  = 4,
         AllInterfaces     = 7
      };

   private:
      EventController* eventController;
      SDL_Window*      window;

      std::unique_ptr<InputKeyboard> keyboard;
      std::unique_ptr<InputMouse>    mouse;
      std::unique_ptr<InputGamepad>  gamepad;

   public:
      InputManager (EventController* eventCtrl, SDL_Window* window);
      virtual ~InputManager ();

      void Update ();

      InputManager& Reset (InterfaceType what);
      InputManager& ShutDown (InterfaceType what);

      InputKeyboard* Keyboard () { if (keyboard == nullptr) Reset(KeyboardInterface); return keyboard.get(); }
      InputMouse* Mouse ()       { if (mouse == nullptr) Reset(MouseInterface); return mouse.get(); }
      InputGamepad* Gamepad ()   { if (gamepad == nullptr) Reset(GamepadInterface); return gamepad.get(); }
   };

}

