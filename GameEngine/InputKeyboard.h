
#pragma once

#include <SFML/Window/Event.hpp>

#include "EventListener.h"

#include "DLL_DEF.h"

namespace sf {
   class Event;
}


namespace ge {

   class EventController;

   /// @brief Input-Klasse f�r Taststur-Eingaben. Wird �ber
   /// InputCore::Keyboard() geliefert.
   class GEDLL InputKeyboard : public EventListener
   {
   public:
      enum KeyType {
         Key_None  =  -2,
         Key_Any   =  -1,
         Key_Count = sf::Keyboard::KeyCount
      };

   private:
      std::array<bool, Key_Count> currKeys;
      std::array<bool, Key_Count> prevKeys;

      bool OnEvent (const sf::Event& event) override;

   public:
      /// @brief Konstruktor. Ben�tigt den Pointer zu einem validen Objekt vom
      /// Typ ge::EventController (wird automatisch bei der Initialisierung
      /// �ber Core �bergeben).
      InputKeyboard (EventController* eventCtrl);

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
      /// @param key Key_None = keine, Key_Any = beliebig; Nummer 0 - 255
      /// (Standard: Key_Any)
      bool Key (int key = Key_Any);

      /// @brief Ermittelt, ob gerade eine Taste gedr�ckt wurde.
      ///
      /// Im Gegensatz zu Key() ist dieser Status nur im Moment des
      /// Herunterdr�ckens _true_, nach dem n�chsten Aufruf von Update()
      /// allerdings wieder _false_.
      /// @param key Key_None = keine, Key_Any = beliebig; Nummer 0 - 255
      /// (Standard: Key_Any)
      bool KeyPressed (int key = Key_Any);

      /// @brief Ermittelt, ob gerade eine Taste losgelassen wurde.
      ///
      /// Dieser Status ist nur im Moment des Loslassens _true_, nach dem
      /// n�chsten Aufruf von Update() allerdings wieder _false_.
      /// @param key Key_None = keine, Key_Any = beliebig; Nummer 0 - 255
      /// (Standard: Key_Any)
      bool KeyReleased (int key = Key_Any);
   };

}

