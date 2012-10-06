
#pragma once

#include "Precomp.h"

#include <irrlicht.h>


namespace ge {

   /// @brief Event-Basisklasse zur zentralen Event-Erfassung und deren
   /// Weiterleitung an die entsprehcenden EventListener-Objekte.
   ///
   /// Alle Events (z.B. Eingabe-Events der Tastatur oder benutzerdefinierte
   /// Events) werden an dieses Objekt gesendet. Jedes Event-Objekt wird
   /// daraufhin auf seinen Typ untersucht und an die entsprechende
   /// Behandlungskomponente weitergeleitet, die eine Ableitung von
   /// ge::EventListener sein muss.
   ///
   /// Die Anmeldung der Event-Listener als Endstation für eine bestimmte Art
   /// von Events erfolgt über ein entsprechendes Callback.
   ///
   /// Die Event-Listener werden bei der Verwendung von Core automatisch
   /// gesetzt, so dass im Normalfall keine weiteren Einstellungen notwendig
   /// sind.
   class EventController : public irr::IEventReceiver
   {
      std::function<void(const irr::SEvent&)> guiCallback;
      std::function<void(const irr::SEvent&)> mouseCallback;
      std::function<void(const irr::SEvent&)> keyboardCallback;
      std::function<void(const irr::SEvent&)> gamepadCallback;
      std::function<void(const irr::SEvent&)> customCallback;

      virtual bool OnEvent (const irr::SEvent& e) override
      {
         switch (e.EventType) {
            case irr::EET_GUI_EVENT:            if (guiCallback != nullptr) guiCallback(e);           return true;
            case irr::EET_MOUSE_INPUT_EVENT:    if (mouseCallback != nullptr) mouseCallback(e);       return true;
            case irr::EET_KEY_INPUT_EVENT:      if (keyboardCallback != nullptr) keyboardCallback(e); return true;
            case irr::EET_JOYSTICK_INPUT_EVENT: if (gamepadCallback != nullptr) gamepadCallback(e);   return true;
            case irr::EET_USER_EVENT:           if (customCallback != nullptr) customCallback(e);     return true;
         }

         return false;
      }

   public:
      /// @brief Konstruktor.
      EventController () { }

      /// @brief Destruktor.
      ~EventController () { }


      /// @brief Legt den Listener für GUI-Events fest.
      void GUICallback (const std::function<void(const irr::SEvent&)>& callback)      { guiCallback = callback; }

      /// @brief Legt den Listener für Maus-Events fest.
      void MouseCallback (const std::function<void(const irr::SEvent&)>& callback)    { mouseCallback = callback; }

      /// @brief Legt den Listener für Tastatur-Events fest.
      void KeyboardCallback (const std::function<void(const irr::SEvent&)>& callback) { keyboardCallback = callback; }

      /// @brief Legt den Listener für Gamepad-Events fest.
      void GamepadCallback (const std::function<void(const irr::SEvent&)>& callback)  { gamepadCallback = callback; }

      /// @brief Legt den Listener für benutzerdefinierte Events fest.
      void CustomCallback (const std::function<void(const irr::SEvent&)>& callback)   { customCallback = callback; }


      /// @brief Entfernt die Verbindung zum Listener für GUI-Events.
      void ResetGUICallback () { guiCallback = nullptr; }

      /// @brief Entfernt die Verbindung zum Listener für Maus-Events.
      void ResetMouseCallback () { mouseCallback = nullptr; }

      /// @brief Entfernt die Verbindung zum Listener für Tastatur-Events.
      void ResetKeyboardCallback () { keyboardCallback = nullptr; }

      /// @brief Entfernt die Verbindung zum Listener für Gamepad-Events.
      void ResetGamepadCallback () { gamepadCallback = nullptr; }

      /// @brief Entfernt die Verbindung zum Listener für benutzerdefinierte
      /// Events.
      void ResetCustomCallback () { customCallback = nullptr; }
   };

}

