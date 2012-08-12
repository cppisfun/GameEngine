
#include "Precomp.h"

#include "InputMouse.h"
#include "EventController.h"

#include "../Base/Error.h"

using namespace irr;


InputMouse::InputMouse (EventController* eventCtrl) : currWheel(0), prevWheel(0)
{
   Init(eventCtrl);
}

InputMouse::~InputMouse ()
{
}

void InputMouse::Init (EventController* eventCtrl)
{
   if (eventCtrl == nullptr) error::NullPointer("Invalid event controller pointer!", __FUNCTION__);
   eventCtrl->MouseCallback(std::bind(&InputMouse::OnEvent, this, std::placeholders::_1));

   std::fill(currButtons.begin(), currButtons.end(), false);
   std::fill(prevButtons.begin(), prevButtons.end(), false);

   // TODO: initialize positions!
}

void InputMouse::OnEvent (const SEvent& event)
{
   if (!Enabled()) return;

   switch (event.MouseInput.Event) {
      case EMIE_LMOUSE_PRESSED_DOWN: currButtons[LEFT_BUTTON]   = true;  return;
      case EMIE_MMOUSE_PRESSED_DOWN: currButtons[MIDDLE_BUTTON] = true;  return;
      case EMIE_RMOUSE_PRESSED_DOWN: currButtons[RIGHT_BUTTON]  = true;  return;
      case EMIE_LMOUSE_LEFT_UP:      currButtons[LEFT_BUTTON]   = false; return;
      case EMIE_MMOUSE_LEFT_UP:      currButtons[MIDDLE_BUTTON] = false; return;
      case EMIE_RMOUSE_LEFT_UP:      currButtons[RIGHT_BUTTON]  = false; return;
      //case EMIE_LMOUSE_DOUBLE_CLICK: buttons[LEFT_BUTTON] = DoubleClicked; return;
      //case EMIE_MMOUSE_DOUBLE_CLICK: buttons[_BUTTON] = DoubleClicked; return;
      //case EMIE_RMOUSE_DOUBLE_CLICK: buttons[_BUTTON] = DoubleClicked; return;
      //case EMIE_LMOUSE_TRIPLE_CLICK: buttons[LEFT_BUTTON] = TripleClicked; return;
      //case EMIE_MMOUSE_TRIPLE_CLICK: buttons[_BUTTON] = TripleClicked; return;
      //case EMIE_RMOUSE_TRIPLE_CLICK: buttons[_BUTTON] = TripleClicked; return;

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

   std::copy(currButtons.begin(), currButtons.end(), prevButtons.begin());
   prevX     = currX;
   prevY     = currY;
   prevWheel = currWheel;
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

