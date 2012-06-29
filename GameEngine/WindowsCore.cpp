
#include "Precomp.h"

#include "WindowsCore.h"

#include "../Base/Error.h"


WindowsCore::WindowsCore (HINSTANCE inst) : windowHandle(nullptr)
{
   Init(inst);
}

WindowsCore::~WindowsCore ()
{
}

void WindowsCore::Init (HINSTANCE inst)
{
   if (inst == nullptr) throw error::NullPointer("Invalid instance handle!", __FUNCTION__);

   WNDCLASSEX wndClass    = { 0 };
   wndClass.cbSize        = sizeof(wndClass);
   wndClass.style         = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc   = WndProc;
   wndClass.hInstance     = inst;
   wndClass.hCursor       = LoadCursor(nullptr, IDC_ARROW);
   wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
   wndClass.lpszMenuName  = nullptr;
   wndClass.lpszClassName = "WindowClass";

   if (!RegisterClassEx(&wndClass)) {
      throw error::Create("Failed to register window class!", __FUNCTION__);
   }

   RECT rect = { 0, 0, 640, 480 };

   if (!AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false)) throw error::Execute("Failed to adjust window rectangle!", __FUNCTION__);

   windowHandle = CreateWindow(wndClass.lpszClassName, "GameEngine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                               rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, inst, nullptr);

   if (!windowHandle) throw error::Create("Failed to create window handle!", __FUNCTION__);

   ShowWindow(windowHandle, 1);
}



LRESULT CALLBACK WndProc (HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   switch (msg) {
      case WM_DESTROY:
         PostQuitMessage(0);
         break;

      default:
         return DefWindowProc(wnd, msg, wParam, lParam);
   }

   return 0;
}

