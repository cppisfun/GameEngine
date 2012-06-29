
#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>


class InputMouse
{
   IDirectInputDevice8* device;

   bool enabled;
   std::array<bool, 4> currBtns;
   std::array<bool, 4> prevBtns;
   int currX, currY;
   int prevX, prevY;

   void Init (IDirectInput8* input, HWND wnd);

public:
   InputMouse (IDirectInput8* input, HWND wnd);
   virtual ~InputMouse ();

   void Update ();

   InputMouse& Enable (bool enable = true) { enabled = enable; return *this; }
   InputMouse& Disable ()                  { enabled = false; return *this; }
   InputMouse& X (int x)                   { currX = x; return *this; }
   InputMouse& Y (int y)                   { currY = y; return *this; }

   bool Enabled () const { return enabled; }
   int X () const        { return currX; }
   int Y () const        { return currY; }
   int DX () const       { return currX - prevX; }
   int DY () const       { return currY - prevY; }

   bool Button (int btn = ANY);
   bool ButtonPressed (int btn = ANY);
   bool ButtonReleased (int btn = ANY);
   bool Moved (int dir = ANY);
};

