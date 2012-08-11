
#include "Precomp.h"

#include "Core.h"
#include "EventController.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"


using namespace irr;

void Core::Init ()
{
   eventController.reset(new EventController);
   if (eventController == nullptr) throw error::Create("Failed to create event controller!", __FUNCTION__);

   device.reset(irr::createDevice());
   if (device == nullptr) throw error::Create("Failed to create Irrlicht device!", __FUNCTION__);

   device->setEventReceiver(eventController.get());
}

Core& Core::WindowTitle (const std::string& title)
{
   device->setWindowCaption(base::AsWString(title).c_str());
   return *this;
}

