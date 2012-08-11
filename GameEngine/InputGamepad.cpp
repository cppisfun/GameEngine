
#include "Precomp.h"

#include "InputGamepad.h"
#include "EventController.h"

#include "../Base/Error.h"

using namespace irr;


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
}

void InputGamepad::OnEvent (const SEvent& event)
{
   // TODO
}

//InputGamepad::InputGamepad (IDirectInput8* input, HWND wnd) : enabled(true)
//{
//   Init(input, wnd);
//}
//
//InputGamepad::~InputGamepad ()
//{
//}
//
//void InputGamepad::Init (IDirectInput8* input, HWND wnd)
//{
//   if (input == nullptr)    throw error::NullPointer("Invalid input device!", __FUNCTION__);
//   else if (wnd == nullptr) throw error::NullPointer("Invalid window handle!", __FUNCTION__);
//}
//
//void InputGamepad::Update ()
//{
//   if (!enabled) return;
//}

