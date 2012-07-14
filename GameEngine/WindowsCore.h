
#pragma once

#include "DLL_DEF.h"


class GEDLL WindowsCore
{
   HWND windowHandle;
   WNDCLASSEX wndClass;

   void Init (HINSTANCE inst);

public:
   WindowsCore (HINSTANCE inst);
   virtual ~WindowsCore ();

   HWND WindowHandle () const { return windowHandle; }
};


LRESULT CALLBACK WndProc (HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);
