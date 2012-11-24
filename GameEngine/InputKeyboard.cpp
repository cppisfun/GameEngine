
#include "Precomp.h"

#include <OISInputManager.h>
#include <OISKeyboard.h>

#include "InputKeyboard.h"

#include "../Base/Error.h"


namespace ge {

   InputKeyboard::InputKeyboard (OIS::InputManager* inputManager) : input(nullptr), device(nullptr)
   {
      Init(inputManager);
   }

   InputKeyboard::~InputKeyboard ()
   {
      if (device != nullptr) {
         input->destroyInputObject(device);
         device = nullptr;
      }
   }

   void InputKeyboard::Init (OIS::InputManager* inputManager)
   {
      if (inputManager == nullptr) throw error::NullPointer("Invalid input manager pointer!", __FUNCTION__);
      input = inputManager;

      device = (OIS::Keyboard*)input->createInputObject(OIS::OISKeyboard, true);
      if (device == nullptr) error::Create("Failed to create keyboard device!", __FUNCTION__);

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
      if (key < Key_None || key >= Key_Count) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
      else if (key >= 0) return (currKeys[key] > 0);

      for (int i = 0; i < Key_Count; ++i) {
         if (currKeys[i] > 0) return (key == Key_Any);
      }

      return (key == Key_None);
   }

   bool InputKeyboard::KeyPressed (int key)
   {
      if (key < Key_None || key >= Key_Count) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
      else if (key >= 0) return (currKeys[key] > 0 && prevKeys[key] == 0);

      for (int i = 0; i < Key_Count; ++i) {
         if (currKeys[i] > 0 && prevKeys[i] == 0) return (key == Key_Any);
      }

      return (key == Key_None);
   }

   bool InputKeyboard::KeyReleased (int key)
   {
      if (key < Key_None || key >= Key_Count) throw error::InvalidParam("Key id out of range!", __FUNCTION__);
      else if (key >= 0) return (currKeys[key] == 0 && prevKeys[key] > 0);

      for (int i = 0; i < Key_Count; ++i) {
         if (currKeys[i] == 0 && prevKeys[i] > 0) return (key == Key_Any);
      }

      return (key == Key_None);
   }

}

