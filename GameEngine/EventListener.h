
#pragma once

#include <IEventReceiver.h>

#include "DLL_DEF.h"


namespace ge {

   /// @brief Oberklasse für Event-Listener. Alle Klassen, die ihre Events von
   /// ge::EventController erhalten, müssen von EventListener abgeleitet werden.
   class GEDLL EventListener
   {
      bool enabled;

      virtual void OnEvent (const irr::SEvent& event) = 0;
      virtual void Update () = 0;

   public:
      /// @brief Konstruktor. Schaltet automatisch die Event-Bearbeitung ein.
      EventListener () : enabled(true) { }

      /// @brief Destruktor.
      virtual ~EventListener () { }


      /// @brief Legt fest, ob dieser Listener aktuell auf Events reagieren
      /// soll.
      void Enable (bool enable) { enabled = enable; }

      /// @brief Schaltet die Event-Bearbeitung aus. Events können zwar
      /// weiterhin an den Listener gesendet werden, es erfolgt aber keine
      /// Reaktion vom Listener.
      void Disable () { enabled = false; }


      /// @brief Ermittelt, ob der Listener aktuell auf Events reagiert oder die
      /// empfangenen Events ignoriert.
      bool Enabled () const { return enabled; }
   };

}

