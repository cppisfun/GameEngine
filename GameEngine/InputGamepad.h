
#pragma once

#include "DLL_DEF.h"

#include "EventReceiver.h"

namespace OIS {
   class InputManager;
   class JoyStick;
}


namespace ge {

   /// @brief Input-Klasse für Gamepad-Steuerung. Wird über InputCore::Gamepad()
   /// geliefert.
   class GEDLL InputGamepad : public EventReceiver
   {
      std::unique_ptr<OIS::JoyStick> device;

      void Init (OIS::InputManager* input);

   public:
      /// @brief Konstruktor. Benötigt den Pointer zu einem validen Objekt vom
      /// Typ OIS::InputManager (wird automatisch bei der Initialisierung über
      /// Core übergeben).
      InputGamepad (OIS::InputManager* input);

      /// @brief Destruktor.
      virtual ~InputGamepad ();

      /// @brief Aktualisiert den Eingabestatus und stellt Abweichungen vom
      /// vorigen Status fest. Muss bei jedem Durchlauf aufgerufen werden,
      /// damit die Eingaben korrekt verarbeitet werden können.
      void Update () override;
   };

}

