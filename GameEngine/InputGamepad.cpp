
#include "Precomp.h"

#include <OISInputManager.h>
#include <OISJoyStick.h>

#include "InputGamepad.h"

#include "../Base/Error.h"

using namespace OIS;


namespace ge {

   InputGamepad::InputGamepad (InputManager* inputManager)
   : input(nullptr), device(nullptr)
   {
      Init(inputManager);
   }

   InputGamepad::~InputGamepad ()
   {
      if (device != nullptr) {
         input->destroyInputObject(device);
         device = nullptr;
      }
   }

   void InputGamepad::Init (InputManager* inputManager)
   {
      if (inputManager == nullptr) throw error::NullPointer("Invalid input manager pointer!", __FUNCTION__);
      input = inputManager;

      device = (JoyStick*)input->createInputObject(OISJoyStick, true);
      if (device == nullptr) throw error::Create("Failed to create gamepad device!", __FUNCTION__);
   }

   void InputGamepad::Update ()
   {
      if (!Enabled()) return;
      // TODO
   }

}

