
#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>


class InputGamepad
{
   bool enabled;

   void Init (IDirectInput8* input, HWND wnd);

public:
   InputGamepad (IDirectInput8* input, HWND wnd);
   virtual ~InputGamepad ();

   void Update ();

   InputGamepad& Enable (bool enable = true) { enabled = enable; return *this; }
   InputGamepad& Disable ()                  { enabled = false; return *this; }
};

