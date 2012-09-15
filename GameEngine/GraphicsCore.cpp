
#include "Precomp.h"

#include "GraphicsCore.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"

using namespace ge;
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

GraphicsCore& GraphicsCore::DrawPixel (int x, int y, const Color& color)
{
   driver->drawPixel(x, y, color.AsIrrColor());
   return *this;
}

GraphicsCore& GraphicsCore::DrawLine (int left, int top, int right, int bottom, const Color& color)
{
   driver->draw2DLine(core::vector2d<int>(left, top), core::vector2d<int>(right, bottom), color.AsIrrColor());
   return *this;
}

GraphicsCore& GraphicsCore::DrawRectangle (int left, int top, int right, int bottom, const Color& color, const DrawType& type)
{
   if (type == Outline) driver->draw2DRectangleOutline(core::rect<int>(left, top, right, bottom), color.AsIrrColor());
   else                 driver->draw2DRectangle(color.AsIrrColor(), core::rect<int>(left, top, right, bottom));

   return *this;
}

GraphicsCore& GraphicsCore::Text (int x, int y, const std::string& text)   // TODO
{
   gui->getBuiltInFont()->draw(base::AsWString(text).c_str(), core::rect<int>(x, y, x + 100, y + 100), foreColor.AsIrrColor());
   return *this;
}

