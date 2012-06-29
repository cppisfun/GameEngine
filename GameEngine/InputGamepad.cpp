
#include "Precomp.h"

#include "InputGamepad.h"

#include "../Base/Error.h"


InputGamepad::InputGamepad (IDirectInput8* input, HWND wnd) : enabled(true)
{
   Init(input, wnd);
}

InputGamepad::~InputGamepad ()
{
}

void InputGamepad::Init (IDirectInput8* input, HWND wnd)
{
   if (input == nullptr)    throw error::NullPointer("Invalid input device!", __FUNCTION__);
   else if (wnd == nullptr) throw error::NullPointer("Invalid window handle!", __FUNCTION__);
}

void InputGamepad::Update ()
{
   if (!enabled) return;
}

