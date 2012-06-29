
#include "Precomp.h"

#include "GraphicsCore.h"

#include "../Base/Error.h"


GraphicsCore::GraphicsCore (HINSTANCE inst, HWND wnd)
: clearColor(0, 0, 63), foreColor(255, 255, 255), backColor(0, 0, 0),
  device(nullptr), context(nullptr), swapChain(nullptr), backBuffer(nullptr)
{
   Init(inst, wnd);
}

GraphicsCore::~GraphicsCore ()
{
   SecureRelease(backBuffer);
   SecureRelease(swapChain);
   SecureRelease(context);
   SecureRelease(device);
}

void GraphicsCore::Init (HINSTANCE inst, HWND wnd)
{
   if (inst == nullptr)     throw error::NullPointer("Invalid instance handle!", __FUNCTION__);
   else if (wnd == nullptr) throw error::NullPointer("Invalid window handle!", __FUNCTION__);

   RECT dimensions;
   if (!GetClientRect(wnd, &dimensions)) throw error::Query("Failed to query dimensions of window client area!", __FUNCTION__);

   unsigned int width  = dimensions.right - dimensions.left;
   unsigned int height = dimensions.bottom - dimensions.top;

   D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE };
   unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

   D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
   unsigned int totalFeatureLevels   = ARRAYSIZE(featureLevels);

   DXGI_SWAP_CHAIN_DESC swapChainDesc;
   ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

   swapChainDesc.BufferCount                        = 1;
   swapChainDesc.BufferDesc.Width                   = width;
   swapChainDesc.BufferDesc.Height                  = height;
   swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
   swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60;
   swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
   swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
   swapChainDesc.OutputWindow                       = wnd;
   swapChainDesc.Windowed                           = true;
   swapChainDesc.SampleDesc.Count                   = 1;
   swapChainDesc.SampleDesc.Quality                 = 0;

   unsigned int creationFlags = 0;
#ifdef DEBUG
   creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

   HRESULT res;

   for (unsigned int driver = 0; driver < totalDriverTypes; ++driver) {
      res = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[driver], nullptr, creationFlags, featureLevels, totalFeatureLevels,
                                          D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &featureLevel, &context);
      if (SUCCEEDED(res)) {
         driverType = driverTypes[driver];
         break;
      }
   }

   if (FAILED(res)) throw error::Create("Failed to create Direct3D device!", __FUNCTION__);

   ID3D11Texture2D* backBufferTexture;

   res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
   if (FAILED(res)) throw error::Query("Failed to query swap chain back buffer!", __FUNCTION__);

   res = device->CreateRenderTargetView(backBufferTexture, nullptr, &backBuffer);
   if (FAILED(res)) throw error::Create("Failed to create render target view on back buffer!", __FUNCTION__);

   context->OMSetRenderTargets(1, &backBuffer, nullptr);

   D3D11_VIEWPORT viewPort;
   viewPort.Width    = static_cast<float>(width);
   viewPort.Height   = static_cast<float>(height);
   viewPort.MinDepth = 0.0f;
   viewPort.MaxDepth = 1.0f;
   viewPort.TopLeftX = 0.0f;
   viewPort.TopLeftY = 0.0f;

   context->RSSetViewports(1, &viewPort);
}

void GraphicsCore::Begin ()
{
   context->ClearRenderTargetView(backBuffer, clearColor.Get());
}

void GraphicsCore::End ()
{
   swapChain->Present(0, 0);
}

