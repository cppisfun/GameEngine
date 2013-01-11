
#pragma once

#include "DLL_DEF.h"

namespace sf {
   class Event;
}


namespace ge {

   /// @ brief Interface für alle Klassen, die Events vom Typ sf::Event
   /// verarbeiten. Alle Klassen, die ihre Events von ge::EventController
   /// erhalten, müssen von EventListener abgeleitet werden.
   class GEDLL EventListener
   {
      bool enabled;

      /// @brief Verarbeiten von eingehenden Events. Muss in allen abgeleiteten
      /// Klassen implementiert werden.
      virtual bool OnEvent (const sf::Event& event) = 0;

      /// @brief Aktualisieren des Objektes. Muss in allen abgeleiteten Klassen
      /// implementiert werden.
      virtual void Update () = 0;

   public:
      /// @brief Konstruktor. Das Verarbeiten von Events ist nach Anlegen eines
      /// Objektes automatisch aktiviert. Dieser Status kann mit Enable() bzw.
      /// Disable() jederzeit geändert werden.
      EventListener () : enabled(true) { }

      /// @brief Aktiviert bzw. Deaktiviert das Verarbeiten von Events.
      void Enable (bool enable = true) { enabled = enable; }

      /// @brief Deaktiviert das Verarbeiten von Events.
      void Disable () { enabled = false; }

      /// @brief Gibt an, ob aktuell eingehende Events verarbeitet werden.
      bool Enabled () const { return enabled; }
   };

}

