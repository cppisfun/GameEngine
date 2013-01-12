
#pragma once

#include <functional>

#include <SFML/Window/Event.hpp>


namespace ge {

   /// @brief Klasse zur zentralen Event-Erfassung und deren Weiterleitung an
   /// die zuständigen EventListener-Objekte.
   ///
   /// Alle Events, die über sf::Event-Objekte weitergegeben werden können,
   /// werden an dieses Objekt gesendet. Jedes eingehende Event-Objekt wird
   /// abhängig vom Typ an den zuständigen Event-Listener weitergeleitet.
   ///
   /// Die Anmeldung der Event-Listener erfolgt über ein entsprechendes
   /// Callback. Diese werden bei Verwendung von Core automatisch gesetzt, so
   /// dass im Normalfall keine weiteren Einstellungen notwendig sind.
   class EventController
   {
      std::function<bool(const sf::Event&)> windowCallback;
      std::function<bool(const sf::Event&)> keyboardCallback;
      std::function<bool(const sf::Event&)> mouseCallback;
      std::function<bool(const sf::Event&)> gamepadCallback;

   public:
      /// @brief Konstruktor.
      EventController () { }

      /// @brief Destruktor.
      ~EventController () { }


      /// @brief Legt den Listener für die Events des Hauptfensters fest.
      void WindowCallback (const std::function<bool(const sf::Event&)>& callback) { windowCallback = callback; }

      /// @brief Legt den Listener für Tastatur-Events fest.
      void KeyboardCallback (const std::function<bool(const sf::Event&)>& callback) { keyboardCallback = callback; }

      /// @brief Legt den Listener für Maus-Events fest.
      void MouseCallback (const std::function<bool(const sf::Event&)>& callback) { mouseCallback = callback; }

      /// @brief Legt den Listener für Gamepad-Events fest.
      void GamepadCallback (const std::function<bool(const sf::Event&)>& callback) { gamepadCallback = callback; }


      /// @brief Entfernt den Listener für die Events des Hauptfensters.
      void RemoveWindowCallback () { windowCallback = nullptr; }

      /// @brief Entfernt den Listener für Tastatur-Events.
      void RemoveKeyboardCallback () { keyboardCallback = nullptr; }

      /// @brief Entfernt den Listener für Maus-Events.
      void RemoveMouseCallback () { mouseCallback = nullptr; }

      /// @brief Entfernt den Listener für Gamepad-Events.
      void RemoveGamepadCallback () { gamepadCallback = nullptr; }


      /// @brief Leitet einen Event an den entsprechenden Listener weiter.
      bool Event (const sf::Event& event)
      {
         switch (event.type) {
            case sf::Event::Closed:
            case sf::Event::Resized:
            case sf::Event::LostFocus:
            case sf::Event::GainedFocus:
               if (windowCallback != nullptr) return windowCallback(event);
               break;

            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
            case sf::Event::TextEntered:
               if (keyboardCallback != nullptr) return keyboardCallback(event);
               break;

            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
            case sf::Event::MouseWheelMoved:
            case sf::Event::MouseMoved:
            case sf::Event::MouseEntered:
            case sf::Event::MouseLeft:
               if (mouseCallback != nullptr) return mouseCallback(event);
               break;

            case sf::Event::JoystickButtonPressed:
            case sf::Event::JoystickButtonReleased:
            case sf::Event::JoystickMoved:
               if (gamepadCallback != nullptr) return gamepadCallback(event);
               break;
         }

         return false;
      }
   };

}

