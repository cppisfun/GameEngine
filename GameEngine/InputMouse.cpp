
#include "Precomp.h"

#include <SDL.h>

#include "InputMouse.h"
#include "EventController.h"

#include "../Base/Error.h"


namespace ge {

   InputMouse::InputMouse (EventController* eventCtrl, SDL_Window* window)
   : window(window), currPosition(0, 0), prevPosition(0, 0), currWheelPosition(0), prevWheelPosition(0)
   {
      if (eventCtrl == nullptr) throw error::NullPointer("Invalid event controller pointer!", ERROR_LOCATION);
      eventCtrl->MouseCallback(std::bind(&InputMouse::OnEvent, this, std::placeholders::_1));

      std::fill(currButtons.begin(), currButtons.end(), false);
      std::fill(prevButtons.begin(), prevButtons.end(), false);
   }

   InputMouse::~InputMouse ()
   {
   }

   bool InputMouse::OnEvent (const SDL_Event& event)
   {
      if (!Enabled()) return false;

      switch (event.type) {
         case SDL_MOUSEBUTTONDOWN: currButtons[event.button.button - 1] = true;      return true;
         case SDL_MOUSEBUTTONUP:   currButtons[event.button.button - 1] = false;     return true;
         case SDL_MOUSEMOTION:     currPosition.Set(event.motion.x, event.motion.y); return true;
         case SDL_MOUSEWHEEL:      currWheelPosition += event.wheel.y;               return true;
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

   InputMouse& InputMouse::Position (const Point<int>& position)
   {
      currPosition = position;
      SDL_WarpMouseInWindow(window, position.X(), position.Y());

      return *this;
   }

   InputMouse& InputMouse::Show (bool show)
   {
      SDL_ShowCursor(show ? 1 : 0);
      return *this;
   }

   InputMouse& InputMouse::Hide ()
   {
      SDL_ShowCursor(0);
      return *this;
   }

   bool InputMouse::Moved (int direction) const
   {
      if      (direction == Direction_Any)        return DX() != 0 || DY() != 0;
      else if (direction == Direction_None)       return DX() == 0 && DY() == 0;
      else if (direction == Direction_Left)       return DX() < 0;
      else if (direction == Direction_Right)      return DX() > 0;
      else if (direction == Direction_Horizontal) return DX() != 0;
      else if (direction == Direction_Up)         return DY() < 0;
      else if (direction == Direction_Down)       return DY() > 0;
      else if (direction == Direction_Vertical)   return DY() != 0;
      else throw error::InvalidParam("Direction out of range!", ERROR_LOCATION);
   }

   bool InputMouse::WheelMoved (int direction) const
   {
      if      (direction == Direction_Any)      return DWheel() != 0;
      else if (direction == Direction_None)     return DWheel() == 0;
      else if (direction == Direction_Up)       return DWheel() < 0;
      else if (direction == Direction_Down)     return DWheel() > 0;
      else if (direction == Direction_Vertical) return DWheel() != 0;
      else throw error::InvalidParam("Direction out of range!", ERROR_LOCATION);
   }

   bool InputMouse::Button (int btn) const
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", ERROR_LOCATION);
      else if (btn >= 0) return currButtons[btn];

      for (int i = 0; i < Button_Count; ++i) {
         if (currButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputMouse::ButtonPressed (int btn) const
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", ERROR_LOCATION);
      else if (btn >= 0) return (currButtons[btn] && !prevButtons[btn]);

      for (int i = 0; i < Button_Count; ++i) {
         if (currButtons[i] && !prevButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputMouse::ButtonReleased (int btn) const
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", ERROR_LOCATION);
      else if (btn >= 0) return (!currButtons[btn] && prevButtons[btn]);

      for (int i = 0; i < Button_Count; ++i) {
         if (!currButtons[i] && prevButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputMouse::Visible () const
   {
      return SDL_ShowCursor(-1) == 1;
   }

}

