
#include "Precomp.h"

#include "InputMouse.h"
#include "EventController.h"

#include "../Base/Error.h"


namespace ge {

   InputMouse::InputMouse (EventController* eventCtrl)
   : currPosition(0, 0), prevPosition(0, 0), currWheelPosition(0), prevWheelPosition(0)
   {
      if (eventCtrl == nullptr) throw error::NullPointer("Invalid event controller pointer!", __FUNCTION__);
      eventCtrl->MouseCallback(std::bind(&InputMouse::OnEvent, this, std::placeholders::_1));

      std::fill(currButtons.begin(), currButtons.end(), false);
      std::fill(prevButtons.begin(), prevButtons.end(), false);
   }

   InputMouse::~InputMouse ()
   {
   }

   bool InputMouse::OnEvent (const sf::Event& event)
   {
      if (!Enabled()) return false;

      switch (event.type) {
         case sf::Event::MouseButtonPressed:  currButtons[event.mouseButton.button] = true;           return true;
         case sf::Event::MouseButtonReleased: currButtons[event.mouseButton.button] = false;          return true;
         case sf::Event::MouseMoved:          currPosition.Set(event.mouseMove.x, event.mouseMove.y); return true;
         case sf::Event::MouseWheelMoved:     currWheelPosition += event.mouseWheel.delta;            return true;
         // TODO: sf::Event::MouseEntered
         // TODO: sf::Event::MouseLeft
      }

      return false;
   }

   void InputMouse::Update ()
   {
      if (!Enabled()) return;

      std::move(currButtons.begin(), currButtons.end(), prevButtons.begin());
      prevPosition      = currPosition;
      prevWheelPosition = currWheelPosition;
   }

   bool InputMouse::Button (int btn)
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn >= 0) return currButtons[btn];

      for (int i = 0; i < Button_Count; ++i) {
         if (currButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputMouse::ButtonPressed (int btn)
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn >= 0) return (currButtons[btn] && !prevButtons[btn]);

      for (int i = 0; i < Button_Count; ++i) {
         if (currButtons[i] && !prevButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputMouse::ButtonReleased (int btn)
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn >= 0) return (!currButtons[btn] && prevButtons[btn]);

      for (int i = 0; i < Button_Count; ++i) {
         if (!currButtons[i] && prevButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputMouse::Moved (int direction)
   {
      if (direction == Direction_Any)             return (DX() != 0 || DY() != 0);
      else if (direction == Direction_None)       return (DX() == 0 && DY() == 0);
      else if (direction == Direction_Left)       return (DX() < 0);
      else if (direction == Direction_Right)      return (DX() > 0);
      else if (direction == Direction_Horizontal) return (DX() != 0);
      else if (direction == Direction_Up)         return (DY() < 0);
      else if (direction == Direction_Down)       return (DY() > 0);
      else if (direction == Direction_Vertical)   return (DY() != 0);
      else throw error::InvalidParam("Direction out of range!", __FUNCTION__);
   }

   bool InputMouse::WheelMoved (int direction)
   {
      if (direction == Direction_Any)           return (DWheel() != 0);
      else if (direction == Direction_None)     return (DWheel() == 0);
      else if (direction == Direction_Up)       return (DWheel() < 0);
      else if (direction == Direction_Down)     return (DWheel() > 0);
      else if (direction == Direction_Vertical) return (DWheel() != 0);
      else throw error::InvalidParam("Direction out of range!", __FUNCTION__);
   }

}


/*
   InputMouse& InputMouse::X (int x)
   {
      currX = x;
      prevX = x;

      cursor->setPosition(x, currY);
      return *this;
   }

   InputMouse& InputMouse::Y (int y)
   {
      currY = y;
      prevY = y;

      cursor->setPosition(currX, y);
      return *this;
   }

   InputMouse& InputMouse::Position (int x, int y)
   {
      currX = x;
      prevX = x;
      currY = y;
      prevY = y;

      cursor->setPosition(x, y);
      return *this;
   }
*/