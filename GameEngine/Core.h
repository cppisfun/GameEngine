
#pragma once

#include <SFML/Graphics.hpp>

#include "EventController.h"
#include "EventListener.h"

#include "GraphicsCore.h"
#include "InputCore.h"
#include "AudioCore.h"
#include "ResourcesCore.h"

#include "Point.h"

#include "../Base/Error.h"

#include "DLL_DEF.h"


/// @brief Namespace für alle GameEngine-Komponenten.
namespace ge {

   /// @brief Hauptkomponente von GameEngine, verwaltet alle Kernobjekte.
   ///
   /// Wurde nach dem Singleton-Muster entworfen und steht somit immer durch
   /// Aufrufen von Core::Instance() zur Verfügung.
   ///
   /// Die Klasse instantiiert Kernobjekte entweder durch Aufrufen der
   /// Methode Reset() oder Verwenden eines entsprechenden Getters. Sollte die
   /// Verwendung einer Kernkomponente vom Bestehen einer anderen abhängen,
   /// wird dies intern entsprechend berücksichtigt.
   class GEDLL Core : public EventListener
   {
   public:
      /// @brief Auflistung der möglichen Komponentenangaben zur Verwendung mit
      /// Core::Reset() oder Core::ShutDown().
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

      std::unique_ptr<sf::RenderWindow> window;

      std::unique_ptr<EventController> eventController;
      std::unique_ptr<GraphicsCore>    graphics;
      std::unique_ptr<InputCore>       input;
      std::unique_ptr<AudioCore>       audio;
      std::unique_ptr<ResourcesCore>   resources;

      bool hasFocus;

      Core () : hasFocus(true), eventController(nullptr), graphics(nullptr), input(nullptr), audio(nullptr), resources(nullptr)
      {
         window.reset(new sf::RenderWindow);
         if (window == nullptr) throw error::Create("Failed to create application window!", __FUNCTION__);

         window->create(sf::VideoMode(800, 600), "GameEngine 0.0.5");
         window->clear(sf::Color::Blue);
         window->display();

         eventController.reset(new EventController);
         if (eventController == nullptr) throw error::Create("Failed to create event controller!", __FUNCTION__);

         eventController->WindowCallback(std::bind(&Core::OnEvent, this, std::placeholders::_1));
      }

      Core (const Core&);
      Core& operator= (const Core&);

      void Update () override
      {
         if (!Enabled()) return;

         sf::Event event;
         while (window->pollEvent(event)) eventController->Event(event);
      }

      bool OnEvent (const sf::Event& event) override
      {
         if (!Enabled()) return false;

         switch (event.type) {
            case sf::Event::Closed:      window->close();  return true;
            case sf::Event::GainedFocus: hasFocus = true;  return true;
            case sf::Event::LostFocus:   hasFocus = false; return true;
            // TODO: sf::Event::Resized
            // TODO: sf::Event::TextEntered
         }

         return false;
      }

   public:
      /// @brief Destruktor. Entfernt automatisch alle noch bestehenden
      /// Kernkomponenten und gibt Ressourcen frei, die innerhalb von Core oder
      /// eines in Core gehaltenen Kernobjektes erreichbar sind.
      ~Core ()
      {
         ShutDown(AllInterfaces);
         if (window->isOpen()) window->close();
      }

      /// @brief Liefert den Pointer zum Core-Objekt. Beim ersten Aufruf wird
      /// dieses erstellt, alle Aufrufe liefern dieses einzelne Objekt zurück.
      static Core* Instance ()
      {
         if (instance == nullptr) instance.reset(new Core);
         return instance.get();
      }


      /// @brief Setzt eine oder mehrere Kernkomponenten zurück. Dies beinhaltet
      /// die Freigabe der Ressourcen, die in den entsprechenden Komponenten
      /// gehalten werden.
      /// @param what Komponentenangabe aus Core::What
      Core& Reset (const What& what)
      {
         if (what & GraphicsInterface)  graphics.reset(new GraphicsCore(window.get()));
         if (what & InputInterface)     input.reset(new InputCore(eventController.get()));
         if (what & AudioInterface)     audio.reset(new AudioCore);
         if (what & ResourcesInterface) resources.reset(new ResourcesCore);

         return *this;
      }

      /// @brief Entfernt eine oder mehrere Kernkomponenten. Dies beinhaltet
      /// die Freigabe der Ressourcen, die in den entsprechenden Komponenten
      /// gehalten werden.
      /// @param what Komponentenangabe aus Core::What
      Core& ShutDown (const What& what)
      {
         if (what & ResourcesInterface) resources.reset();
         if (what & AudioInterface)     audio.reset();
         if (what & InputInterface)     input.reset();
         if (what & GraphicsInterface)  graphics.reset();

         return *this;
      }


      /// @brief Legt den Fenstertitel fest.
      Core& WindowTitle (const std::string& title) { window->setTitle(title); return *this; }

      /// @brief Erzeugt das Fenster-Icon aus einer entsprechenden Datei (ohne
      /// die Verwendung von ResourcesCore).
      Core& WindowIcon (const std::string& iconFile)
      {
         if (iconFile.empty()) throw error::InvalidParam("No icon file specified!", __FUNCTION__);

         sf::Image img;
         if (!img.loadFromFile(iconFile)) throw error::Create("Failed to create icon from file \"" + iconFile + "\"!", __FUNCTION__);

         const auto size = img.getSize();
         window->setIcon(size.x, size.y, img.getPixelsPtr());

         return *this;
      }

