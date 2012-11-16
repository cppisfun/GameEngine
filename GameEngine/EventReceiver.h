
#pragma once

#include "DLL_DEF.h"


namespace ge {

   /// @ brief Interface für alle Klassen, die Events verarbeiten. Dient der
   /// Einhaltung einer einheitlichen Schnittstelle.
   class GEDLL EventReceiver
   {
      bool enabled;

      /// @brief Aktualisieren des Objektes. Muss in allen abgeleiteten Klassen
      /// implementiert werden.
      virtual void Update () = 0;

   public:
      /// @brief Konstruktor. Das Verarbeiten von Events ist nach Anlegen eines
      /// Objektes automatisch aktiviert. Dieser Status kann mit Enable() bzw.
      /// Disable() jederzeit geändert werden.
      EventReceiver () : enabled(true) { }

      /// @brief Aktiviert bzw. Deaktiviert das Verarbeiten von Events.
      void Enable (bool enable = true) { enabled = enable; }

      /// @brief Deaktiviert das Verarbeiten von Events.
      void Disable () { enabled = false; }

      /// @brief Gibt an, ob aktuell eingehende Events verarbeitet werden.
      bool Enabled () { return enabled; }
   };

}

