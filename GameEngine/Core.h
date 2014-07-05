
#pragma once

#include "EventController.h"
#include "EventListener.h"

#include "GraphicsManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "ResourcesManager.h"

#include "Point.h"

#include "../Base/Error.h"

#include "DLL_DEF.h"


namespace ge {

   class GEDLL Core : public EventListener
   {
   public:
      enum What {
         NoInterface        = 0,
         GraphicsInterface  = 1,
         InputInterface     = 2,
         AudioInterface     = 4,
         ResourcesInterface = 8,
         AllInterfaces      = 15
      };

   private:
      static std::unique_ptr<Core> instance;

//      std::unique_ptr<sf::RenderWindow> window;

      std::unique_ptr<EventController>  eventController;
      std::unique_ptr<GraphicsManager>  graphics;
      std::unique_ptr<InputManager>     input;
      std::unique_ptr<AudioManager>     audio;
      std::unique_ptr<ResourcesManager> resources;

      bool hasFocus;

      Core () : hasFocus(true), eventController(nullptr), graphics(nullptr), input(nullptr), audio(nullptr), resources(nullptr)
      {
//         window.reset(new sf::RenderWindow);
//         if (window == nullptr) throw error::Create("Failed to create application window!", ERROR_LOCATION);
//
//         window->create(sf::VideoMode(800, 600), "GameEngine 0.0.5");
//         window->clear(sf::Color::Blue);
//         window->display();

         eventController.reset(new EventController);
         if (eventController == nullptr) throw error::Create("Failed to create event controller!", ERROR_LOCATION);

         eventController->WindowCallback(std::bind(&Core::OnEvent, this));
      }

      Core (const Core&);
      Core& operator= (const Core&);

      void Update () override
      {
         if (!Enabled()) return;

//         sf::Event event;
//         while (window->pollEvent(event)) eventController->Event(event);
      }

      bool OnEvent (/*const sf::Event& event*/) override
      {
         if (!Enabled()) return false;

//         switch (event.type) {
//            case sf::Event::Closed:      window->close();  return true;
//            case sf::Event::GainedFocus: hasFocus = true;  return true;
//            case sf::Event::LostFocus:   hasFocus = false; return true;
//            // TODO: sf::Event::Resized
//            // TODO: sf::Event::TextEntered
//         }

         return false;
      }

   public:
      ~Core ()
      {
         ShutDown(AllInterfaces);
//         if (window->isOpen()) window->close();
      }

      static Core* Instance ()
      {
         if (instance == nullptr) instance.reset(new Core);
         return instance.get();
      }

      Core& Reset (const What& what)
      {
         if (what & GraphicsInterface)  graphics.reset(new GraphicsManager/*(window.get())*/);
         if (what & InputInterface)     input.reset(new InputManager(eventController.get()));
         if (what & AudioInterface)     audio.reset(new AudioManager);
         if (what & ResourcesInterface) resources.reset(new ResourcesManager);

         return *this;
      }

      Core& ShutDown (const What& what)
      {
         if (what & ResourcesInterface) resources.reset();
         if (what & AudioInterface)     audio.reset();
         if (what & InputInterface)     input.reset();
         if (what & GraphicsInterface)  graphics.reset();

         return *this;
      }

//      Core& WindowTitle (const std::string& title) { window->setTitle(title); return *this; }

      Core& WindowIcon (const std::string& iconFile)
      {
         if (iconFile.empty()) throw error::InvalidParam("No icon file specified!", ERROR_LOCATION);

//         sf::Image img;
//         if (!img.loadFromFile(iconFile)) throw error::Create("Failed to create icon from file \"" + iconFile + "\"!", ERROR_LOCATION);
//
//         const auto size = img.getSize();
//         window->setIcon(size.x, size.y, img.getPixelsPtr());

         return *this;
      }

      Core& WindowIcon (const Binary& resource)
      {
         if (resource.empty()) throw error::InvalidParam("Icon resource is empty!", ERROR_LOCATION);

//         sf::Image img;
//         if (!img.loadFromMemory(resource.data(), resource.size())) throw error::Create("Failed to create icon from resource!", ERROR_LOCATION);
//
//         const auto size = img.getSize();
//         window->setIcon(size.x, size.y, img.getPixelsPtr());

         return *this;
      }

//      Core& WindowPosition (int x, int y)                        { window->setPosition(sf::Vector2<int>(x, y)); return *this; }
//      Core& WindowPosition (const Point<int>& pos)               { window->setPosition(pos.AsSFMLVector()); return *this; }
//      Core& WindowSize (unsigned int width, unsigned int height) { window->setSize(sf::Vector2<unsigned int>(width, height)); return *this; }
//      Core& WindowSize (const Point<unsigned int>& dims)         { window->setSize(dims.AsSFMLVector()); return *this; }
//      Core& ShowWindow (bool show = true)                        { window->setVisible(show); return *this; }
//      Core& HideWindow ()                                        { window->setVisible(false); return *this; }
//      Core& ShowMouse (bool show = true)                         { window->setMouseCursorVisible(show); return *this; }
//      Core& HideMouse ()                                         { window->setMouseCursorVisible(false); return *this; }
//      Core& EnableVSync (bool enable = true)                     { window->setVerticalSyncEnabled(enable); return *this; }
//      Core& DisableVSync ()                                      { window->setVerticalSyncEnabled(false); return *this; }
//      Core& EnableKeyRepeat (bool enable = true)                 { window->setKeyRepeatEnabled(enable); return *this; }
//      Core& DisableKeyRepeat ()                                  { window->setKeyRepeatEnabled(false); return *this; }
//      Core& EnableFrameRateLimit (unsigned int limit)            { window->setFramerateLimit(limit); return *this; }
//      Core& DisableFrameRateLimit ()                             { window->setFramerateLimit(0u); return *this; }
//      Core& DoNothing ()                                         { sf::sleep(sf::milliseconds(50)); return *this; }
//      Core& Quit ()                                              { window->close(); return *this; }

//      const Point<int> WindowPosition () const      { return Point<int>(window->getPosition()); }
//      const Point<unsigned int> WindowSize () const { return Point<unsigned int>(window->getSize()); }
//      HWND WindowHandle () const                    { return window->getSystemHandle(); }

//      bool IsRunning () { Update(); return window->isOpen(); }
//      bool HasFocus () const { return hasFocus; }

      GraphicsManager* Graphics ()   { if (graphics == nullptr) Reset(GraphicsInterface); return graphics.get(); }
      InputManager* Input ()         { if (input == nullptr) Reset(InputInterface); return input.get(); }
      AudioManager* Audio ()         { if (audio == nullptr) Reset(AudioInterface); return audio.get(); }
      ResourcesManager* Resources () { if (resources == nullptr) Reset(ResourcesInterface); return resources.get(); }
   };



   std::unique_ptr<Core> Core::instance = nullptr;

}