      /// @brief Erzeugt das Fenster-Icon aus bereits im Speicher befindlichen
      /// Binärdaten (normalerweise im ResourcesCore gehalten).
      Core& WindowIcon (const std::vector<char>& resource)
      {
         if (resource.empty()) throw error::InvalidParam("Icon resource is empty!", __FUNCTION__);

         sf::Image img;
         if (!img.loadFromMemory(resource.data(), resource.size())) throw error::Create("Failed to create icon from resource!", __FUNCTION__);

         const auto size = img.getSize();
         window->setIcon(size.x, size.y, img.getPixelsPtr());

         return *this;
      }

      /// @brief Legt die Fensterposition fest.
      Core& WindowPosition (int x, int y) { window->setPosition(sf::Vector2<int>(x, y)); return *this; }

      /// @brief Legt die Fensterposition fest.
      Core& WindowPosition (const Point<int>& pos) { window->setPosition(pos.AsSFMLVector()); return *this; }

      /// @brief Legt die Fenstergröße fest.
      Core& WindowSize (unsigned int width, unsigned int height) { window->setSize(sf::Vector2<unsigned int>(width, height)); return *this; }

      /// @brief Legt die Fenstergröße fest.
      Core& WindowSize (const Point<unsigned int>& dims) { window->setSize(dims.AsSFMLVector()); return *this; }

      /// @brief Legt fest, ob das Fenster sichtbar sein soll.
      Core& ShowWindow (bool show = true) { window->setVisible(show); return *this; }

      /// @brief Macht das Fenster unsichtbar (es besteht jedoch noch).
      Core& HideWindow () { window->setVisible(false); return *this; }

      /// @brief Legt fest, ob der Mauszeiger sichtbar sein soll.
      Core& ShowMouse (bool show = true) { window->setMouseCursorVisible(show); return *this; }

      /// @brief Macht den Mauszeiger unsichtbar.
      Core& HideMouse () { window->setMouseCursorVisible(false); return *this; }

      /// @brief Legt fest, ob Vertical Sync verwendet werden soll.
      Core& EnableVSync (bool enable = true) { window->setVerticalSyncEnabled(enable); return *this; }

      /// @brief Schaltet die Verwendung von Vertical Sync ab.
      Core& DisableVSync () { window->setVerticalSyncEnabled(false); return *this; }

      /// @brief Legt fest, ob automatisches Key Repeat verwendet werden soll.
      Core& EnableKeyRepeat (bool enable = true) { window->setKeyRepeatEnabled(enable); return *this; }

      /// @brief Schaltet die Verwendung des automatischen Key Repeat ab.
      Core& DisableKeyRepeat () { window->setKeyRepeatEnabled(false); return *this; }

      /// @brief Legt die Limitierung der Frame-Rate fest (limit > 0) oder
      /// schaltet die Limitierung ab (limit = 0).
      Core& EnableFrameRateLimit (unsigned int limit) { window->setFramerateLimit(limit); return *this; }

      /// @brief Schaltet die Limitierung der Frame-Rate ab.
      Core& DisableFrameRateLimit () { window->setFramerateLimit(0u); return *this; }

      /// @brief Stoppt die Ausführung des Programms, ohne Prozessor-Zeit zu
      /// beanspruchen (z.B. wenn das Fenster keinen Fokus besitzt).
      Core& DoNothing () { sf::sleep(sf::milliseconds(50)); return *this; }

      /// @brief Schließt das Fenster und beendet die Einsatzbereitschaft der
      /// Kernkomponenten.
      Core& Quit () { window->close(); return *this; }


      /// @brief Liefert die Fensterposition.
      const Point<int> WindowPosition () const { return Point<int>(window->getPosition()); }

      /// @brief Liefert die Fenstergröße.
      const Point<unsigned int> WindowSize () const { return Point<unsigned int>(window->getSize()); }

      /// @brief Liefert das Handle des Fensters.
      HWND WindowHandle () const { return window->getSystemHandle(); }

      /// @brief Ermittelt, ob das SFML-RenderWindow aktiviert wurde und
      /// aktuell fehlerfrei arbeitet.
      bool IsRunning () { Update(); return window->isOpen(); }

      /// @brief Ermittelt, ob das SFML-RenderWindow aktuell den Fokus besitzt.
      bool HasFocus () const { return hasFocus; }

      /// @brief Liefert den Pointer zur Kernkomponente für Grafik.
      GraphicsCore* Graphics () { if (graphics == nullptr) Reset(GraphicsInterface); return graphics.get(); }

      /// @brief Liefert den Pointer zur Kernkomponente für Eingabegeräte.
      InputCore* Input () { if (input == nullptr) Reset(InputInterface); return input.get(); }

      /// @brief Liefert den Pointer zur Kernkomponente für Audio.
      AudioCore* Audio () { if (audio == nullptr) Reset(AudioInterface); return audio.get(); }

      /// @brief Liefert den Pointer zur Kernkomponente für Ressourcen.
      ResourcesCore* Resources () { if (resources == nullptr) Reset(ResourcesInterface); return resources.get(); }
   };



   std::unique_ptr<Core> Core::instance = nullptr;

}

