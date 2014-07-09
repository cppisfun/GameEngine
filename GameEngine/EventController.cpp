
#include "Precomp.h"

#include <SDL.h>

#include "EventController.h"


namespace ge {

   bool EventController::Event (const SDL_Event& event) const
   {
      switch (event.type) {
         case SDL_WINDOWEVENT:
         case SDL_QUIT:
            if (coreCallback != nullptr) return coreCallback(event);
            break;

         case SDL_KEYDOWN:
         case SDL_KEYUP:
//         case SDL_TEXTEDITING:
//         case SDL_TEXTINPUT:
            if (keyboardCallback != nullptr) return keyboardCallback(event);
            break;

         case SDL_MOUSEMOTION:
         case SDL_MOUSEBUTTONDOWN:
         case SDL_MOUSEBUTTONUP:
         case SDL_MOUSEWHEEL:
            if (mouseCallback != nullptr) return mouseCallback(event);
            break;

         case SDL_CONTROLLERAXISMOTION:
         case SDL_CONTROLLERBUTTONDOWN:
         case SDL_CONTROLLERBUTTONUP:
//         case SDL_CONTROLLERDEVICEADDED:
//         case SDL_CONTROLLERDEVICEREMOVED:
//         case SDL_CONTROLLERDEVICEREMAPPED:
//         case SDL_JOYAXISMOTION:
//         case SDL_JOYBALLMOTION:
//         case SDL_JOYHATMOTION:
//         case SDL_JOYBUTTONDOWN:
//         case SDL_JOYBUTTONUP:
//         case SDL_JOYDEVICEADDED:
//         case SDL_JOYDEVICEREMOVED:
            if (gamepadCallback != nullptr) return gamepadCallback(event);
            break;
      }

      return false;
   }
}

