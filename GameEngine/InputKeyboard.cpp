
#include "Precomp.h"

#include "InputKeyboard.h"
#include "EventController.h"

#include "../Base/Error.h"

using namespace irr;


InputKeyboard::InputKeyboard (EventController* eventCtrl)
{
   Init(eventCtrl);
}

InputKeyboard::~InputKeyboard ()
{
}

void InputKeyboard::Init (EventController* eventCtrl)
{
   if (eventCtrl == nullptr) throw error::NullPointer("Invalid event controller pointer!", __FUNCTION__);
   eventCtrl->KeyboardCallback(std::bind(&InputKeyboard::OnEvent, this, std::placeholders::_1));

   std::fill(currKeys.begin(), currKeys.end(), false);
   std::fill(prevKeys.begin(), prevKeys.end(), false);
}

void InputKeyboard::OnEvent (const SEvent& event)
{
   if (!Enabled()) return;
   currKeys[event.KeyInput.Key] = event.KeyInput.PressedDown;
}

void InputKeyboard::Update ()
{
   if (!Enabled()) return;
   std::copy(currKeys.begin(), currKeys.end(), prevKeys.begin());
}

bool InputKeyboard::Key (int key)
{
   if (key < NONE || key > KEY_KEY_CODES_COUNT) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
   else if (key >= 0) return currKeys[key];

   for (int i = 0; i < KEY_KEY_CODES_COUNT; ++i) {
      if (currKeys[i]) return (key == ANY);
   }

   return (key == NONE);
}

bool InputKeyboard::KeyPressed (int key)
{
   if (key < NONE || key > KEY_KEY_CODES_COUNT) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
   else if (key >= 0) return (currKeys[key] && !prevKeys[key]);

   for (int i = 0; i < KEY_KEY_CODES_COUNT; ++i) {
      if (currKeys[i] && !prevKeys[i]) return (key == ANY);
   }

   return (key == NONE);
}

bool InputKeyboard::KeyReleased (int key)
{
   if (key < NONE || key > KEY_KEY_CODES_COUNT) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
   else if (key >= 0) return (!currKeys[key] && prevKeys[key]);

   for (int i = 0; i < KEY_KEY_CODES_COUNT; ++i) {
      if (!currKeys[i] && prevKeys[i]) return (key == ANY);
   }

   return (key == NONE);
}

