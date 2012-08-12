
#include "Precomp.h"

#include <irrlicht.h>

#include "InputMouse.h"
#include "EventController.h"

#include "../Base/Error.h"

using namespace irr;
using namespace irr::gui;


InputMouse::InputMouse (ICursorControl* cursorCtrl, EventController* eventCtrl)
: cursor(nullptr), currWheel(0), prevWheel(0), currX(0), prevX(0), currY(0), prevY(0)
{
   Init(cursorCtrl, eventCtrl);
}

InputMouse::~InputMouse ()
{
}

void InputMouse::Init (ICursorControl* cursorCtrl, EventController* eventCtrl)
{
   if (cursorCtrl == nullptr)     throw error::NullPointer("Invalid cursor control pointer!", __FUNCTION__);
   else if (eventCtrl == nullptr) throw error::NullPointer("Invalid event controller pointer!", __FUNCTION__);

   cursor = cursorCtrl;
   eventCtrl->MouseCallback(std::bind(&InputMouse::OnEvent, this, std::placeholders::_1));

   std::fill(currButtons.begin(), currButtons.end(), false);
   std::fill(prevButtons.begin(), prevButtons.end(), false);
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

      case EMIE_MOUSE_MOVED:
         currX = event.MouseInput.X;
         currY = event.MouseInput.Y;
         return;

      case EMIE_MOUSE_WHEEL:
         currWheel += event.MouseInput.Wheel;
         return;
   }
}

void InputMouse::Update ()
{
   if (!Enabled()) return;

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

   std::copy(currButtons.begin(), currButtons.end(), prevButtons.begin());

   prevX     = currX;
   prevY     = currY;
   prevWheel = currWheel;
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

bool InputMouse::Moved (int dir)
{
   if (dir == ANY)             return (DX() != 0 || DY() != 0);
   else if (dir == LEFT)       return (DX() < 0);
   else if (dir == RIGHT)      return (DX() > 0);
   else if (dir == HORIZONTAL) return (DX() != 0);
   else if (dir == UP)         return (DY() < 0);
   else if (dir == DOWN)       return (DY() > 0);
   else if (dir == VERTICAL)   return (DY() != 0);
   else if (dir == NONE)       return true;
   else throw error::InvalidParam("Direction out of range!", __FUNCTION__);
}

bool InputMouse::WheelMoved (int dir)
{
   if (dir == ANY) return       (DWheel() != 0);
   else if (dir == UP) return   (DWheel() < 0);
   else if (dir == DOWN) return (DWheel() > 0);
   else if (dir == NONE) return true;
   else throw error::InvalidParam("Direction out of range!", __FUNCTION__);
}

bool InputMouse::Button (int btn)
{
   if (btn < NONE || btn >= BUTTON_COUNT) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
   else if (btn >= 0) return currButtons[btn];

   for (int i = 0; i < BUTTON_COUNT; ++i) {
      if (currButtons[i]) return (btn == ANY);
   }

   return (btn == NONE);
}

bool InputMouse::ButtonPressed (int btn)
{
   if (btn < NONE || btn >= BUTTON_COUNT) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
   else if (btn >= 0) return (currButtons[btn] && !prevButtons[btn]);

   for (int i = 0; i < BUTTON_COUNT; ++i) {
      if (currButtons[i] && !prevButtons[i]) return (btn == ANY);
   }

   return (btn == NONE);
}

bool InputMouse::ButtonReleased (int btn)
{
   if (btn < NONE || btn >= BUTTON_COUNT) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
   else if (btn >= 0) return (!currButtons[btn] && prevButtons[btn]);

   for (int i = 0; i < BUTTON_COUNT; ++i) {
      if (!currButtons[i] && prevButtons[i]) return (btn == ANY);
   }

   return (btn == NONE);
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
