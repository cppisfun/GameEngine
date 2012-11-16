
#include "Precomp.h"

#include <OISInputManager.h>
#include <OISKeyboard.h>

#include "InputKeyboard.h"

#include "../Base/Error.h"

using namespace OIS;


namespace ge {

   class InputKeyboard::EventHandler : public KeyListener
   {
   public:
      EventHandler () { }

      bool keyPressed (const KeyEvent& event) override  { return true; }
      bool keyReleased (const KeyEvent& event) override { return true; }
   };





   InputKeyboard::InputKeyboard (InputManager* input) : device(nullptr), eventHandler(nullptr)
   {
      Init(input);
   }

   InputKeyboard::~InputKeyboard ()
   {
      if (device != nullptr) device->setEventCallback(nullptr);
   }

   void InputKeyboard::Init (InputManager* input)
   {
      if (input == nullptr) throw error::NullPointer("Invalid input manager pointer!", __FUNCTION__);

      device.reset((Keyboard*)input->createInputObject(OISKeyboard, true));
      if (device == nullptr) error::Create("Failed to create keyboard device!", __FUNCTION__);

      eventHandler.reset(new EventHandler);
      if (eventHandler == nullptr) error::Create("Failed to create keyboard event handler!", __FUNCTION__);

      device->setEventCallback(eventHandler.get());

      std::fill(currKeys.begin(), currKeys.end(), false);
      std::fill(prevKeys.begin(), prevKeys.end(), false);
   }

   void InputKeyboard::Update ()
   {
      if (!Enabled()) return;

      std::move(currKeys.begin(), currKeys.end(), prevKeys.begin());
      device->capture();
      device->copyKeyStates(currKeys.data());
   }

   bool InputKeyboard::Key (int key)
   {
      if (key < NONE || key >= KeyCount) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
      else if (key >= 0) return (currKeys[key] > 0);

      for (int i = 0; i < KeyCount; ++i) {
         if (currKeys[i] > 0) return (key == Any);
      }

      return (key == None);
   }

   bool InputKeyboard::KeyPressed (int key)
   {
      if (key < None || key >= KeyCount) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
      else if (key >= 0) return (currKeys[key] > 0 && prevKeys[key] == 0);

      for (int i = 0; i < KeyCount; ++i) {
         if (currKeys[i] > 0 && prevKeys[i] == 0) return (key == Any);
      }

      return (key == None);
   }

   bool InputKeyboard::KeyReleased (int key)
   {
      if (key < None || key >= KeyCount) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
      else if (key >= 0) return (currKeys[key] == 0 && prevKeys[key] > 0);

      for (int i = 0; i < KeyCount; ++i) {
         if (currKeys[i] == 0 && prevKeys[i] > 0) return (key == Any);
      }

      return (key == None);
   }

}

