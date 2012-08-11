
#pragma once

#include "Precomp.h"

#include <irrlicht.h>


class EventController : public irr::IEventReceiver
{
   std::function<void(const irr::SEvent&)> guiCallback;
   std::function<void(const irr::SEvent&)> mouseCallback;
   std::function<void(const irr::SEvent&)> keyboardCallback;
   std::function<void(const irr::SEvent&)> gamepadCallback;
   std::function<void(const irr::SEvent&)> customCallback;

   virtual bool OnEvent (const irr::SEvent& e) override
   {
      switch (e.EventType) {
         case irr::EET_GUI_EVENT:            if (guiCallback != nullptr) guiCallback(e);           return true;
         case irr::EET_MOUSE_INPUT_EVENT:    if (mouseCallback != nullptr) mouseCallback(e);       return true;
         case irr::EET_KEY_INPUT_EVENT:      if (keyboardCallback != nullptr) keyboardCallback(e); return true;
         case irr::EET_JOYSTICK_INPUT_EVENT: if (gamepadCallback != nullptr) gamepadCallback(e);   return true;
         case irr::EET_USER_EVENT:           if (customCallback != nullptr) customCallback(e);     return true;
      }

      return false;
   }

public:
   EventController ()  { }
   ~EventController () { }

   void GUICallback (const std::function<void(const irr::SEvent&)>& callback)      { guiCallback = callback; }
   void MouseCallback (const std::function<void(const irr::SEvent&)>& callback)    { mouseCallback = callback; }
   void KeyboardCallback (const std::function<void(const irr::SEvent&)>& callback) { keyboardCallback = callback; }
   void GamepadCallback (const std::function<void(const irr::SEvent&)>& callback)  { gamepadCallback = callback; }
   void CustomCallback (const std::function<void(const irr::SEvent&)>& callback)   { customCallback = callback; }

   void ResetGUICallback ()      { guiCallback = nullptr; }
   void ResetMouseCallback ()    { mouseCallback = nullptr; }
   void ResetKeyboardCallback () { keyboardCallback = nullptr; }
   void ResetGamepadCallback ()  { gamepadCallback = nullptr; }
   void ResetCustomCallback ()   { customCallback = nullptr; }
};
