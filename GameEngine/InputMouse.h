
#pragma once

#include <irrlicht.h>

#include "EventListener.h"

#include "DLL_DEF.h"

class EventController;


class GEDLL InputMouse : public EventListener
{
   void Init (EventController* eventCtrl);

   void OnEvent (const irr::SEvent& event) override;

public:
   InputMouse (EventController* eventCtrl);
   virtual ~InputMouse ();
};

//   InputMouse& X (int x)                   { currX = x; return *this; }
//   InputMouse& Y (int y)                   { currY = y; return *this; }
//
//   int X () const        { return currX; }
//   int Y () const        { return currY; }
//   int DX () const       { return currX - prevX; }
//   int DY () const       { return currY - prevY; }
//
//   bool Button (int btn = ANY);
//   bool ButtonPressed (int btn = ANY);
//   bool ButtonReleased (int btn = ANY);
//   bool Moved (int dir = ANY);

