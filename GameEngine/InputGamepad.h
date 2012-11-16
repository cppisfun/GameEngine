
#pragma once

#include "DLL_DEF.h"

#include "EventReceiver.h"

namespace OIS {
   class InputManager;
   class JoyStick;
}


namespace ge {

   /// @brief Input-Klasse f�r Gamepad-Steuerung. Wird �ber InputCore::Gamepad()
   /// geliefert.
   class GEDLL InputGamepad : public EventReceiver
   {
      std::unique_ptr<OIS::JoyStick> device;

      void Init (OIS::InputManager* input);

   public:
      /// @brief Konstruktor. Ben�tigt den Pointer zu einem validen Objekt vom
      /// Typ OIS::InputManager (wird automatisch bei der Initialisierung �ber
      /// Core �bergeben).
      InputGamepad (OIS::InputManager* input);

      /// @brief Destruktor.
      virtual ~InputGamepad ();

      /// @brief Aktualisiert den Eingabestatus und stellt Abweichungen vom
      /// vorigen Status fest. Muss bei jedem Durchlauf aufgerufen werden,
      /// damit die Eingaben korrekt verarbeitet werden k�nnen.
      void Update () override;
   };

}

