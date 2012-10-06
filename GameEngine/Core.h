
#pragma once

#include <irrlicht.h>

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
      static Core* instance;

      std::unique_ptr<irr::IrrlichtDevice> device;
      std::unique_ptr<EventController> eventController;
      bool resizableWindow;

      std::unique_ptr<GraphicsCore>  graphics;
      std::unique_ptr<InputCore>     input;
      std::unique_ptr<AudioCore>     audio;
      std::unique_ptr<ResourcesCore> resources;

      Core ();
      Core (const Core&);
      Core& operator= (const Core&);

      void Init ();

   public:
      /// @brief Destruktor. Entfernt automatisch alle noch bestehenden
      /// Kernkomponenten und gibt Ressourcen frei, die innerhalb von Core
      /// oder eines in Core gehaltenen Kernobjektes erreichbar sind.
      ~Core ();

      /// @brief Liefert den Pointer zum Core-Objekt. Beim ersten Aufruf wird
      /// dieses erstellt, alle Aufrufe liefern dieses einzelne Objekt zurück.
      static Core* Instance ()
      {
         if (!instance) instance = new Core;
         return instance;
      }


      /// @brief Setzt eine oder mehrere Kernkomponenten zurück. Dies beinhaltet
      /// die Freigabe der Ressourcen, die in den entsprechenden Komponenten
      /// gehalten werden.
      /// @param what Komponentenangabe aus Core::What
      Core& Reset (const What& what)
      {
         if (what & GraphicsInterface)  graphics.reset(new GraphicsCore(device.get()));
         if (what & InputInterface)     input.reset(new InputCore(device.get(), eventController.get()));
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
      Core& WindowTitle (const std::string& title);

      /// @brief Legt fest, ob die Fenstergröße verändert werden kann.
      /// @param resizable Gibt an, ob die Größenänderung möglich ist (Standard: true)
      Core& ResizableWindow (bool resizable = true) { device->setResizable(resizable); return *this; }

      /// @brief Legt fest, dass die Fenstergröße nicht geändert werden kann.
      Core& StaticWindow () { device->setResizable(false); return *this; }

      /// @brief Minimiert das Fenster.
      Core& MinimizeWindow () { device->minimizeWindow(); return *this; }

      /// @brief Maximiert das Fenster.
      Core& MaximizeWindow () { device->maximizeWindow(); return *this; }

      /// @brief Stellt das Fenster wieder her.
      Core& RestoreWindow () { device->restoreWindow(); return *this; }


      /// @brief Leert den Puffer der Systemnachrichten an die Anwendung.
      Core& ClearSystemMessages () { device->clearSystemMessages(); return *this; }

      /// @brief Signalisiert, dass das irrlicht-Device aktuell keine Rechenzeit benötigt.
      Core& DoNothing () { device->yield(); return *this; }

      /// @brief Schließt das irrlicht-Device.
      Core& Quit () { device->closeDevice(); return *this; }


      /// @brief Liefert den Pointer zur Kernkomponente für Grafik.
      GraphicsCore* Graphics () { if (graphics == nullptr) Reset(GraphicsInterface); return graphics.get(); }

      /// @brief Liefert den Pointer zur Kernkomponente für Eingabegeräte.
      InputCore* Input () { if (input == nullptr) Reset(InputInterface); return input.get(); }

      /// @brief Liefert den Pointer zur Kernkomponente für Audio.
      AudioCore* Audio () { if (audio == nullptr) Reset(AudioInterface); return audio.get(); }

      /// @brief Liefert den Pointer zur Kernkomponente für Ressourcen.
      ResourcesCore* Resources () { if (resources == nullptr) Reset(ResourcesInterface); return resources.get(); }

      /// @brief Liefert den Pointer zum irrlicht-Device.
      irr::IrrlichtDevice* Device () { return device.get(); }


      /// @brief Ermittelt, ob das irrlicht-Device aktiviert wurde und aktuell fehlerfrei arbeitet.
      bool IsRunning () const { return device->run(); }

      /// @brief Ermittelt, ob die Anwendung im Fullscreen-Modus ausgeführt wird.
      bool IsFullscreen () const { return device->isFullscreen(); }

      /// @brief Ermittelt, ob das Fenster aktiviert ist.
      bool IsWindowActive () const { return device->isWindowActive(); }

      /// @brief Ermittelt, ob das Fenster den Fokus besitzt
      bool IsWindowFocused () const { return device->isWindowFocused(); }

      /// @brief Ermittelt, ob die Fenstergröße geändert werden kann.
      bool IsWindowResizable () const { return resizableWindow; }

      /// @brief Ermittelt, ob das Fenster minimiert ist.
      bool IsWindowMinimized () const { return device->isWindowMinimized(); }
   };


   Core* Core::instance = nullptr;

}

