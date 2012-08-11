
#include "Precomp.h"

#include "InputCore.h"

#include "../Base/Error.h"


InputCore::InputCore (EventController* eventCtrl)
: eventController(nullptr), keyboard(nullptr), mouse(nullptr), gamepad(nullptr)
{
   Init(eventCtrl);
}

InputCore::~InputCore ()
{
   ShutDown(AllInterfaces);
}

void InputCore::Init (EventController* eventCtrl)
{
   if (eventCtrl == nullptr) throw error::NullPointer("Invalid event controller pointer!", __FUNCTION__);

   eventController = eventCtrl;
   Reset(KeyboardInterface);
}

InputCore& InputCore::Reset (const What& what)
{
   if (what & KeyboardInterface) keyboard.reset(new InputKeyboard(eventController));
   if (what & MouseInterface)    mouse.reset(new InputMouse(eventController));
   if (what & GamepadInterface)  gamepad.reset(new InputGamepad(eventController));

   return *this;
}

InputCore& InputCore::ShutDown (const What& what)
{
   if (what & KeyboardInterface) keyboard.reset();
   if (what & MouseInterface)    mouse.reset();
   if (what & GamepadInterface)  gamepad.reset();

   return *this;
}

