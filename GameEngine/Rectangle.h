
#pragma once

#include "Precomp.h"

#include <SFML/System/Vector2.hpp>

#include "Point.h"

#include "DLL_DEF.h"


namespace ge {

   /// @brief Standard-Klasse f�r Rechtecke (Koordinaten).
   class GEDLL Rectangle
   {
      int left;
      int top;
      int right;
      int bottom;

      void Adjust ()
      {
         if (left > right) std::swap(left, right);
         if (top > bottom) std::swap(top, bottom);
      }

   public:
      /// @brief Konstruktor. Initialisierung �ber Zahlenangaben.
      Rectangle (int left, int top, int right, int bottom)
      {
         Set(left, top, right, bottom);
      }

      /// @brief Konstruktor. Initialisierung �ber ge::Point.
      Rectangle (const Point& topLeft, const Point& bottomRight)
      {
         Set(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y());
      }

      /// @brief Konstruktor. Initialisierung �ber SFML-Vektoren.
      Rectangle (const sf::Vector2<int>& topLeft, const sf::Vector2<int>& bottomRight)
      {
         Set(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
      }


      /// @brief Legt die linke Position fest (ver�ndert die Breite).
      Rectangle& Left (int val) { left = val; Adjust(); return *this; }

      /// @brief Legt die obere Position fest (ver�ndert die H�he).
      Rectangle& Top (int val) { top = val; Adjust(); return *this; }

      /// @brief Legt die rechte Position fest (ver�ndert die Breite).
      Rectangle& Right (int val) { right = val; Adjust(); return *this; }

      /// @brief Legt die untere Position fest (ver�ndert die H�he).
      Rectangle& Bottom (int val) { bottom = val; Adjust(); return *this; }

      /// @brief Legt alle Positionen �ber Zahlenwerte fest.
      Rectangle& Set (int leftVal, int topVal, int rightVal, int bottomVal)
      {
         left   = leftVal;
         top    = topVal;
         right  = rightVal;
         bottom = bottomVal;

         Adjust();
         return *this;
      }

      /// @brief Legt die Breite fest (ver�ndert rechte Position).
      Rectangle& Width (int val)  { right = left + val; Adjust(); return *this; }

      /// @brief Legt die H�he fest (ver�ndert untere Position).
      Rectangle& Height (int val) { bottom = top + val; Adjust(); return *this; }


      /// @brief Liefert die linke Position.
      int Left () const { return left; }

      /// @brief Liefert die obere Position.
      int Top () const { return top; }

      /// @brief Liefert die rechte Position.
      int Right () const { return right; }

      /// @brief Liefert die untere Position.
      int Bottom () const { return bottom; }

      /// @brief Liefert die Breite.
      int Width () const { return right - left; }

      /// @brief Liefert die H�he.
      int Height () const { return bottom - top; }


      /// @brief Liefert ein entsprechendes Paar aus ge::Point.
      const std::pair<Point, Point> AsPoints () const { return std::make_pair(Point(left, top), Point(right, bottom)); }

      /// @brief Liefert ein entsprechendes Paar aus SFML-Vektoren.
      const std::pair<sf::Vector2<int>, sf::Vector2<int>> AsSFMLVectors () const
      {
         return std::make_pair(sf::Vector2<int>(left, top), sf::Vector2<int>(right, bottom));
      }
   };

}

