
#pragma once

#include "EventListener.h"
#include "Point.h"

#include "DLL_DEF.h"


namespace ge {

   class EventController;

   class GEDLL InputMouse : public EventListener
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
         Button_Left   = 0,
         Button_Right  = 1,
         Button_Middle = 2,
         Button_Extra1 = 3,
         Button_Extra2 = 4,
         Button_Count  = 5
      };

   private:
      Point<int> currPosition;
      Point<int> prevPosition;
      int        currWheelPosition;
      int        prevWheelPosition;

      std::array<bool, Button_Count> currButtons;
      std::array<bool, Button_Count> prevButtons;

      bool OnEvent (/*const sf::Event& event*/) override;

   public:
      InputMouse (EventController* eventCtrl);
      virtual ~InputMouse ();

      void Update () override;

      int X () const                      { return currPosition.X(); }
      int Y () const                      { return currPosition.Y(); }
      const Point<int>& Position () const { return currPosition; }
      int Wheel () const                  { return currWheelPosition; }
      int DX () const                     { return currPosition.X() - prevPosition.X(); }
      int DY () const                     { return currPosition.Y() - prevPosition.Y(); }
      int DWheel () const                 { return currWheelPosition - prevWheelPosition; }

      bool Moved (int direction = Direction_Any);
      bool WheelMoved (int direction = Direction_Any);

      bool Button (int btn = Button_Any);
      bool ButtonPressed (int btn = Button_Any);
      bool ButtonReleased (int btn = Button_Any);
   };

}


/*
   class GEDLL InputMouse : public EventListener
   {
      irr::gui::ICursorControl* cursor;

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
   };

}

*/