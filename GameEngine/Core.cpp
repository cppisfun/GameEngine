
#include "Precomp.h"

#include "Core.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"

using namespace irr;


namespace ge {

   static LRESULT CALLBACK WindowProc (HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      switch (msg) {
         case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
      }

      return DefWindowProc(wnd, msg, wParam, lParam);
   }

   Core::Core (HINSTANCE inst)
   : instanceHandle(inst), resizableWindow(false), device(nullptr),
     graphics(nullptr), input(nullptr), audio(nullptr), resources(nullptr)
   {
      Init();
   }

   Core::~Core ()
   {
      ShutDown(AllInterfaces);
      UnregisterClass(windowClassName, instanceHandle);
   }

   void Core::Init ()
   {
      if (instanceHandle == nullptr) throw error::NullPointer("Invalid instance handle!", __FUNCTION__);

      InitWindow();

      SIrrlichtCreationParameters params;
      params.WindowId = windowHandle;

      device.reset(irr::createDeviceEx(params));
      if (device == nullptr) throw error::Create("Failed to create Irrlicht device!", __FUNCTION__);
   }

   void Core::InitWindow ()
   {
      WNDCLASSEX wnd    = { 0 };
      wnd.cbSize        = sizeof(WNDCLASSEX);
      wnd.style         = CS_HREDRAW | CS_VREDRAW;
      wnd.lpfnWndProc   = WindowProc;
      wnd.hInstance     = instanceHandle;
      wnd.hCursor       = LoadIcon(nullptr, IDC_ARROW);
      wnd.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      wnd.lpszMenuName  = nullptr;
      wnd.lpszClassName = windowClassName;

      if (!RegisterClassEx(&wnd)) throw error::Create("Failed to register window class!", __FUNCTION__);

      windowHandle = CreateWindow(windowClassName, "GE Main Window", WS_OVERLAPPEDWINDOW, 0, 0, 640, 480, nullptr, nullptr, instanceHandle, nullptr);
      if (windowHandle == nullptr) throw error::Create("Failed to create main window!", __FUNCTION__);

      ShowWindow(windowHandle, SW_NORMAL);
      UpdateWindow(windowHandle);
   }

   Core& Core::WindowTitle (const std::string& title)
   {
      device->setWindowCaption(base::AsWString(title).c_str());
      return *this;
   }

}

