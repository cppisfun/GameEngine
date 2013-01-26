
#pragma once

#include "Precomp.h"

#include <SFML/System/Vector2.hpp>

#include "Point.h"

#include "DLL_DEF.h"


namespace ge {

   /// @brief Standard-Klasse für Rechtecke (Koordinaten).
   template<typename T>
   class GEDLL Rect
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
      Rect (T left, T top, T right, T bottom)
      {
         CheckType();
         Set(left, top, right, bottom);
      }

      /// @brief Konstruktor. Initialisierung über ge::Point.
      Rect (const Point<T>& topLeft, const Point<T>& bottomRight)
      {
         CheckType();
         FromPoints(topLeft, bottomRight);
      }

      /// @brief Konstruktor. Initialisierung über SFML-Vektoren.
      Rect (const sf::Vector2<T>& topLeft, const sf::Vector2<T>& bottomRight)
      {
         CheckType();
         FromSFMLVectors(topLeft, bottomRight);
      }


      /// @brief Legt die linke Position fest (verändert die Breite).
      Rect& Left (T val) { left = val; Adjust(); return *this; }

      /// @brief Legt die obere Position fest (verändert die Höhe).
      Rect& Top (T val) { top = val; Adjust(); return *this; }

      /// @brief Legt die rechte Position fest (verändert die Breite).
      Rect& Right (T val) { right = val; Adjust(); return *this; }

      /// @brief Legt die untere Position fest (verändert die Höhe).
      Rect& Bottom (T val) { bottom = val; Adjust(); return *this; }

      /// @brief Legt alle Positionen über Zahlenwerte fest.
      Rect& Set (T leftVal, T topVal, T rightVal, T bottomVal)
      {
         left   = leftVal;
         top    = topVal;
         right  = rightVal;
         bottom = bottomVal;

         Adjust();
         return *this;
      }

      /// @brief Legt alle Positionen über zwei Point-Objekte fest.
      Rect& FromPoints (const Point<T>& topLeft, const Point<T>& bottomRight)
      {
         return Set(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y());
      }

      /// @brief Legt alle Positionen über zwei SFML-Vektoren fest.
      Rect& FromSFMLVectors (const sf::Vector2<T>& topLeft, const sf::Vector2<T>& bottomRight)
      {
         return Set(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
      }

      /// @brief Legt die Breite fest (verändert rechte Position).
      Rect& Width (T val) { right = left + val; Adjust(); return *this; }

      /// @brief Legt die Höhe fest (verändert untere Position).
      Rect& Height (T val) { bottom = top + val; Adjust(); return *this; }


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


      /// @brief Stellt fest, ob ein angegebener Punkt vom aktuellen Rechteck
      /// beinhaltet wird.
      bool Contains (const Point<T>& point) const { return left <= point.X() && top <= point.Y() && right >= point.X() && bottom >= point.Y(); }

      /// @brief Stellt fest, ob ein angegebenes Rechteck vom aktuellen
      /// Rechteck beinhaltet wird.
      bool Contains (const Rect<T>& rect) const { return left <= rect.Left() && top <= rect.Top() && right >= rect.Right() && bottom >= rect.Bottom(); }

      /// @brief Stellt fest, ob ein angegebenes Rechteck mit dem aktuellen
      /// Rechteck eine Schnittmenge bildet.
      bool Intersects (const Rect<T>& other) const
      {
         return !(other.Empty() || left > other.Right() || right < other.Left() || top > other.Bottom() || bottom < other.Top());
      }

      /// @brief Stellt fest, ob das Rechteck eine Breite und Höhe besitzt oder
      /// ob es gewissermaßen "leer" ist.
      bool Empty () const { return Width() > 0 && Height() > 0; }


      /// @brief Operator == für zwei Rect-Objekte.
      bool operator== (const Rect<T>& other) const { return left == other.Left() && top == other.Top() && right == other.Right() && bottom == other.Bottom(); }

      /// @brief Operator != für zwei Rect-Objekte.
      bool operator!= (const Rect<T>& other) const { return left != other.Left() || top != other.Top() || right != other.Right() || bottom != other.Bottom(); }

      /// @brief Überschriebener Operator % (Modulo). Liefert die Schnittmenge
      /// zweier Rechtecke als Rect-Objekt.
      Rect<T> operator% (const Rect<T>& other) const
      {
         Rect<T> rect(0, 0, 0, 0);
         if (!Intersects(other)) return rect;

         rect.Set(std::max(left, other.Left()), std::max(top, other.Top()), std::min(right, other.Right()), std::min(bottom, other.Bottom()));
         return rect;
      }
   };

}

