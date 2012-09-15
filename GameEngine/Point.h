
#pragma once

#include "Precomp.h"

#include <vector2d.h>

#include "DLL_DEF.h"


namespace ge {

   class GEDLL Point
   {
      int x;
      int y;

   public:
      Point (int x, int y) : x(x), y(y) { }
      Point (const irr::core::vector2d<int>& vec) : x(vec.X), y(vec.Y) { }

      Point& X (int val)              { x = val; return *this; }
      Point& Y (int val)              { y = val; return *this; }
      Point& Set (int xVal, int yVal) { x = xVal; y = yVal; return *this; }

      Point& FromIrrVector (const irr::core::vector2d<int>& vec) { return Set(vec.X, vec.Y); }

      int X () const { return x; }
      int Y () const { return y; }

      const irr::core::vector2d<int> AsIrrVector () const { return irr::core::vector2d<int>(x, y); }
   };

}

