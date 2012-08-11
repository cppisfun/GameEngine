
#include "Precomp.h"

#include "InputMouse.h"
#include "EventController.h"

#include "../Base/Error.h"

using namespace irr;


InputMouse::InputMouse (EventController* eventCtrl)
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
}

void InputMouse::OnEvent (const SEvent& event)
{
   // TODO
}

//bool InputMouse::Button (int btn)
//{
//   if (btn < NONE || btn >= 4) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
//   else if (btn >= 0) return currBtns[btn];
//
//   for (int i = 0; i < 4; ++i) {
//      if (currBtns[btn]) return (btn == ANY);
//   }
//
//   return (btn == NONE);
//}
//
//bool InputMouse::ButtonPressed (int btn)
//{
//   if (btn < NONE || btn >= 4) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
//   else if (btn >= 0) return (currBtns[btn] && !prevBtns[btn]);
//
//   for (int i = 0; i < 4; ++i) {
//      if (currBtns[i] && !prevBtns[i]) return (btn == ANY);
//   }
//
//   return (btn == NONE);
//}
//
//bool InputMouse::ButtonReleased (int btn)
//{
//   if (btn < NONE || btn >= 4) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
//   else if (btn >= 0) return (!currBtns[btn] && prevBtns[btn]);
//
//   for (int i = 0; i < 4; ++i) {
//      if (!currBtns[i] && prevBtns[i]) return (btn == ANY);
//   }
//
//   return (btn == NONE);
//}
//
//bool InputMouse::Moved (int dir)
//{
//   if (dir < NONE || dir == 0 || (dir > UP && dir != DOWN && dir != VERTICAL)) throw error::InvalidParam("Direction out of range!", __FUNCTION__);
//   else if (dir == ANY)        return (DX() != 0 || DY() != 0);
//   else if (dir == LEFT)       return (DX() < 0);
//   else if (dir == RIGHT)      return (DX() > 0);
//   else if (dir == HORIZONTAL) return (DX() != 0);
//   else if (dir == UP)         return (DY() < 0);
//   else if (dir == DOWN)       return (DY() > 0);
//   else if (dir == VERTICAL)   return (DY() != 0);
//
//   return (dir == NONE);
//}

