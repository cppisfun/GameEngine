
#include "Precomp.h"

#include "InputCore.h"

#include "../Base/Error.h"


InputCore::InputCore (HINSTANCE inst, HWND wnd)
: device(nullptr), keyboard(nullptr), mouse(nullptr), gamepad(nullptr)
{
   Init(inst, wnd);
}

InputCore::~InputCore ()
{
   ShutDown(AllInterfaces);
   SecureRelease(device);
}

void InputCore::Init (HINSTANCE inst, HWND wnd)
{
   if (inst == nullptr)     throw error::NullPointer("Invalid instance handle!", __FUNCTION__);
   else if (wnd == nullptr) throw error::NullPointer("Invalid window handle!", __FUNCTION__);

   instanceHandle = inst;
   windowHandle   = wnd;

   HRESULT res = DirectInput8Create(inst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&device, nullptr);
   if (FAILED(res)) throw error::Create("Failed to create DirectInput8 device!", __FUNCTION__);

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
   if (what & KeyboardInterface) keyboard.reset(new InputKeyboard(device, windowHandle));
   if (what & MouseInterface)    mouse.reset(new InputMouse(device, windowHandle));
   if (what & GamepadInterface)  gamepad.reset(new InputGamepad(device, windowHandle));

   return *this;
}

InputCore& InputCore::ShutDown (const What& what)
{
   if (what & KeyboardInterface) keyboard.reset();
   if (what & MouseInterface)    mouse.reset();
   if (what & GamepadInterface)  gamepad.reset();

   return *this;
}

