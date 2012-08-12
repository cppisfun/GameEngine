
#pragma once


#include <irrlicht.h>

#include "EventController.h"

#include "InputKeyboard.h"
#include "InputMouse.h"
#include "InputGamepad.h"

#include "DLL_DEF.h"


class GEDLL InputCore
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
   irr::IrrlichtDevice* device;
   EventController* eventController;

   std::unique_ptr<InputKeyboard> keyboard;
   std::unique_ptr<InputMouse>    mouse;
   std::unique_ptr<InputGamepad>  gamepad;

   void Init (irr::IrrlichtDevice* irrDevice, EventController* eventCtrl);

public:
   InputCore (irr::IrrlichtDevice* irrDevice, EventController* eventCtrl);
   virtual ~InputCore ();

   void Update ();

   InputCore& Reset (const What& what);
   InputCore& ShutDown (const What& what);

   InputKeyboard* Keyboard () { if (keyboard == nullptr) Reset(KeyboardInterface); return keyboard.get(); }
   InputMouse* Mouse ()       { if (mouse == nullptr) Reset(MouseInterface); return mouse.get(); }
   InputGamepad* Gamepad ()   { if (gamepad == nullptr) Reset(GamepadInterface); return gamepad.get(); }
};

