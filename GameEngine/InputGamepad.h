
#pragma once

#include "EventListener.h"

#include "DLL_DEF.h"


namespace ge {

   class EventController;

   /// @brief Input-Klasse für Gamepad-Steuerung. Wird über InputCore::Gamepad()
   /// geliefert.
   class GEDLL InputGamepad : public EventListener
   {
      static const int buttonCount = 32;
      static const int axisCount   = 6;

      std::array<bool, buttonCount> currButtons;
      std::array<bool, buttonCount> prevButtons;

      void Init (EventController* eventCtrl);

      void OnEvent (const irr::SEvent& event);

   public:
      /// @brief Konstruktor. Benötigt den Pointer zu einem validen Objekt vom
      /// Typ ge::EventController (wird automatisch bei der Initialisierung über
      /// Core übergeben).
      InputGamepad (EventController* eventCtrl);

      /// @brief Destruktor.
      virtual ~InputGamepad ();


      /// @brief Aktualisiert den Eingabestatus und stellt Abweichungen vom
      /// vorigen Status fest. Muss bei jedem Durchlauf aufgerufen werden,
      /// damit die Eingaben korrekt verarbeitet werden können.
      void Update ();


      /// @brief Ermittelt, ob ein Button gehalten wird.
      ///
      /// Im Gegensatz zu ButtonPressed() ist dieser Status immer _true_,
      /// solange der Button gehalten wird.
      /// @param btn NONE = keiner, ANY = beliebig; Nummer 0 - 31
      /// (Standard: ANY)
      bool Button (int btn = ANY);

      /// @brief Ermittelt, ob gerade ein Button gedrückt wurde.
      ///
      /// Im Gegensatz zu Button() ist dieser Status nur im Moment des
      /// Herunterdrückens _true_, nach dem nächsten Aufruf von Update()
      /// allerdings wieder _false_.
      /// @param btn NONE = keiner, ANY = beliebig; Nummer 0 - 31
      /// (Standard: ANY)
      bool ButtonPressed (int btn = ANY);

      /// @brief Ermittelt, ob gerade ein Button losgelassen wurde.
      ///
      /// Dieser Status ist nur im Moment des Loslassens _true_, nach dem
      /// nächsten Aufruf von Update() allerdings wieder _false_.
      /// @param btn NONE = keiner, ANY = beliebig; Nummer 0 - 31
      /// (Standard: ANY)
      bool ButtonReleased (int btn = ANY);
   };

}

