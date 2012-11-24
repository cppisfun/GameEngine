
#pragma once

#include "EventReceiver.h"

#include "DLL_DEF.h"

namespace OIS {
   class InputManager;
   class Keyboard;
}


namespace ge {

   /// @brief Input-Klasse für Taststur-Eingaben. Wird über InputCore::Keyboard()
   /// geliefert.
   class GEDLL InputKeyboard : public EventReceiver
   {
   public:
      enum KeyType {
         Key_None  =  -2,
         Key_Any   =  -1,
         Key_Count = 256
      };

   private:
      OIS::InputManager* input;
      OIS::Keyboard*     device;

      std::array<char, Key_Count> currKeys;
      std::array<char, Key_Count> prevKeys;

      void Init (OIS::InputManager* inputManager);

   public:
      /// @brief Konstruktor. Benötigt den Pointer zu einem validen Objekt vom
      /// Typ OIS::InputManager (wird automatisch bei der Initialisierung über
      /// Core übergeben).
      InputKeyboard (OIS::InputManager* inputManager);

      /// @brief Destruktor.
      virtual ~InputKeyboard ();

      /// @brief Aktualisiert den Eingabestatus und stellt Abweichungen vom
      /// vorigen Status fest. Muss bei jedem Durchlauf aufgerufen werden,
      /// damit die Eingaben korrekt verarbeitet werden können.
      void Update () override;


      /// @brief Ermittelt, ob eine Taste gehalten wird.
      ///
      /// Im Gegensatz zu KeyPressed() ist dieser Status immer _true_, solange
      /// die Taste gehalten wird.
      /// @param key None = keine, Any = beliebig; Nummer 0 - 255
      /// (Standard: Any)
      bool Key (int key = Key_Any);

      /// @brief Ermittelt, ob gerade eine Taste gedrückt wurde.
      ///
      /// Im Gegensatz zu Key() ist dieser Status nur im Moment des
      /// Herunterdrückens _true_, nach dem nächsten Aufruf von Update()
      /// allerdings wieder _false_.
      /// @param key None = keine, Any = beliebig; Nummer 0 - 255
      /// (Standard: Any)
      bool KeyPressed (int key = Key_Any);

      /// @brief Ermittelt, ob gerade eine Taste losgelassen wurde.
      ///
      /// Dieser Status ist nur im Moment des Loslassens _true_, nach dem
      /// nächsten Aufruf von Update() allerdings wieder _false_.
      /// @param key None = keine, Any = beliebig; Nummer 0 - 255
      /// (Standard: Any)
      bool KeyReleased (int key = Key_Any);
   };

}

