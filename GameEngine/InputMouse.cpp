
#include "Precomp.h"

#include <OISInputManager.h>
#include <OISMouse.h>

#include "InputMouse.h"

#include "../Base/Error.h"


namespace ge {

   InputMouse::InputMouse (OIS::InputManager* inputManager)
   : input(nullptr), device(nullptr), currPosition(0, 0), prevPosition(0, 0), currWheelPosition(0), prevWheelPosition(0)
   {
      Init(inputManager);
   }

   InputMouse::~InputMouse ()
   {
      if (device != nullptr) {
         input->destroyInputObject(device);
         device = nullptr;
      }
   }

   void InputMouse::Init (OIS::InputManager* inputManager)
   {
      if (inputManager == nullptr) throw error::NullPointer("Invalid input manager pointer!", __FUNCTION__);
      input = inputManager;

      device =(OIS::Mouse*)input->createInputObject(OIS::OISMouse, true);
      if (device == nullptr) throw error::Create("Failed to create mouse device!", __FUNCTION__);

      std::fill(currButtons.begin(), currButtons.end(), false);
      std::fill(prevButtons.begin(), prevButtons.end(), false);
   }

   void InputMouse::Update ()
   {
      if (!Enabled()) return;

      std::move(currButtons.begin(), currButtons.end(), prevButtons.begin());
      device->capture();

      auto state = device->getMouseState();
      std::swap(currPosition, prevPosition);
      currPosition.Set(state.X.abs, state.Y.abs);
      prevWheelPosition = currWheelPosition;
      currWheelPosition = state.Z.abs;

      int  buttonState = state.buttons;
      for (int i = 0; i < Button_Count; ++i) { currButtons[i] = ((buttonState & (1L << i)) != 0); }
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
namespace ge {

   void InputMouse::Init (ICursorControl* cursorCtrl, EventController* eventCtrl)
   {
      std::fill(buttonClickStates.begin(), buttonClickStates.end(), Nothing);
   }

   void InputMouse::OnEvent (const SEvent& event)
   {
      if (!Enabled()) return;

      switch (event.MouseInput.Event) {
         case EMIE_LMOUSE_PRESSED_DOWN: currButtons[LEFT_BUTTON]         = true;                return;
         case EMIE_MMOUSE_PRESSED_DOWN: currButtons[MIDDLE_BUTTON]       = true;                return;
         case EMIE_RMOUSE_PRESSED_DOWN: currButtons[RIGHT_BUTTON]        = true;                return;
         case EMIE_LMOUSE_LEFT_UP:      currButtons[LEFT_BUTTON]         = false;               return;
         case EMIE_MMOUSE_LEFT_UP:      currButtons[MIDDLE_BUTTON]       = false;               return;
         case EMIE_RMOUSE_LEFT_UP:      currButtons[RIGHT_BUTTON]        = false;               return;
         case EMIE_LMOUSE_DOUBLE_CLICK: buttonClickStates[LEFT_BUTTON]   = ButtonDoubleClicked; return;
         case EMIE_MMOUSE_DOUBLE_CLICK: buttonClickStates[MIDDLE_BUTTON] = ButtonDoubleClicked; return;
         case EMIE_RMOUSE_DOUBLE_CLICK: buttonClickStates[RIGHT_BUTTON]  = ButtonDoubleClicked; return;
         case EMIE_LMOUSE_TRIPLE_CLICK: buttonClickStates[LEFT_BUTTON]   = ButtonTripleClicked; return;
         case EMIE_MMOUSE_TRIPLE_CLICK: buttonClickStates[MIDDLE_BUTTON] = ButtonTripleClicked; return;
         case EMIE_RMOUSE_TRIPLE_CLICK: buttonClickStates[RIGHT_BUTTON]  = ButtonTripleClicked; return;
      }
   }

   void InputMouse::Update ()
   {
      for (int i = 0; i < BUTTON_COUNT; ++i) {
         if (buttonClickStates[i] != ButtonWasPressed) {
            buttonClickStates[i] = Nothing;
         }

         if (ButtonPressed(i) && buttonClickStates[i] == Nothing) {
            buttonClickStates[i] = ButtonWasPressed;
         }
         else if (ButtonReleased(i) && buttonClickStates[i] == ButtonWasPressed) {
            buttonClickStates[i] = ButtonClicked;
         }
      }
   }

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

   bool InputMouse::Clicked (int btn)
   {
      if (btn < NONE || btn >= BUTTON_COUNT) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn >= 0) return (buttonClickStates[btn] == ButtonClicked);

      for (int i = 0; i < BUTTON_COUNT; ++i) {
         if (buttonClickStates[i] == ButtonClicked) return (btn == ANY);
      }

      return (btn == NONE);
   }

   bool InputMouse::DoubleClicked (int btn)
   {
      if (btn < NONE || btn >= BUTTON_COUNT) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn >= 0) return (buttonClickStates[btn] == ButtonDoubleClicked);

      for (int i = 0; i < BUTTON_COUNT; ++i) {
         if (buttonClickStates[i] == ButtonDoubleClicked) return (btn == ANY);
      }

      return (btn == NONE);
   }

   bool InputMouse::TripleClicked (int btn)
   {
      if (btn < NONE || btn >= BUTTON_COUNT) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
      else if (btn >= 0) return (buttonClickStates[btn] == ButtonTripleClicked);

      for (int i = 0; i < BUTTON_COUNT; ++i) {
         if (buttonClickStates[i] == ButtonTripleClicked) return (btn == ANY);
      }

      return (btn == NONE);
   }

}

*/