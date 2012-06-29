
#include "Precomp.h"

#include "InputKeyboard.h"

#include "../Base/Error.h"


InputKeyboard::InputKeyboard (IDirectInput8* input, HWND wnd) : device(nullptr)
{
   Init(input, wnd);
}

InputKeyboard::~InputKeyboard ()
{
   if (device != nullptr) {
      device->Unacquire();
      SecureRelease(device);
   }
}

void InputKeyboard::Init (IDirectInput8* input, HWND wnd)
{
   if (input == nullptr)    throw error::NullPointer("Invalid input device!", __FUNCTION__);
   else if (wnd == nullptr) throw error::NullPointer("Invalid window handle!", __FUNCTION__);

   HRESULT res = input->CreateDevice(GUID_SysKeyboard, &device, nullptr);
   if (FAILED(res)) throw error::Create("Failed to create keyboard device!", __FUNCTION__);

   res = device->SetDataFormat(&c_dfDIKeyboard);
   if (FAILED(res)) throw error::Execute("Failed to set data format for keyboard device!", __FUNCTION__);

   res = device->SetCooperativeLevel(wnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
   if (FAILED(res)) throw error::Execute("Failed to set cooperative level for keyboard device!", __FUNCTION__);

   res = device->Acquire();
   if (FAILED(res)) throw error::Query("Failed to acquire keyboard device!", __FUNCTION__);
}

void InputKeyboard::Update ()
{
   std::swap(currKeys, prevKeys);

   HRESULT res = device->GetDeviceState(currKeys.size(), (LPVOID)&currKeys);
   if (FAILED(res)) {
      if (FAILED(device->Acquire())) return;

      res = device->GetDeviceState(currKeys.size(), (LPVOID)&currKeys);
      if (FAILED(res)) throw error::Read("Failed to read keyboard device state!", __FUNCTION__);
   }
}

bool InputKeyboard::Key (int key)
{
   if (key < NONE || key >= 256) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
   else if (key >= 0) return CheckCurr(key);

   for (int i = 0; i < 256; ++i) {
      if (CheckCurr(i)) return (key == ANY);
   }

   return (key == NONE);
}

bool InputKeyboard::KeyPressed (int key)
{
   if (key < NONE || key >= 256) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
   else if (key >= 0) return (CheckCurr(key) && !CheckPrev(key));

   for (int i = 0; i < 256; ++i) {
      if (CheckCurr(i) && !CheckPrev(i)) return (key == ANY);
   }

   return (key == NONE);
}

bool InputKeyboard::KeyReleased (int key)
{
   if (key < NONE || key >= 256) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
   else if (key >= 0) return (!CheckCurr(key) && CheckPrev(key));

   for (int i = 0; i < 256; ++i) {
      if (!CheckCurr(i) && CheckPrev(i)) return (key == ANY);
   }

   return (key == NONE);
}

