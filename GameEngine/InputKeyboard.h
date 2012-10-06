
#pragma once

#include <Keycodes.h>

#include "EventListener.h"

#include "DLL_DEF.h"


namespace ge {

   class EventController;

   /// @brief Input-Klasse f�r Tastatureingaben. Wird �ber InputCore::Keyboard()
   /// geliefert.
   class GEDLL InputKeyboard : public EventListener
   {
      std::array<bool, irr::KEY_KEY_CODES_COUNT> currKeys;
      std::array<bool, irr::KEY_KEY_CODES_COUNT> prevKeys;

      void Init (EventController* eventCtrl);

      void OnEvent (const irr::SEvent& event) override;

   public:
      /// @brief Konstruktor. Ben�tigt den Pointer zu einem validen Objekt vom
      /// Typ ge::EventController (wird automatisch bei der Initialisierung �ber
      /// Core �bergeben).
      InputKeyboard (EventController* eventCtrl);

      /// @brief Destruktor.
      virtual ~InputKeyboard ();


      /// @brief Aktualisiert den Eingabestatus und stellt Abweichungen vom
      /// vorigen Status fest. Muss bei jedem Durchlauf aufgerufen werden,
      /// damit die Eingaben korrekt verarbeitet werden k�nnen.
      void Update ();


      /// @brief Ermittelt, ob eine Taste gehalten wird.
      ///
      /// Im Gegensatz zu KeyPressed() ist dieser Status immer _true_, solange
      /// die Taste gehalten wird.
      /// @param key NONE = keine, ANY = beliebig; Nummer 0 - 255
      /// (Standard: ANY)
      bool Key (int key = ANY);

      /// @brief Ermittelt, ob gerade eine Taste gedr�ckt wurde.
      ///
      /// Im Gegensatz zu Key() ist dieser Status nur im Moment des
      /// Herunterdr�ckens _true_, nach dem n�chsten Aufruf von Update()
      /// allerdings wieder _false_.
      /// @param key NONE = keine, ANY = beliebig; Nummer 0 - 255
      /// (Standard: ANY)
      bool KeyPressed (int key = ANY);

      /// @brief Ermittelt, ob gerade eine Taste losgelassen wurde.
      ///
      /// Dieser Status ist nur im Moment des Loslassens _true_, nach dem
      /// n�chsten Aufruf von Update() allerdings wieder _false_.
      /// @param key NONE = keine, ANY = beliebig; Nummer 0 - 255
      /// (Standard: ANY)
      bool KeyReleased (int key = ANY);
   };

}

