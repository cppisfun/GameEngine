
#pragma once

#include "EventListener.h"

#include "DLL_DEF.h"

class EventController;


class GEDLL InputMouse : public EventListener
{
private:
   int currX, currY;
   int prevX, prevY;
   float currWheel, prevWheel;
   std::array<bool, BUTTON_COUNT> currButtons;
   std::array<bool, BUTTON_COUNT> prevButtons;

   void Init (EventController* eventCtrl);

   void OnEvent (const irr::SEvent& event) override;

public:
   InputMouse (EventController* eventCtrl);
   virtual ~InputMouse ();

   void Update ();

   int X () const { return currX; }
   int Y () const { return currY; }
   float Wheel () const { return currWheel; }

   int DX () const { return currX - prevX; }
   int DY () const { return currY - prevY; }
   float DWheel () const { return prevWheel - currWheel; }

   bool Moved (int direction = ANY);
   bool WheelMoved (int direction = ANY);

   bool Button (int btn = ANY);
   bool ButtonPressed (int btn = ANY);
   bool ButtonReleased (int btn = ANY);
   //bool ButtonClicked (int btn = ANY);
   //bool ButtonDoubleClicked (int btn = ANY);
   //bool ButtonTripleClicked (int btn = ANY);
};
