
#pragma once

#include "EventReceiver.h"

#include "DLL_DEF.h"

namespace OIS {
   class InputManager;
   class Keyboard;
}


namespace ge {

   /// @brief Input-Klasse f�r Taststur-Eingaben. Wird �ber InputCore::Keyboard()
   /// geliefert.
   class GEDLL InputKeyboard : public EventReceiver
   {
      class EventHandler;

   public:
      enum KeyType {
         None     = -2,
         Any      = -1,
         KeyCount = 256
      };

   private:
      std::unique_ptr<EventHandler>  eventHandler;
      std::unique_ptr<OIS::Keyboard> device;

      std::array<char, 256> currKeys;
      std::array<char, 256> prevKeys;

      void Init (OIS::InputManager* input);

   public:
      /// @brief Konstruktor. Ben�tigt den Pointer zu einem validen Objekt vom
      /// Typ OIS::InputManager (wird automatisch bei der Initialisierung �ber
      /// Core �bergeben).
      InputKeyboard (OIS::InputManager* input);

      /// @brief Destruktor.
      virtual ~InputKeyboard ();

      /// @brief Aktualisiert den Eingabestatus und stellt Abweichungen vom
      /// vorigen Status fest. Muss bei jedem Durchlauf aufgerufen werden,
      /// damit die Eingaben korrekt verarbeitet werden k�nnen.
      void Update () override;


      /// @brief Ermittelt, ob eine Taste gehalten wird.
      ///
      /// Im Gegensatz zu KeyPressed() ist dieser Status immer _true_, solange
      /// die Taste gehalten wird.
      /// @param key NONE = keine, ANY = beliebig; Nummer 0 - 255
      /// (Standard: ANY)
      bool Key (int key = Any);

      /// @brief Ermittelt, ob gerade eine Taste gedr�ckt wurde.
      ///
      /// Im Gegensatz zu Key() ist dieser Status nur im Moment des
      /// Herunterdr�ckens _true_, nach dem n�chsten Aufruf von Update()
      /// allerdings wieder _false_.
      /// @param key NONE = keine, ANY = beliebig; Nummer 0 - 255
      /// (Standard: ANY)
      bool KeyPressed (int key = Any);

      /// @brief Ermittelt, ob gerade eine Taste losgelassen wurde.
      ///
      /// Dieser Status ist nur im Moment des Loslassens _true_, nach dem
      /// n�chsten Aufruf von Update() allerdings wieder _false_.
      /// @param key NONE = keine, ANY = beliebig; Nummer 0 - 255
      /// (Standard: ANY)
      bool KeyReleased (int key = Any);
   };

}

