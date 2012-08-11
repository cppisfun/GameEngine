
#pragma once

#include <irrlicht.h>

#include "EventListener.h"

#include "DLL_DEF.h"

class EventController;


class GEDLL InputGamepad : public EventListener
{
   void Init (EventController* eventCtrl);

   void OnEvent (const irr::SEvent& event);

public:
   InputGamepad (EventController* eventCtrl);
   virtual ~InputGamepad ();
};

