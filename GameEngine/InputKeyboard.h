
#pragma once

#include <Keycodes.h>

#include "EventListener.h"

#include "DLL_DEF.h"

class EventController;


class GEDLL InputKeyboard : public EventListener
{

   std::array<bool, irr::KEY_KEY_CODES_COUNT> currKeys;
   std::array<bool, irr::KEY_KEY_CODES_COUNT> prevKeys;

   void Init (EventController* eventCtrl);

   void OnEvent (const irr::SEvent& event) override;

public:
   InputKeyboard (EventController* eventCtrl);
   virtual ~InputKeyboard ();

   void Update ();

   bool Key (int key = ANY);
   bool KeyPressed (int key = ANY);
   bool KeyReleased (int key = ANY);
};

