
#pragma once

#include "EventReceiver.h"
#include "Point.h"

#include "DLL_DEF.h"

namespace OIS {
   class InputManager;
   class Mouse;
}


namespace ge {

   /// @brief Input-Klasse für Maus-Steuerung. Wird über InputCore::Mouse()
   /// geliefert.
   class GEDLL InputMouse : public EventReceiver
   {
   public:
      enum DirectionType {
         Direction_Any        = -1,
         Direction_None       =  0,
         Direction_Left       =  1,
         Direction_Right      =  2,
         Direction_Horizontal =  3,
         Direction_Up         =  4,
         Direction_Down       =  8,
         Direction_Vertical   = 12
      };

      enum ButtonType {
         Button_None   = -2,
         Button_Any    = -1,
         Button_Left   =  0,
         Button_Right  =  1,
         Button_Middle =  2,
         Button_Extra1 =  3,
         Button_Extra2 =  4,
         Button_Extra3 =  5,
         Button_Extra4 =  6,
         Button_Extra5 =  7,
         Button_Count  =  8
      };

   private:
      OIS::InputManager* input;
      OIS::Mouse*        device;

      Point currPosition;
      Point prevPosition;
      int   currWheelPosition;
      int   prevWheelPosition;

      std::array<bool, Button_Count> currButtons;
      std::array<bool, Button_Count> prevButtons;

      void Init (OIS::InputManager* inputManager);

   public:
      /// @brief Konstruktor. Benötigt den Pointer zu einem validen Objekt vom
      /// Typ OIS::InputManager (wird automatisch bei der Initialisierung über
      /// Core übergeben).
      InputMouse (OIS::InputManager* inputManager);

      /// @brief Destruktor.
      virtual ~InputMouse ();

      /// @brief Aktualisiert den Eingabestatus und stellt Abweichungen vom
      /// vorigen Status fest. Muss bei jedem Durchlauf aufgerufen werden,
      /// damit die Eingaben korrekt verarbeitet werden können.
      void Update () override;


      /// @brief Liefert die X-Position.
      int X () const { return currPosition.X(); }

      /// @brief Liefert die Y-Position.
      int Y () const { return currPosition.Y(); }

      /// @brief Liefert die Mausposition als ge::Point.
      const Point& Position () const { return currPosition; }

      /// @brief Liefert die Position des Mausrades.
      int Wheel () const { return currWheelPosition; }

      /// @brief Liefert die Positionsänderung in X-Richtung seit dem letzten
      /// Aufruf von Update().
      int DX () const { return currPosition.X() - prevPosition.X(); }

      /// @brief Liefert die Positionsänderung in Y-Richtung seit dem letzten
      /// Aufruf von Update().
      int DY () const { return currPosition.Y() - prevPosition.Y(); }

      /// @brief Liefert die Positionsänderung des Mausrades seit dem letzten
      /// Aufruf von Update().
      int DWheel () const { return currWheelPosition - prevWheelPosition; }


      /// @brief Ermittelt, ob die Maus seit dem letzten Update()-Aufruf
      /// bewegt wurde (und ggf. in welche Richtung).
      /// @param direction NoDirection = keine, AnyDirection = beliebig,
      /// Left, Right, Up, Down, Horizontal, Vertical (Standard: AnyDirection)
      bool Moved (int direction = Direction_Any);

      /// @brief Ermittelt, ob das Mausrad seit dem letzten Update()-Aufruf
      /// bewegt wurde (und ggf. in welche Richtung).
      /// @param direction NoDirection = keine, AnyDirection = beliebig,
      /// Up = nach oben / vom Benutzer weg, Down = nach unten / zum Benutzer
      /// hin (Standard: AnyDirection)
      bool WheelMoved (int direction = Direction_Any);


      /// @brief Ermittelt, ob ein Button gehalten wird.
      ///
      /// Im Gegensatz zu ButtonPressed() ist dieser Status immer _true_,
      /// solange der Button gehalten wird.
      /// @param btn None = keiner, Any = beliebig; Nummer 0 - 7
      /// (Standard: Any)
      bool Button (int btn = Button_Any);

      /// @brief Ermittelt, ob gerade ein Button gedrückt wurde.
      ///
      /// Im Gegensatz zu Button() ist dieser Status nur im Moment des
      /// Herunterdrückens _true_, nach dem nächsten Aufruf von Update()
      /// allerdings wieder _false_.
      /// @param btn None = keiner, Any = beliebig; Nummer 0 - 7
      /// (Standard: Any)
      bool ButtonPressed (int btn = Button_Any);

      /// @brief Ermittelt, ob gerade eine Taste losgelassen wurde.
      ///
      /// Dieser Status ist nur im Moment des Loslassens _true_, nach dem
      /// nächsten Aufruf von Update() allerdings wieder _false_.
      /// @param btn None = keiner, Any = beliebig; Nummer 0 - 7
      /// (Standard: Any)
      bool ButtonReleased (int btn = Button_Any);
   };

}


/*
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

      std::array<ButtonClickState, BUTTON_COUNT> buttonClickStates;

   public:
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

*/