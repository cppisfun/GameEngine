
#include "Precomp.h"

#include "InputKeyboard.h"
#include "EventController.h"

#include "../Base/Error.h"


namespace ge {

   InputKeyboard::InputKeyboard (EventController* eventCtrl)
   {
      if (eventCtrl == nullptr) throw error::NullPointer("Invalid event controller pointer!", ERROR_LOCATION);
      eventCtrl->KeyboardCallback(std::bind(&InputKeyboard::OnEvent, this));

      std::fill(currKeys.begin(), currKeys.end(), false);
      std::fill(prevKeys.begin(), prevKeys.end(), false);
   }

   InputKeyboard::~InputKeyboard ()
   {
   }

   bool InputKeyboard::OnEvent (/*const sf::Event& event*/)
   {
      if (!Enabled()) return false;

//      switch (event.type) {
//         case sf::Event::KeyPressed:  currKeys[event.key.code] = true;  return true;
//         case sf::Event::KeyReleased: currKeys[event.key.code] = false; return true;
//      }

      return false;
   }

   void InputKeyboard::Update ()
   {
      if (!Enabled()) return;
      std::copy(currKeys.begin(), currKeys.end(), prevKeys.begin());
   }

   bool InputKeyboard::Key (int key)
   {
      if (key < Key_None || key >= Key_Count) throw error::InvalidParam("Key id out of range!", ERROR_LOCATION);
      else if (key >= 0) return (currKeys[key]);

      for (int i = 0; i < Key_Count; ++i) {
         if (currKeys[i]) return (key == Key_Any);
      }

      return (key == Key_None);
   }

   bool InputKeyboard::KeyPressed (int key)
   {
      if (key < Key_None || key >= Key_Count) throw error::InvalidParam("Key id out of range!", ERROR_LOCATION);
      else if (key >= 0) return (currKeys[key] && !prevKeys[key]);

      for (int i = 0; i < Key_Count; ++i) {
         if (currKeys[i] && !prevKeys[i]) return (key == Key_Any);
      }

      return (key == Key_None);
   }

   bool InputKeyboard::KeyReleased (int key)
   {
      if (key < Key_None || key >= Key_Count) throw error::InvalidParam("Key id out of range!", ERROR_LOCATION);
      else if (key >= 0) return (!currKeys[key] && prevKeys[key]);

      for (int i = 0; i < Key_Count; ++i) {
         if (!currKeys[i] && prevKeys[i]) return (key == Key_Any);
      }

      return (key == Key_None);
   }

}

