
#include "Precomp.h"

#include <OISInputManager.h>

#include "InputCore.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"

using namespace OIS;
using namespace base;


namespace ge {

   InputCore::InputCore (HWND window)
   : input(nullptr), keyboard(nullptr), mouse(nullptr), gamepad(nullptr)
   {
      Init(window);
   }

   InputCore::~InputCore ()
   {
      ShutDown(AllInterfaces);

      if (input != nullptr) {
         InputManager::destroyInputSystem(input);
         input = nullptr;
      }
   }

   void InputCore::Init (HWND window)
   {
      if (window == nullptr) throw error::NullPointer("Invalid window handle!", __FUNCTION__);

      input = InputManager::createInputSystem((size_t)window);
      if (input == nullptr) throw error::Create("Failed to create input system!", __FUNCTION__);

      Reset(KeyboardInterface);
   }

   void InputCore::Update ()
   {
      if (keyboard != nullptr) keyboard->Update();
      if (mouse != nullptr)    mouse->Update();
      if (gamepad != nullptr)  gamepad->Update();
   }

   InputCore& InputCore::Reset (const What& what)
   {
      if (what & KeyboardInterface) keyboard.reset(new InputKeyboard(input));
      if (what & MouseInterface)    mouse.reset(new InputMouse(input));
      if (what & GamepadInterface)  gamepad.reset(new InputGamepad(input));

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

