
#pragma once

#include "Precomp.h"

#include <SFML/System/Vector2.hpp>

#include "DLL_DEF.h"


namespace ge {

   /// @brief Standard-Klasse für Punkte (Koordinaten).
   template<typename T>
   class GEDLL Point
   {
      T x;
      T y;

      void CheckType () { static_assert(std::is_arithmetic<T>::value, "ge::Point<T> only supports integral or floating point types!"); }

   public:
      /// @brief Konstruktor. Initialisierung über Zahlenangaben.
      Point (T x, T y) : x(x), y(y) { CheckType(); }

      /// @brief Konstruktor. Initialisierung über einen SFML-Vektor.
      Point (const sf::Vector2<T>& vec) : x(vec.x), y(vec.y) { CheckType(); }


      /// @brief Legt die X-Position fest.
      Point& X (T val) { x = val; return *this; }

      /// @brief Legt die Y-Position fest.
      Point& Y (T val) { y = val; return *this; }

      /// @brief Legt die Position über Zahlenwerte fest.
      Point& Set (T xVal, T yVal) { x = xVal; y = yVal; return *this; }

      /// @brief Legt die Position über einen SFML-Vektor fest.
      Point& FromSFMLVector (const sf::Vector2<T>& vec) { return Set(vec.x, vec.y); }


      /// @brief Liefert die X-Position.
      T X () const { return x; }

      /// @brief Liefert die Y-Position.
      T Y () const { return y; }


      /// @brief Liefert einen entsprechenden SFML-Vektor.
      const sf::Vector2<T> AsSFMLVector () const { return sf::Vector2<T>(x, y); }
   };

}

