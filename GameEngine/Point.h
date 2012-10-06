
#pragma once

#include "Precomp.h"

#include <vector2d.h>

#include "DLL_DEF.h"


namespace ge {

   /// @brief Standard-Klasse für Punkte (Koordinaten).
   class GEDLL Point
   {
      int x;
      int y;

   public:
      /// @brief Konstruktor. Initialisierung über Zahlenangaben.
      Point (int x, int y) : x(x), y(y) { }

      /// @brief Konstruktor. Initialisierung über einen irrlicht-Vektor.
      Point (const irr::core::vector2d<int>& vec) : x(vec.X), y(vec.Y) { }


      /// @brief Legt die X-Position fest.
      Point& X (int val) { x = val; return *this; }

      /// @brief Legt die Y-Position fest.
      Point& Y (int val) { y = val; return *this; }

      /// @brief Legt die Position über Zahlenwerte fest.
      Point& Set (int xVal, int yVal) { x = xVal; y = yVal; return *this; }

      /// @brief Left die Position über einen irrlicht-Vektor fest.
      Point& FromIrrVector (const irr::core::vector2d<int>& vec) { return Set(vec.X, vec.Y); }


      /// @brief Liefert die X-Position.
      int X () const { return x; }

      /// @brief Liefert die Y-Position.
      int Y () const { return y; }


      /// @brief Liefert einen entsprechenden irrlicht-Vektor.
      const irr::core::vector2d<int> AsIrrVector () const { return irr::core::vector2d<int>(x, y); }
   };

}

