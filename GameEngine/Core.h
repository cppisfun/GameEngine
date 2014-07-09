
#pragma once

#include "EventListener.h"
#include "Point.h"

#include "GraphicsManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "ResourcesManager.h"

#include "DLL_DEF.h"

struct SDL_Window;
struct SDL_Renderer;


namespace ge {

   class EventController;

   class GEDLL Core : public EventListener
   {
   public:
      enum InterfaceType {
         NoInterface        = 0,
         GraphicsInterface  = 1,
         InputInterface     = 2,
         AudioInterface     = 4,
         ResourcesInterface = 8,
         AllInterfaces      = 15
      };

      enum WindowModeType {
         Window,
         Fullscreen,
         FullscreenWindow
      };

   private:
      static std::unique_ptr<Core> instance;

      SDL_Window*   window;
      SDL_Renderer* renderer;

      std::unique_ptr<EventController>  eventController;
      std::unique_ptr<GraphicsManager>  graphics;
      std::unique_ptr<InputManager>     input;
      std::unique_ptr<AudioManager>     audio;
      std::unique_ptr<ResourcesManager> resources;

      bool running;

      Core ();
      Core (const Core&);
      Core& operator= (const Core&);

      void Update () override;

      bool OnEvent (const SDL_Event& event) override;

   public:
      virtual ~Core ();

      static Core* Instance () { if (instance == nullptr) instance.reset(new Core); return instance.get(); }

      Core& Reset (InterfaceType what);
      Core& ShutDown (InterfaceType what);

      Core& EnableScreenSaver (bool enable = true);
      Core& DisableScreenSaver ();
      Core& Brightness (float value);

      Core& WindowTitle (const std::string& title);
      Core& WindowPosition (int x, int y);
      Core& WindowSize (int width, int height);
      Core& WindowMaximumSize (int width, int height);
      Core& WindowMinimumSize (int width, int height);

      Core& WindowPosition (const Point<int>& pos)     { return WindowPosition(pos.X(), pos.Y()); }
      Core& WindowSize (const Point<int>& dims)        { return WindowSize(dims.X(), dims.Y()); }
      Core& WindowMaximumSize (const Point<int>& dims) { return WindowMaximumSize(dims.X(), dims.Y()); }
      Core& WindowMinimumSize (const Point<int>& dims) { return WindowMinimumSize(dims.X(), dims.Y()); }

      Core& MaximizeWindow ();
      Core& MinimizeWindow ();
      Core& RestoreWindow ();
      Core& WindowToFront ();
      Core& WindowMode (WindowModeType mode);
      Core& WindowBorder (bool border = true);
      Core& ShowWindow (bool show = true);
      Core& HideWindow ();

      Core& Focus (bool focus = true);
      Core& Quit ();

      bool ScreenSaverEnabled () const;
      float Brightness () const;

      Point<int> WindowPosition () const;
      Point<int> WindowSize () const;
      Point<int> WindowMaximumSize () const;
      Point<int> WindowMinimumSize () const;

      bool Running ();
      bool Focussed () const;

      GraphicsManager* Graphics ()   { if (graphics == nullptr) Reset(GraphicsInterface); return graphics.get(); }
      InputManager* Input ()         { if (input == nullptr) Reset(InputInterface); return input.get(); }
      AudioManager* Audio ()         { if (audio == nullptr) Reset(AudioInterface); return audio.get(); }
      ResourcesManager* Resources () { if (resources == nullptr) Reset(ResourcesInterface); return resources.get(); }
   };



   std::unique_ptr<Core> Core::instance = nullptr;

}

