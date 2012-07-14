
#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

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
   HINSTANCE instanceHandle;
   HWND windowHandle;
   IDirectInput8* device;

   std::unique_ptr<InputKeyboard> keyboard;
   std::unique_ptr<InputMouse> mouse;
   std::unique_ptr<InputGamepad> gamepad;

   void Init (HINSTANCE inst, HWND wnd);

public:
   InputCore (HINSTANCE inst, HWND wnd);
   virtual ~InputCore ();

   void Update ();

   InputCore& Reset (const What& what);
   InputCore& ShutDown (const What& what);

   HINSTANCE InstanceHandle () const { return instanceHandle; }
   HWND WindowHandle () const        { return windowHandle; }

   InputKeyboard* Keyboard () { if (keyboard == nullptr) Reset(KeyboardInterface); return keyboard.get(); }
   InputMouse* Mouse ()       { if (mouse == nullptr) Reset(MouseInterface); return mouse.get(); }
   InputGamepad* Gamepad ()   { if (gamepad == nullptr) Reset(GamepadInterface); return gamepad.get(); }
};

