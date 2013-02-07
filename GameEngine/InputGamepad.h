
#pragma once

#include <SFML/Window/Event.hpp>

#include "EventListener.h"

#include "DLL_DEF.h"

namespace sf {
   class Event;
}


namespace ge {

   class EventController;

   /// @brief Input-Klasse für Gamepad-Steuerung. Wird über
   /// InputCore::Gamepad() geliefert.
   class GEDLL InputGamepad : public EventListener
   {
   public:
      enum ButtonType {
         Button_None  = -2,
         Button_Any   = -1,
         Button_Count = sf::Joystick::ButtonCount
      };

   private:
      std::array<bool, Button_Count> currButtons;
      std::array<bool, Button_Count> prevButtons;

      bool OnEvent (const sf::Event& event) override;

   public:
      /// @brief Konstruktor. Benötigt den Pointer zu einem validen Objekt vom
      /// Typ ge::EventController (wird automatisch bei der Initialisierung
      /// über Core übergeben).
      InputGamepad (EventController* eventCtrl);

      /// @brief Destruktor.
      virtual ~InputGamepad ();


      /// @brief Aktualisiert den Eingabestatus und stellt Abweichungen vom
      /// vorigen Status fest. Muss bei jedem Durchlauf aufgerufen werden,
      /// damit die Eingaben korrekt verarbeitet werden können.
      void Update () override;


      /// @brief Ermittelt, ob ein Button gehalten wird.
      ///
      /// Im Gegensatz zu ButtonPressed() ist dieser Status immer _true_,
      /// solange die Taste gehalten wird.
      /// @param btn Button_None = keine, Button_Any = beliebig; Nummer 0 - 31
      /// (Standard: Button_Any)
      bool Button (int btn = Button_Any);

      /// @brief Ermittelt, ob gerade ein Button gedrückt wurde.
      ///
      /// Im Gegensatz zu Key() ist dieser Status nur im Moment des
      /// Herunterdrückens _true_, nach dem nächsten Aufruf von Update()
      /// allerdings wieder _false_.
      /// @param btn Button_None = keine, Button_Any = beliebig; Nummer 0 - 31
      /// (Standard: Button_Any)
      bool ButtonPressed (int btn = Button_Any);

      /// @brief Ermittelt, ob gerade eine Taste losgelassen wurde.
      ///
      /// Dieser Status ist nur im Moment des Loslassens _true_, nach dem
      /// nächsten Aufruf von Update() allerdings wieder _false_.
      /// @param btn Button_None = keine, Button_Any = beliebig; Nummer 0 - 31
      /// (Standard: Button_Any)
      bool ButtonReleased (int btn = Button_Any);
   };

}

