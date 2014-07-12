
#pragma once

union SDL_Event;


namespace ge {

   class EventController
   {
      std::function<bool(const SDL_Event&)> coreCallback;
      std::function<bool(const SDL_Event&)> keyboardCallback;
      std::function<bool(const SDL_Event&)> mouseCallback;
      std::function<bool(const SDL_Event&)> gamepadCallback;

   public:
      EventController ()  { }
      ~EventController () { }

      void CoreCallback     (const std::function<bool(const SDL_Event&)>& callback) { coreCallback = callback; }
      void KeyboardCallback (const std::function<bool(const SDL_Event&)>& callback) { keyboardCallback = callback; }
      void MouseCallback    (const std::function<bool(const SDL_Event&)>& callback) { mouseCallback = callback; }
      void GamepadCallback  (const std::function<bool(const SDL_Event&)>& callback) { gamepadCallback = callback; }

      void RemoveCoreCallback ()     { coreCallback = nullptr; }
      void RemoveKeyboardCallback () { keyboardCallback = nullptr; }
      void RemoveMouseCallback ()    { mouseCallback = nullptr; }
      void RemoveGamepadCallback ()  { gamepadCallback = nullptr; }

      bool Event (const SDL_Event& event) const;
   };

}

