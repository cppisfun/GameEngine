
#include "Precomp.h"

#include <OISInputManager.h>
#include <OISJoyStick.h>

#include "InputGamepad.h"

#include "../Base/Error.h"

using namespace OIS;


namespace ge {

   InputGamepad::InputGamepad (InputManager* input) : device(nullptr)
   {
      Init(input);
   }

   InputGamepad::~InputGamepad ()
   {
   }

   void InputGamepad::Init (InputManager* input)
   {
      if (input == nullptr) throw error::NullPointer("Invalid input manager pointer!", __FUNCTION__);

      device = (JoyStick*)input->createInputObject(OISJoyStick, true);
      if (device == nullptr) throw error::Create("Failed to create gamepad device!", __FUNCTION__);
   }

   void InputGamepad::Update ()
   {
      if (!Enabled()) return;
      // TODO
   }

}

