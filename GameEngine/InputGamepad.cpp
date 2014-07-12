
#include "Precomp.h"

#include <SDL.h>

#include "InputGamepad.h"
#include "EventController.h"

#include "../Base/Error.h"


namespace ge {

   InputGamepad::InputGamepad (EventController* eventCtrl)
   : prevLeftStick(0, 0), currLeftStick(0, 0), prevRightStick(0, 0), currRightStick(0, 0)
   {
      // FIXME: implement proper detection (support more than one controller?)
      if (SDL_NumJoysticks() == 0) throw error::NotFound("No gamepad found on the system!", ERROR_LOCATION);

      device = SDL_JoystickOpen(0);
      if (device == nullptr) throw error::NullPointer("Failed to open gamepad device handle!", ERROR_LOCATION);

      if (eventCtrl ==  nullptr) throw error::NullPointer("Invalid event controller pointer!", ERROR_LOCATION);
      eventCtrl->GamepadCallback(std::bind(&InputGamepad::OnEvent, this, std::placeholders::_1));

      std::fill(currButtons.begin(), currButtons.end(), false);
      std::fill(prevButtons.begin(), prevButtons.end(), false);
   }

   InputGamepad::~InputGamepad ()
   {
      if (device == nullptr) {
         if (SDL_JoystickGetAttached(device) == SDL_TRUE) SDL_JoystickClose(device);
         device = nullptr;
      }
   }

   bool InputGamepad::OnEvent (const SDL_Event& event)
   {
      if (!Enabled()) return false;

      switch (event.type) {
         case SDL_JOYAXISMOTION:
            if (event.jaxis.which == 0) { // TODO: support more than one controller?
               if      (event.jaxis.axis == 0) currLeftStick.X(event.jaxis.value);
               else if (event.jaxis.axis == 1) currLeftStick.Y(event.jaxis.value);
               else if (event.jaxis.axis == 3) currRightStick.X(event.jaxis.value);
               else if (event.jaxis.axis == 4) currRightStick.Y(event.jaxis.value);
            }
            return true;

         case SDL_JOYBUTTONDOWN:
            if (event.jbutton.which == 0) currButtons[event.jbutton.button] = true;
            return true;

         case SDL_JOYBUTTONUP:
            if (event.jbutton.which == 0) currButtons[event.jbutton.button] = false;
            return true;
      }

      return false;
   }

   void InputGamepad::Update ()
   {
      if (!Enabled()) return;

      prevLeftStick  = currLeftStick;
      prevRightStick = currRightStick;

      std::copy(currButtons.begin(), currButtons.end(), prevButtons.begin());
   }

   bool InputGamepad::LeftStickMoved (int direction) const
   {
      switch (direction) {
         case Direction_Any:        return LeftStickDX() != 0 || LeftStickDY() != 0;
         case Direction_None:       return LeftStickDX() == 0 && LeftStickDY() == 0;
         case Direction_Left:       return LeftStickDX() < 0;
         case Direction_Right:      return LeftStickDX() > 0;
         case Direction_Horizontal: return LeftStickDX() != 0;
         case Direction_Up:         return LeftStickDY() < 0;
         case Direction_Down:       return LeftStickDY() > 0;
         case Direction_Vertical:   return LeftStickDY() != 0;
         default: throw error::InvalidParam("Direction out of range!", ERROR_LOCATION);
      }
   }

   bool InputGamepad::RightStickMoved (int direction) const
   {
      switch (direction) {
         case Direction_Any:        return RightStickDX() != 0 || RightStickDY() != 0;
         case Direction_None:       return RightStickDX() == 0 && RightStickDY() == 0;
         case Direction_Left:       return RightStickDX() < 0;
         case Direction_Right:      return RightStickDX() > 0;
         case Direction_Horizontal: return RightStickDX() != 0;
         case Direction_Up:         return RightStickDY() < 0;
         case Direction_Down:       return RightStickDY() > 0;
         case Direction_Vertical:   return RightStickDY() != 0;
         default: throw error::InvalidParam("Direction out of range!", ERROR_LOCATION);
      }
   }

   bool InputGamepad::Button (int btn) const
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", ERROR_LOCATION);
      else if (btn > 0) return currButtons[btn];

      for (int i = 0; i < Button_Count; ++i) {
         if (currButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputGamepad::ButtonPressed (int btn) const
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", ERROR_LOCATION);
      else if (btn > 0) return (currButtons[btn] && !prevButtons[btn]);

      for (int i = 0; i < Button_Count; ++i) {
         if (currButtons[i] && !prevButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

   bool InputGamepad::ButtonReleased (int btn) const
   {
      if (btn < Button_None || btn >= Button_Count) throw error::InvalidParam("Button id out of range!", ERROR_LOCATION);
      else if (btn > 0) return (!currButtons[btn] && prevButtons[btn]);

      for (int i = 0; i < Button_Count; ++i) {
         if (!currButtons[i] && prevButtons[i]) return (btn == Button_Any);
      }

      return (btn == Button_None);
   }

}

