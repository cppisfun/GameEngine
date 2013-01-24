
#pragma once

#include "Precomp.h"

#include <vector2d.h>
#include <SFML/System/Vector2.hpp>

#include "DLL_DEF.h"


namespace ge {

   /// @brief Standard-Klasse f�r Punkte (Koordinaten).
   class GEDLL Point
   {
      int x;
      int y;

   public:
      /// @brief Konstruktor. Initialisierung �ber Zahlenangaben.
      Point (int x, int y) : x(x), y(y) { }

      /// @brief Konstruktor. Initialisierung �ber einen irrlicht-Vektor.
      Point (const irr::core::vector2d<int>& vec) : x(vec.X), y(vec.Y) { }

      /// @brief Konstruktor. Initialisierung �ber einen SFML-Vektor.
      Point (const sf::Vector2<int>& vec) : x(vec.x), y(vec.y) { }


      /// @brief Legt die X-Position fest.
      Point& X (int val) { x = val; return *this; }

      /// @brief Legt die Y-Position fest.
      Point& Y (int val) { y = val; return *this; }

      /// @brief Legt die Position �ber Zahlenwerte fest.
      Point& Set (int xVal, int yVal) { x = xVal; y = yVal; return *this; }

      /// @brief Legt die Position �ber einen irrlicht-Vektor fest.
      Point& FromIrrVector (const irr::core::vector2d<int>& vec) { return Set(vec.X, vec.Y); }

      /// @brief Legt die Position �ber einen SFML-Vektor fest.
      Point& FromSFMLVector (const sf::Vector2<int>& vec) { return Set(vec.x, vec.y); }


      /// @brief Liefert die X-Position.
      int X () const { return x; }

      /// @brief Liefert die Y-Position.
      int Y () const { return y; }


      /// @brief Liefert einen entsprechenden irrlicht-Vektor.
      const irr::core::vector2d<int> AsIrrVector () const { return irr::core::vector2d<int>(x, y); }

      /// @brief Liefert einen entsprechenden SFML-Vektor.
      const sf::Vector2<int> AsSFMLVector () const { return sf::Vector2<int>(x, y); }
   };

}

