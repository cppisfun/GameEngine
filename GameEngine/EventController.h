
#pragma once

#include <functional>


namespace ge {

   class EventController
   {
      std::function<bool(/*const sf::Event&*/)> windowCallback;
      std::function<bool(/*const sf::Event&*/)> keyboardCallback;
      std::function<bool(/*const sf::Event&*/)> mouseCallback;
      std::function<bool(/*const sf::Event&*/)> gamepadCallback;

   public:
      EventController ()  { }
      ~EventController () { }

      void WindowCallback (const std::function<bool(/*const sf::Event&*/)>& callback)   { windowCallback = callback; }
      void KeyboardCallback (const std::function<bool(/*const sf::Event&*/)>& callback) { keyboardCallback = callback; }
      void MouseCallback (const std::function<bool(/*const sf::Event&*/)>& callback)    { mouseCallback = callback; }
      void GamepadCallback (const std::function<bool(/*const sf::Event&*/)>& callback)  { gamepadCallback = callback; }

      void RemoveWindowCallback ()   { windowCallback = nullptr; }
      void RemoveKeyboardCallback () { keyboardCallback = nullptr; }
      void RemoveMouseCallback ()    { mouseCallback = nullptr; }
      void RemoveGamepadCallback ()  { gamepadCallback = nullptr; }

      bool Event (/*const sf::Event& event*/)
      {
//         switch (event.type) {
//            case sf::Event::Closed:
//            case sf::Event::Resized:
//            case sf::Event::LostFocus:
//            case sf::Event::GainedFocus:
//               if (windowCallback != nullptr) return windowCallback(event);
//               break;
//
//            case sf::Event::KeyPressed:
//            case sf::Event::KeyReleased:
//            case sf::Event::TextEntered:
//               if (keyboardCallback != nullptr) return keyboardCallback(event);
//               break;
//
//            case sf::Event::MouseButtonPressed:
//            case sf::Event::MouseButtonReleased:
//            case sf::Event::MouseWheelMoved:
//            case sf::Event::MouseMoved:
//            case sf::Event::MouseEntered:
//            case sf::Event::MouseLeft:
//               if (mouseCallback != nullptr) return mouseCallback(event);
//               break;
//
//            case sf::Event::JoystickButtonPressed:
//            case sf::Event::JoystickButtonReleased:
//            case sf::Event::JoystickMoved:
//               if (gamepadCallback != nullptr) return gamepadCallback(event);
//               break;
//         }

         return false;
      }
   };

}

