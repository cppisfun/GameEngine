
#pragma once

#include "EventListener.h"
#include "Position.h"

#include "DLL_DEF.h"

union SDL_Event;
struct _SDL_Joystick; // SDL_Joystick cannot be forwarded directly due to a name clash issue


namespace ge {

   class EventController;

   class GEDLL InputGamepad : public EventListener
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
         Button_None  = -2,
         Button_Any   = -1,
         Button_Count = 8
      };

   private:
      _SDL_Joystick* device;

      Position prevLeftStick;
      Position currLeftStick;

      Position prevRightStick;
      Position currRightStick;

      std::array<bool, Button_Count> currButtons;
      std::array<bool, Button_Count> prevButtons;

      bool OnEvent (const SDL_Event& event) override;

   public:
      InputGamepad (EventController* eventCtrl);
      virtual ~InputGamepad ();

      void Update () override;

      int LeftStickX () const              { return currLeftStick.X(); }
      int LeftStickY () const              { return currLeftStick.Y(); }
      int LeftStickDX () const             { return currLeftStick.X() - prevLeftStick.X(); }
      int LeftStickDY () const             { return currLeftStick.Y() - prevLeftStick.Y(); }
      const Position& LeftStick () const { return currLeftStick; }

      int RightStickX () const              { return currRightStick.X(); }
      int RightStickY () const              { return currRightStick.Y(); }
      int RightStickDX () const             { return currRightStick.X() - prevRightStick.X(); }
      int RightStickDY () const             { return currRightStick.Y() - prevRightStick.Y(); }
      const Position& RightStick () const { return currRightStick; }

      bool LeftStickMoved (int direction = Direction_Any) const;
      bool RightStickMoved (int direction = Direction_Any) const;

      bool Button (int btn = Button_Any) const;
      bool ButtonPressed (int btn = Button_Any) const;
      bool ButtonReleased (int btn = Button_Any) const;
   };

}

