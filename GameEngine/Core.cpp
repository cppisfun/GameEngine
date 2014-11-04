
#pragma once

#include "Precomp.h"

#include <SDL.h>

#include "Core.h"
#include "EventController.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"
#include "../Base/LimitedValue.h"


namespace ge {

   Core::Core () : running(false), window(nullptr), renderer(nullptr), eventController(nullptr), graphics(nullptr), input(nullptr), audio(nullptr), resources(nullptr)
   {
      if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw error::Create("Failed to initialize SDL!", ERROR_LOCATION);

      window = SDL_CreateWindow("GameEngine 0.1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
      if (window == nullptr) throw error::Create("Failed to create SDL application window!", ERROR_LOCATION);

      renderer = SDL_CreateRenderer(window, -1, 0);
      if (renderer == nullptr) throw error::Create("Failed to create SDL renderer!", ERROR_LOCATION);

      eventController.reset(new EventController);
      if (eventController == nullptr) throw error::Create("Failed to create event controller!", ERROR_LOCATION);

      eventController->CoreCallback(std::bind(&Core::OnEvent, this, std::placeholders::_1));
      running = true;
   }

   Core::~Core ()
   {
      ShutDown(AllInterfaces);

      if (renderer != nullptr) { SDL_DestroyRenderer(renderer); renderer = nullptr; }
      if (window != nullptr)   { SDL_DestroyWindow(window); window = nullptr; }

      SDL_Quit();
   }

   void Core::Update ()
   {
      if (!Enabled()) return;

      SDL_Event event;
      while (SDL_PollEvent(&event)) eventController->Event(event);
   }

   bool Core::OnEvent (const SDL_Event& event)
   {
      if (!Enabled()) return false;

      switch (event.type) {
         case SDL_QUIT: running = false; return true;
      }

      return false;
   }

   Core& Core::Reset (InterfaceType what)
   {
      if (what & GraphicsInterface)  graphics.reset(new GraphicsManager(renderer));
      if (what & InputInterface)     input.reset(new InputManager(eventController.get(), window));
      if (what & AudioInterface)     audio.reset(new AudioManager);
      if (what & ResourcesInterface) resources.reset(new ResourcesManager);

      return *this;
   }

   Core& Core::ShutDown (InterfaceType what)
   {
      if (what & ResourcesInterface) resources.reset();
      if (what & AudioInterface)     audio.reset();
      if (what & InputInterface)     input.reset();
      if (what & GraphicsInterface)  graphics.reset();

      return *this;
   }

   Core& Core::EnableScreenSaver (bool enable)
   {
      if (enable) SDL_EnableScreenSaver();
      else        SDL_DisableScreenSaver();

      return *this;
   }

   Core& Core::DisableScreenSaver ()
   {
      SDL_DisableScreenSaver();
      return *this;
   }

   Core& Core::Brightness (float value)
   {
      SDL_SetWindowBrightness(window, misc::LimitedFloat(0.0f, 1.0f, false, value).Value());
      return *this;
   }

   Core& Core::WindowTitle (const std::string& title)
   {
      SDL_SetWindowTitle(window, title.c_str());
      return *this;
   }

   Core& Core::WindowPosition (int x, int y)
   {
      SDL_SetWindowPosition(window, x, y);
      return *this;
   }

   Core& Core::WindowSize (int width, int height)
   {
      SDL_SetWindowSize(window, width, height);
      return *this;
   }

   Core& Core::WindowMaximumSize (int width, int height)
   {
      SDL_SetWindowMaximumSize(window, width, height);
      return *this;
   }

   Core& Core::WindowMinimumSize (int width, int height)
   {
      SDL_SetWindowMinimumSize(window, width, height);
      return *this;
   }

   Core& Core::MaximizeWindow ()
   {
      SDL_MaximizeWindow(window);
      return *this;
   }

   Core& Core::MinimizeWindow ()
   {
      SDL_MinimizeWindow(window);
      return *this;
   }

   Core& Core::RestoreWindow ()
   {
      SDL_RestoreWindow(window);
      return *this;
   }

   Core& Core::WindowToFront ()
   {
      SDL_RaiseWindow(window);
      return *this;
   }

   Core& Core::WindowMode (WindowModeType mode)
   {
      if      (mode == Window)     SDL_SetWindowFullscreen(window, 0);
      else if (mode == Fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
      else                         SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

      return *this;
   }

   Core& Core::WindowBorder (bool border)
   {
      SDL_SetWindowBordered(window, border ? SDL_TRUE : SDL_FALSE);
      return *this;
   }

   Core& Core::ShowWindow (bool show)
   {
      if (show) SDL_ShowWindow(window);
      else      SDL_HideWindow(window);

      return *this;
   }

   Core& Core::HideWindow ()
   {
      SDL_HideWindow(window);
      return *this;
   }

   Core& Core::Focus (bool focus)
   {
      SDL_SetWindowGrab(window, focus ? SDL_TRUE : SDL_FALSE);
      return *this;
   }

   Core& Core::Quit ()
   {
      running = false;
      return *this;
   }

   bool Core::ScreenSaverEnabled () const
   {
      return SDL_IsScreenSaverEnabled() == SDL_TRUE;
   }

   float Core::Brightness () const
   {
      return SDL_GetWindowBrightness(window);
   }

   Position Core::WindowPosition () const
   {
      int x = 0;
      int y = 0;

      SDL_GetWindowPosition(window, &x, &y);
      return Position(x, y);
   }

   Size Core::WindowSize () const
   {
      int width  = 0;
      int height = 0;

      SDL_GetWindowSize(window, &width, &height);
      return Size(width, height);
   }

   Size Core::WindowMaximumSize () const
   {
      int width  = 0;
      int height = 0;

      SDL_GetWindowMaximumSize(window, &width, &height);
      return Size(width, height);
   }

   Size Core::WindowMinimumSize () const
   {
      int width  = 0;
      int height = 0;

      SDL_GetWindowMinimumSize(window, &width, &height);
      return Size(width, height);
   }

   bool Core::Running ()
   {
      if (window != nullptr) Update();
      return running;
   }

   bool Core::Focussed () const
   {
      return SDL_GetWindowGrab(window) == SDL_TRUE;
   }

}

