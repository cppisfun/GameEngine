
#include "Precomp.h"

#include "InputCore.h"

#include "../Base/Error.h"

using namespace irr;


namespace ge {

   InputCore::InputCore (IrrlichtDevice* irrDevice, EventController* eventCtrl)
   : device(nullptr), eventController(nullptr), keyboard(nullptr), mouse(nullptr), gamepad(nullptr)
   {
      Init(irrDevice, eventCtrl);
   }

   InputCore::~InputCore ()
   {
      ShutDown(AllInterfaces);
   }

   void InputCore::Init (IrrlichtDevice* irrDevice, EventController* eventCtrl)
   {
      if (irrDevice == nullptr)      throw error::NullPointer("Invalid Irrlicht device pointer!", __FUNCTION__);
      else if (eventCtrl == nullptr) throw error::NullPointer("Invalid event controller pointer!", __FUNCTION__);

      device          = irrDevice;
      eventController = eventCtrl;

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
      if (what & KeyboardInterface) keyboard.reset(new InputKeyboard(eventController));
      if (what & MouseInterface)    mouse.reset(new InputMouse(device->getCursorControl(), eventController));
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

