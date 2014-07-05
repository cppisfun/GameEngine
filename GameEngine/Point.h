
#pragma once

#include "Precomp.h"

#include "DLL_DEF.h"


namespace ge {

   template<typename T>
   class GEDLL Point
   {
      T x;
      T y;

      void CheckType () { static_assert(std::is_arithmetic<T>::value, "ge::Point<T> only supports integral or floating point types!"); }

   public:
      Point (T x, T y) { CheckType(); Set(x, y); }

      Point& X (T val)            { x = val; return *this; }
      Point& Y (T val)            { y = val; return *this; }
      Point& Set (T xVal, T yVal) { x = xVal; y = yVal; return *this; }

      T X () const { return x; }
      T Y () const { return y; }

      bool operator== (const Point<T>& other) const { return x == other.X() && y == other.Y(); }
      bool operator!= (const Point<T>& other) const { return x != other.X() || y != other.Y(); }
   };

}

