
#include "Precomp.h"

#include "InputManager.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"

using namespace base;


namespace ge {

   InputManager::InputManager (EventController* eventCtrl)
   : eventController(nullptr), keyboard(nullptr), mouse(nullptr), gamepad(nullptr)
   {
      if (eventCtrl == nullptr) throw error::NullPointer("Invalid event controller handle!", ERROR_LOCATION);
      eventController = eventCtrl;

      Reset(KeyboardInterface);
   }

   InputManager::~InputManager ()
   {
   }

   void InputManager::Update ()
   {
      if (keyboard != nullptr) keyboard->Update();
      if (mouse != nullptr)    mouse->Update();
      if (gamepad != nullptr)  gamepad->Update();
   }

   InputManager& InputManager::Reset (const What& what)
   {
      if (what & KeyboardInterface) keyboard.reset(new InputKeyboard(eventController));
      if (what & MouseInterface)    mouse.reset(new InputMouse(eventController));
      if (what & GamepadInterface)  gamepad.reset(new InputGamepad(eventController));

      return *this;
   }

   InputManager& InputManager::ShutDown (const What& what)
   {
      if (what & KeyboardInterface) keyboard.reset();
      if (what & MouseInterface)    mouse.reset();
      if (what & GamepadInterface)  gamepad.reset();

      return *this;
   }

}

