
#include "Precomp.h"

#include "InputCore.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"

using namespace base;


namespace ge {

   InputCore::InputCore (EventController* eventCtrl)
   : eventController(nullptr), keyboard(nullptr), mouse(nullptr), gamepad(nullptr)
   {
      if (eventCtrl == nullptr) throw error::NullPointer("Invalid event controller handle!", ERROR_LOCATION);
      eventController = eventCtrl;

      Reset(KeyboardInterface);
   }

   InputCore::~InputCore ()
   {
   }

   void InputCore::Update ()
   {
      if (keyboard != nullptr) keyboard->Update();
      if (mouse != nullptr)    mouse->Update();
      if (gamepad != nullptr)  gamepad->Update();
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

}

