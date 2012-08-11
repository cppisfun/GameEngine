
#include "Precomp.h"

#include "GraphicsCore.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"

using namespace irr;


GraphicsCore::GraphicsCore (IrrlichtDevice* device)
: clearColor(0, 0, 63), foreColor(255, 255, 255), backColor(0, 0, 0), driver(nullptr)
{
   Init(device);
}

GraphicsCore::~GraphicsCore ()
{
}

void GraphicsCore::Init (IrrlichtDevice* device)
{
   if (device == nullptr) throw error::NullPointer("Invalid Irrlicht device pointer!", __FUNCTION__);

   driver = device->getVideoDriver();
   if (driver == nullptr) throw error::Query("Failed to query Irrlicht video driver!", __FUNCTION__);

   gui = device->getGUIEnvironment();
   if (gui == nullptr) throw error::Query("Failed to query Irrlicht gui environment!", __FUNCTION__);
}

void GraphicsCore::BeginScene ()
{
   driver->beginScene(true, true, clearColor.AsIrrColor());
}

void GraphicsCore::EndScene ()
{
   driver->endScene();
}

GraphicsCore& GraphicsCore::Text (int x, int y, const std::string& text)   // TODO
{
   gui->getBuiltInFont()->draw(base::AsWString(text).c_str(), core::rect<s32>(x, y, x + 100, y + 100), foreColor.AsIrrColor());
   return *this;
}

