
#pragma once

#include <Keycodes.h>

#include "EventListener.h"

#include "DLL_DEF.h"


namespace ge {

   class EventController;

   /// @brief Input-Klasse für Tastatureingaben. Wird über InputCore::Keyboard()
   /// geliefert.
   class GEDLL InputKeyboard : public EventListener
   {
      std::array<bool, irr::KEY_KEY_CODES_COUNT> currKeys;
      std::array<bool, irr::KEY_KEY_CODES_COUNT> prevKeys;

      void Init (EventController* eventCtrl);

      void OnEvent (const irr::SEvent& event) override;

   public:
      /// @brief Konstruktor. Benötigt den Pointer zu einem validen Objekt vom
      /// Typ ge::EventController (wird automatisch bei der Initialisierung über
      /// Core übergeben).
      InputKeyboard (EventController* eventCtrl);

      /// @brief Destruktor.
      virtual ~InputKeyboard ();


      /// @brief Aktualisiert den Eingabestatus und stellt Abweichungen vom
      /// vorigen Status fest. Muss bei jedem Durchlauf aufgerufen werden,
      /// damit die Eingaben korrekt verarbeitet werden können.
      void Update ();


      /// @brief Ermittelt, ob eine Taste gehalten wird.
      ///
      /// Im Gegensatz zu KeyPressed() ist dieser Status immer _true_, solange
      /// die Taste gehalten wird.
      /// @param key NONE = keine, ANY = beliebig; Nummer 0 - 255
      /// (Standard: ANY)
      bool Key (int key = ANY);

      /// @brief Ermittelt, ob gerade eine Taste gedrückt wurde.
      ///
      /// Im Gegensatz zu Key() ist dieser Status nur im Moment des
      /// Herunterdrückens _true_, nach dem nächsten Aufruf von Update()
      /// allerdings wieder _false_.
      /// @param key NONE = keine, ANY = beliebig; Nummer 0 - 255
      /// (Standard: ANY)
      bool KeyPressed (int key = ANY);

      /// @brief Ermittelt, ob gerade eine Taste losgelassen wurde.
      ///
      /// Dieser Status ist nur im Moment des Loslassens _true_, nach dem
      /// nächsten Aufruf von Update() allerdings wieder _false_.
      /// @param key NONE = keine, ANY = beliebig; Nummer 0 - 255
      /// (Standard: ANY)
      bool KeyReleased (int key = ANY);
   };

}

