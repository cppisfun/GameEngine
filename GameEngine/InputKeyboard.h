
#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>


class InputKeyboard
{
   IDirectInputDevice8* device;

   std::array<char, 256> currKeys;
   std::array<char, 256> prevKeys;

   void Init (IDirectInput8* input, HWND wnd);

   bool CheckCurr (int key) { return (currKeys[key] & 0x80) ? true : false; }
   bool CheckPrev (int key) { return (prevKeys[key] & 0x80) ? true : false; }

public:
   InputKeyboard (IDirectInput8* input, HWND wnd);
   virtual ~InputKeyboard ();

   void Update ();

   bool Key (int key = ANY);
   bool KeyPressed (int key = ANY);
   bool KeyReleased (int key = ANY);
};

