
#include "Precomp.h"

#include "InputGamepad.h"
#include "EventController.h"

#include "../Base/Error.h"

using namespace irr;


namespace ge {

   InputGamepad::InputGamepad (EventController* eventCtrl)
   {
      Init(eventCtrl);
   }

   InputGamepad::~InputGamepad ()
   {
   }

   void InputGamepad::Init (EventController* eventCtrl)
   {
      if (eventCtrl == nullptr) throw error::NullPointer("Invalid event controller pointer!", __FUNCTION__);
      eventCtrl->GamepadCallback(std::bind(&InputGamepad::OnEvent, this, std::placeholders::_1));

      std::fill(currButtons.begin(), currButtons.end(), false);
      std::fill(prevButtons.begin(), prevButtons.end(), false);
   }

   void InputGamepad::OnEvent (const SEvent& event)
   {
      if (!Enabled()) return;

      for (int i = 0; i < buttonCount; ++i) {
         currButtons[i] = event.JoystickEvent.IsButtonPressed(i);
      }
   }

   void InputGamepad::Update ()
   {
      if (!Enabled()) return;

      std::copy(currButtons.begin(), currButtons.end(), prevButtons.begin());
   }

   bool InputGamepad::Button (int btn)
   {
      if (btn < NONE || btn >= buttonCount) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn > 0) return currButtons[btn];

      for (int i = 0; i < buttonCount; ++i) {
         if (currButtons[i]) return (btn == ANY);
      }

      return (btn == NONE);
   }

   bool InputGamepad::ButtonPressed (int btn)
   {
      if (btn < NONE || btn >= buttonCount) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn > 0) return (currButtons[btn] && !prevButtons[btn]);

      for (int i = 0; i < buttonCount; ++i) {
         if (currButtons[i] && !prevButtons[i]) return (btn == ANY);
      }

      return (btn == NONE);
   }

   bool InputGamepad::ButtonReleased (int btn)
   {
      if (btn < NONE || btn >= buttonCount) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn > 0) return (!currButtons[btn] && prevButtons[btn]);

      for (int i = 0; i < buttonCount; ++i) {
         if (!currButtons[i] && prevButtons[i]) return (btn == ANY);
      }

      return (btn == NONE);
   }

}

