
#pragma once

#include <D3D11.h>
#include <D3DX11.h>

#include "Color.h"

#include "DLL_DEF.h"


class GEDLL GraphicsCore
{
   D3D_DRIVER_TYPE driverType;
   D3D_FEATURE_LEVEL featureLevel;

   ID3D11Device* device;
   ID3D11DeviceContext* context;
   IDXGISwapChain* swapChain;
   ID3D11RenderTargetView* backBuffer;

   Color clearColor;
   Color foreColor;
   Color backColor;

   void Init (HINSTANCE inst, HWND wnd);

public:
   GraphicsCore (HINSTANCE inst, HWND wnd);
   virtual ~GraphicsCore ();

   GraphicsCore& ClearColor (const Color& color) { clearColor = color; return *this; }
   GraphicsCore& ForeColor (const Color& color)  { foreColor = color; return *this; }
   GraphicsCore& BackColor (const Color& color)  { backColor = color; return *this; }

   void Begin ();
   void End ();

   Color& ClearColor () { return clearColor; }
   Color& ForeColor ()  { return foreColor; }
   Color& BackColor ()  { return backColor; }
};

