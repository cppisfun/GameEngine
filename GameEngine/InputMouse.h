
#pragma once

#include "EventListener.h"
#include "Point.h"

#include "DLL_DEF.h"

union SDL_Event;
struct SDL_Window;


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
      SDL_Window* window;

      Point<int> currPosition;
      Point<int> prevPosition;
      int        currWheelPosition;
      int        prevWheelPosition;

      std::array<bool, Button_Count> currButtons;
      std::array<bool, Button_Count> prevButtons;

      bool OnEvent (const SDL_Event& event) override;

   public:
      InputMouse (EventController* eventCtrl, SDL_Window* window);
      virtual ~InputMouse ();

      void Update () override;

      InputMouse& Position (const Point<int>& position);
      InputMouse& Show (bool show = true);
      InputMouse& Hide ();

      int X () const                      { return currPosition.X(); }
      int Y () const                      { return currPosition.Y(); }
      const Point<int>& Position () const { return currPosition; }
      int Wheel () const                  { return currWheelPosition; }
      int DX () const                     { return currPosition.X() - prevPosition.X(); }
      int DY () const                     { return currPosition.Y() - prevPosition.Y(); }
      int DWheel () const                 { return currWheelPosition - prevWheelPosition; }

      bool Moved (int direction = Direction_Any) const;
      bool WheelMoved (int direction = Direction_Any) const;

      bool Button (int btn = Button_Any) const;
      bool ButtonPressed (int btn = Button_Any) const;
      bool ButtonReleased (int btn = Button_Any) const;

      bool Visible () const;
   };

}

