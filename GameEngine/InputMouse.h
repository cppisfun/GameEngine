
#pragma once

#include "EventListener.h"

#include "DLL_DEF.h"

namespace irr {
   namespace gui {
      class ICursorControl;
   }
}


namespace ge {

   class EventController;

   /// @brief Input-Klasse für Mauseingaben. Wird über InputCore::Mouse()
   /// geliefert.
   class GEDLL InputMouse : public EventListener
   {
      enum ButtonClickState {
         Nothing = 0,
         ButtonWasPressed,    // only used to determine single clicks
         ButtonClicked,
         ButtonDoubleClicked,
         ButtonTripleClicked
      };

      irr::gui::ICursorControl* cursor;

      int currX, currY;
      int prevX, prevY;
      float currWheel, prevWheel;

      std::array<bool, BUTTON_COUNT> currButtons;
      std::array<bool, BUTTON_COUNT> prevButtons;
      std::array<ButtonClickState, BUTTON_COUNT> buttonClickStates;

      void Init (irr::gui::ICursorControl* cursorCtrl, EventController* eventCtrl);

      void OnEvent (const irr::SEvent& event) override;

   public:
      /// @brief Konstruktor. Benötigt Pointer zu einem validen
      /// irrlicht-Objekt für den Mauszeiger und einem validen Objekt vom Typ
      /// ge::EventController (werden automatisch bei der Initialisierung über
      /// Core übergeben).
      InputMouse (irr::gui::ICursorControl* cursorCtrl, EventController* eventCtrl);

      /// @brief Destruktor.
      virtual ~InputMouse ();


      /// @brief Aktualisiert den Eingabestatus und stellt Abweichungen vom
      /// vorigen Status fest. Muss bei jedem Durchlauf aufgerufen werden,
      /// damit die Eingaben korrekt verarbeitet werden können.
      void Update ();


      /// Legt fest, ob der Mauszeiger angezeigt werden soll.
      /// @param show Gibt an, ob der Mauszeiger sichtbar sein soll (Standard:
      /// true)
      InputMouse& Show (bool show = true) { cursor->setVisible(show); return *this; }

      /// Legt fest, dass der Mauszeiger nicht angezeigt wird.
      InputMouse& Hide () { cursor->setVisible(false); return *this; }

      /// Legt die X-Position fest.
      InputMouse& X (int x);

      /// Legt die Y-Position fest.
      InputMouse& Y (int y);

      /// Legt X- und Y-Position fest.
      InputMouse& Position (int x, int y);


      /// Ermittelt, ob der Mauszeiger sichtbar ist.
      bool IsVisible () const { return cursor->isVisible(); }


      /// Liefert die X-Position.
      int X () const { return currX; }

      /// Liefert die Y-Position.
      int Y () const { return currY; }

      /// Liefert die Position des Mausrades.
      float Wheel () const { return currWheel; }


      /// Liefert die Abweichung in X-Richtung seit dem letzten Update()-Aufruf.
      int DX () const { return currX - prevX; }

      /// Liefert die Abweichung in Y-Richtung seit dem letzten Update()-Aufruf.
      int DY () const { return currY - prevY; }

      /// Liefert die Abweichung der Mausrad-Position seit dem letzten Aufruf
      /// von Update().
      float DWheel () const { return prevWheel - currWheel; }


      /// @brief Ermittelt, ob die Maus seit dem letzten Update()-Aufruf
      /// bewegt wurde (und ggf. in welche Richtung).
      /// @param direction NONE = keine, ANY = beliebig, LEFT, RIGHT, UP, DOWN,
      /// HORIZONTAL, VERTICAL (Standard: ANY)
      bool Moved (int direction = ANY);

      /// @brief Ermittelt, ob das Mausrad seit dem letzten Update()-Aufruf
      /// bewegt wurde (und ggf. in welche Richtung).
      /// @param direction NONE = keine, ANY = beliebig, UP = nach oben / vom
      /// Benutzer weg, DOWN = nach unten / zum Benutzer hin (Standard: ANY)
      bool WheelMoved (int direction = ANY);


      /// @brief Ermittelt, ob ein Button gehalten wird. Im Gegensatz zu
      /// ButtonPressed() ist dieser Status immer _true_, solange der Button
      /// gehalten wird.
      /// @param btn NONE = keiner, ANY = beliebig, LEFT_BUTTON, MIDDLE_BUTTON,
      /// RIGHT_BUTTON (Standard: ANY)
      bool Button (int btn = ANY);

      /// @brief Ermittelt, ob ein Button gerade gedrückt wurde. Im Gegensatz zu
      /// Button() ist dieser Status nur im Moment des Herunterdrückens _true_,
      /// nach dem nächsten Aufruf von Update() allerdings wieder _false_.
      /// @param btn NONE = keiner, ANY = beliebig, LEFT_BUTTON, MIDDLE_BUTTON,
      /// RIGHT_BUTTON (Standard: ANY)
      bool ButtonPressed (int btn = ANY);

      /// @brief Ermittelt, ob ein Button gerade losgelassen wurde. Dieser
      /// Status ist nur im Moment des Loslassens _true_, nach dem nächsten
      /// Aufruf von Update() allerdings wieder _false_.
      /// @param btn NONE = keiner, ANY = beliebig, LEFT_BUTTON, MIDDLE_BUTTON,
      /// RIGHT_BUTTON (Standard: ANY)
      bool ButtonReleased (int btn = ANY);

      /// @brief Ermittelt, ob gerade ein Click erfolgt ist. Dieser Status ist
      /// nur in dem Moment _true_, in welchem der Click vollendet wurde, nach
      /// dem nächsten Aufruf von Update() allerdings wieder _false_.
      /// @param btn NONE = keiner, ANY = beliebig, LEFT_BUTTON, MIDDLE_BUTTON,
      /// RIGHT_BUTTON (Standard: ANY)
      bool Clicked (int btn = ANY);

      /// @brief Ermittelt, ob gerade ein Double-Click erfolgt ist. Dieser
      /// Status ist nur in dem Moment _true_, in welchem der Doppel-Click
      /// vollendet wurde, nach dem nächsten Aufruf von Update() allerdings
      /// wieder _false_.
      /// @param btn NONE = keiner, ANY = beliebig, LEFT_BUTTON, MIDDLE_BUTTON,
      /// RIGHT_BUTTON (Standard: ANY)
      bool DoubleClicked (int btn = ANY);

      /// @brief Ermittelt, ob gerade ein Triple-Click erfolgt ist. Dieser
      /// Status ist nur in dem Moment _true_, in welchem der Triple-Click
      /// vollendet wurde, nach dem nächsten Aufruf von Update() allerdings
      /// wieder _false_.
      /// @param btn NONE = keiner, ANY = beliebig, LEFT_BUTTON, MIDDLE_BUTTON,
      /// RIGHT_BUTTON (Standard: ANY)
      bool TripleClicked (int btn = ANY);
   };

}

