
#include "Precomp.h"

#include <SFML/Window/Event.hpp>

#include "InputGamepad.h"
#include "EventController.h"

#include "../Base/Error.h"


namespace ge {

   InputGamepad::InputGamepad (EventController* eventCtrl)
   {
      if (eventCtrl ==  nullptr) throw error::NullPointer("Invalid event controller pointer!", __FUNCTION__);
      eventCtrl->GamepadCallback(std::bind(&InputGamepad::OnEvent, this, std::placeholders::_1));

      std::fill(currButtons.begin(), currButtons.end(), false);
      std::fill(prevButtons.begin(), prevButtons.end(), false);
   }

   InputGamepad::~InputGamepad ()
   {
   }

   bool InputGamepad::OnEvent (const sf::Event& event)
   {
      if (!Enabled()) return false;

      switch (event.Type) {
         case sf::Event::JoyButtonPressed:  currButtons[event.JoyButton.Button] = true;  return true;
         case sf::Event::JoyButtonReleased: currButtons[event.JoyButton.Button] = false; return true;
         // TODO: sf::Event::JoyMoved
      }

      return false;
   }

   void InputGamepad::Update ()
   {
      if (!Enabled()) return;
      std::copy(currButtons.begin(), currButtons.end(), prevButtons.begin());
   }

   bool InputGamepad::Button (int btn)
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn > 0) return currButtons[btn];

      for (int i = 0; i < Button_Count; ++i) {
         if (currButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputGamepad::ButtonPressed (int btn)
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn > 0) return (currButtons[btn] && !prevButtons[btn]);

      for (int i = 0; i < Button_Count; ++i) {
         if (currButtons[i] && !prevButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputGamepad::ButtonReleased (int btn)
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn > 0) return (!currButtons[btn] && prevButtons[btn]);

      for (int i = 0; i < Button_Count; ++i) {
         if (!currButtons[i] && prevButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

}

