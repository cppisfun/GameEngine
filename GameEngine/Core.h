
#pragma once

#include <SFML/Graphics.hpp>

#include "GraphicsCore.h"
#include "InputCore.h"
#include "AudioCore.h"
#include "ResourcesCore.h"

#include "DLL_DEF.h"

class EventController;


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
   class GEDLL Core
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

      sf::RenderWindow window;

      std::unique_ptr<EventController> eventController;
      std::unique_ptr<GraphicsCore>    graphics;
      std::unique_ptr<InputCore>       input;
      std::unique_ptr<AudioCore>       audio;
      std::unique_ptr<ResourcesCore>   resources;

      Core ();
      Core (const Core&);
      Core& operator= (const Core&);

      void Update ()
      {
         sf::Event event;
         if (window.GetEvent(event)) eventController->Event(event);
      }

   public:
      /// @brief Destruktor. Entfernt automatisch alle noch bestehenden
      /// Kernkomponenten und gibt Ressourcen frei, die innerhalb von Core
      /// oder eines in Core gehaltenen Kernobjektes erreichbar sind.
      ~Core ()
      {
         ShutDown(AllInterfaces);
         if (window.IsOpened()) window.Close();
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
         if (what & GraphicsInterface)  graphics.reset(new GraphicsCore(nullptr));
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


      /// @brief Legt fest, ob das Fenster sichtbar sein soll.
      Core& ShowWindow (bool show = true) { window.Show(show); return *this; }

      /// @brief Macht das Fenster unsichtbar (es besteht jedoch noch).
      Core& HideWindow () { window.Show(false); return *this; }

      /// @brief Schließt das irrlicht-Device.
      Core& Quit () { window.Close(); return *this; }


      /// @brief Liefert den Pointer zur Kernkomponente für Grafik.
      GraphicsCore* Graphics () { if (graphics == nullptr) Reset(GraphicsInterface); return graphics.get(); }

      /// @brief Liefert den Pointer zur Kernkomponente für Eingabegeräte.
      InputCore* Input () { if (input == nullptr) Reset(InputInterface); return input.get(); }

      /// @brief Liefert den Pointer zur Kernkomponente für Audio.
      AudioCore* Audio () { if (audio == nullptr) Reset(AudioInterface); return audio.get(); }

      /// @brief Liefert den Pointer zur Kernkomponente für Ressourcen.
      ResourcesCore* Resources () { if (resources == nullptr) Reset(ResourcesInterface); return resources.get(); }


      /// @brief Ermittelt, ob das irrlicht-Device aktiviert wurde und aktuell fehlerfrei arbeitet.
      bool IsRunning ()
      {
         Update();
         return window.IsOpened();
      }
   };



   std::unique_ptr<Core> Core::instance = nullptr;

}

