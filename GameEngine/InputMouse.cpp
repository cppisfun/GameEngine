
#include "Precomp.h"

#include "InputMouse.h"

#include "../Base/Error.h"


InputMouse::InputMouse (IDirectInput8* input, HWND wnd) : enabled(true), device(nullptr)
{
   Init(input, wnd);
}

InputMouse::~InputMouse ()
{
   if (device != nullptr) {
      device->Unacquire();
      SecureRelease(device);
   }
}

void InputMouse::Init (IDirectInput8* input, HWND wnd)
{
   if (input == nullptr)    throw error::NullPointer("Invalid input device!", __FUNCTION__);
   else if (wnd == nullptr) throw error::NullPointer("Invalid window handle!", __FUNCTION__);

   HRESULT res = input->CreateDevice(GUID_SysMouse, &device, nullptr);
   if (FAILED(res)) throw error::Create("Failed to create mouse device!", __FUNCTION__);

   res = device->SetDataFormat(&c_dfDIMouse);
   if (FAILED(res)) throw error::Execute("Failed to set data format for mouse device!", __FUNCTION__);

   res = device->SetCooperativeLevel(wnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
   if (FAILED(res)) throw error::Execute("Failed to set cooperative level for mouse device!", __FUNCTION__);

   res = device->Acquire();
   if (FAILED(res)) throw error::Query("Failed to acquire mouse device!", __FUNCTION__);
}

void InputMouse::Update ()
{
   if (!enabled) return;

   DIMOUSESTATE state;

   HRESULT res = device->GetDeviceState(sizeof(state), (LPVOID)&state);
   if (FAILED(res)) {
      if (FAILED(device->Acquire())) return;

      res = device->GetDeviceState(sizeof(state), (LPVOID)&state);
      if (FAILED(res)) throw error::Read("Failed to read mouse device state!", __FUNCTION__);
   }

   std::swap(currBtns, prevBtns);
   for (int i = 0; i < 4; ++i) currBtns[i] = (state.rgbButtons[i] & 0x80) ? true : false;

   prevX =  currX;
   prevY =  currY;
   currX += state.lX;
   currY += state.lY;
}

bool InputMouse::Button (int btn)
{
   if (btn < NONE || btn >= 4) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
   else if (btn >= 0) return currBtns[btn];

   for (int i = 0; i < 4; ++i) {
      if (currBtns[btn]) return (btn == ANY);
   }

   return (btn == NONE);
}

bool InputMouse::ButtonPressed (int btn)
{
   if (btn < NONE || btn >= 4) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
   else if (btn >= 0) return (currBtns[btn] && !prevBtns[btn]);

   for (int i = 0; i < 4; ++i) {
      if (currBtns[i] && !prevBtns[i]) return (btn == ANY);
   }

   return (btn == NONE);
}

bool InputMouse::ButtonReleased (int btn)
{
   if (btn < NONE || btn >= 4) throw error::InvalidParam("Button id out of range!", __FUNCTION__);
   else if (btn >= 0) return (!currBtns[btn] && prevBtns[btn]);

   for (int i = 0; i < 4; ++i) {
      if (!currBtns[i] && prevBtns[i]) return (btn == ANY);
   }

   return (btn == NONE);
}

bool InputMouse::Moved (int dir)
{
   if (dir < NONE || dir == 0 || (dir > UP && dir != DOWN && dir != VERTICAL)) throw error::InvalidParam("Direction out of range!", __FUNCTION__);
   else if (dir == ANY)        return (DX() != 0 || DY() != 0);
   else if (dir == LEFT)       return (DX() < 0);
   else if (dir == RIGHT)      return (DX() > 0);
   else if (dir == HORIZONTAL) return (DX() != 0);
   else if (dir == UP)         return (DY() < 0);
   else if (dir == DOWN)       return (DY() > 0);
   else if (dir == VERTICAL)   return (DY() != 0);

   return (dir == NONE);
}

