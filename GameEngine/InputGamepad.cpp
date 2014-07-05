
#include "Precomp.h"

#include "InputGamepad.h"
#include "EventController.h"

#include "../Base/Error.h"


namespace ge {

   InputGamepad::InputGamepad (EventController* eventCtrl)
   {
      if (eventCtrl ==  nullptr) throw error::NullPointer("Invalid event controller pointer!", ERROR_LOCATION);
      eventCtrl->GamepadCallback(std::bind(&InputGamepad::OnEvent, this));

      std::fill(currButtons.begin(), currButtons.end(), false);
      std::fill(prevButtons.begin(), prevButtons.end(), false);
   }

   InputGamepad::~InputGamepad ()
   {
   }

   bool InputGamepad::OnEvent (/*const sf::Event& event*/)
   {
      if (!Enabled()) return false;

//      switch (event.type) {
//         case sf::Event::JoystickButtonPressed:  currButtons[event.joystickButton.button] = true;  return true;
//         case sf::Event::JoystickButtonReleased: currButtons[event.joystickButton.button] = false; return true;
//         // TODO: sf::Event::JoyMoved
//      }

      return false;
   }

   void InputGamepad::Update ()
   {
      if (!Enabled()) return;
      std::copy(currButtons.begin(), currButtons.end(), prevButtons.begin());
   }

   bool InputGamepad::Button (int btn)
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", ERROR_LOCATION);
      else if (btn > 0) return currButtons[btn];

      for (int i = 0; i < Button_Count; ++i) {
         if (currButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputGamepad::ButtonPressed (int btn)
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", ERROR_LOCATION);
      else if (btn > 0) return (currButtons[btn] && !prevButtons[btn]);

      for (int i = 0; i < Button_Count; ++i) {
         if (currButtons[i] && !prevButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputGamepad::ButtonReleased (int btn)
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", ERROR_LOCATION);
      else if (btn > 0) return (!currButtons[btn] && prevButtons[btn]);

      for (int i = 0; i < Button_Count; ++i) {
         if (!currButtons[i] && prevButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

}

