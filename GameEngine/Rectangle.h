
#pragma once

#include "Precomp.h"

#include <SFML/System/Vector2.hpp>

#include "Point.h"

#include "DLL_DEF.h"


namespace ge {

   /// @brief Standard-Klasse für Rechtecke (Koordinaten).
   template<typename T>
   class GEDLL Rectangle
   {
      T left;
      T top;
      T right;
      T bottom;

      void CheckType() { static_assert(std::is_arithmetic<T>::value, "ge::Rectangle<T> only supports integral or floating point types!"); }

      void Adjust ()
      {
         if (left > right) std::swap(left, right);
         if (top > bottom) std::swap(top, bottom);
      }

   public:
      /// @brief Konstruktor. Initialisierung über Zahlenangaben.
      Rectangle (T left, T top, T right, T bottom)
      {
         Set(left, top, right, bottom);
      }

      /// @brief Konstruktor. Initialisierung über ge::Point.
      Rectangle (const Point<T>& topLeft, const Point<T>& bottomRight)
      {
         Set(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y());
      }

      /// @brief Konstruktor. Initialisierung über SFML-Vektoren.
      Rectangle (const sf::Vector2<T>& topLeft, const sf::Vector2<T>& bottomRight)
      {
         Set(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
      }


      /// @brief Legt die linke Position fest (verändert die Breite).
      Rectangle& Left (T val) { left = val; Adjust(); return *this; }

      /// @brief Legt die obere Position fest (verändert die Höhe).
      Rectangle& Top (T val) { top = val; Adjust(); return *this; }

      /// @brief Legt die rechte Position fest (verändert die Breite).
      Rectangle& Right (T val) { right = val; Adjust(); return *this; }

      /// @brief Legt die untere Position fest (verändert die Höhe).
      Rectangle& Bottom (T val) { bottom = val; Adjust(); return *this; }

      /// @brief Legt alle Positionen über Zahlenwerte fest.
      Rectangle& Set (T leftVal, T topVal, T rightVal, T bottomVal)
      {
         left   = leftVal;
         top    = topVal;
         right  = rightVal;
         bottom = bottomVal;

         Adjust();
         return *this;
      }

      /// @brief Legt die Breite fest (verändert rechte Position).
      Rectangle& Width (T val)  { right = left + val; Adjust(); return *this; }

      /// @brief Legt die Höhe fest (verändert untere Position).
      Rectangle& Height (T val) { bottom = top + val; Adjust(); return *this; }


      /// @brief Liefert die linke Position.
      T Left () const { return left; }

      /// @brief Liefert die obere Position.
      T Top () const { return top; }

      /// @brief Liefert die rechte Position.
      T Right () const { return right; }

      /// @brief Liefert die untere Position.
      T Bottom () const { return bottom; }

      /// @brief Liefert die Breite.
      T Width () const { return right - left; }

      /// @brief Liefert die Höhe.
      T Height () const { return bottom - top; }


      /// @brief Liefert ein entsprechendes Paar aus ge::Point.
      const std::pair<Point<T>, Point<T>> AsPoints () const { return std::make_pair(Point<T>(left, top), Point<T>(right, bottom)); }

      /// @brief Liefert ein entsprechendes Paar aus SFML-Vektoren.
      const std::pair<sf::Vector2<T>, sf::Vector2<T>> AsSFMLVectors () const
      {
         return std::make_pair(sf::Vector2<T>(left, top), sf::Vector2<int>(right, bottom));
      }
   };

}

