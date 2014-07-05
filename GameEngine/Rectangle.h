
#pragma once

#include "Precomp.h"

#include "Point.h"

#include "DLL_DEF.h"


namespace ge {

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
      Rectangle (T left, T top, T right, T bottom)                     { CheckType(); Set(left, top, right, bottom); }
      Rectangle (const Point<T>& topLeft, const Point<T>& bottomRight) { CheckType(); FromPoints(topLeft, bottomRight); }

      Rectangle& Left (T val)   { left = val; Adjust(); return *this; }
      Rectangle& Top (T val)    { top = val; Adjust(); return *this; }
      Rectangle& Right (T val)  { right = val; Adjust(); return *this; }
      Rectangle& Bottom (T val) { bottom = val; Adjust(); return *this; }

      Rectangle& Set (T leftVal, T topVal, T rightVal, T bottomVal)
      {
         left   = leftVal;
         top    = topVal;
         right  = rightVal;
         bottom = bottomVal;

         Adjust();
         return *this;
      }

      Rectangle& FromPoints (const Point<T>& topLeft, const Point<T>& bottomRight) { return Set(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y()); }

      Rectangle& Width (T val)  { right = left + val; Adjust(); return *this; }
      Rectangle& Height (T val) { bottom = top + val; Adjust(); return *this; }

      T Left () const   { return left; }
      T Top () const    { return top; }
      T Right () const  { return right; }
      T Bottom () const { return bottom; }
      T Width () const  { return right - left; }
      T Height () const { return bottom - top; }

      const std::pair<Point<T>, Point<T>> AsPoints () const { return std::make_pair(Point<T>(left, top), Point<T>(right, bottom)); }

      bool Contains (const Point<T>& point) const    { return left <= point.X() && top <= point.Y() && right >= point.X() && bottom >= point.Y(); }
      bool Contains (const Rectangle<T>& rect) const { return left <= rect.Left() && top <= rect.Top() && right >= rect.Right() && bottom >= rect.Bottom(); }

      bool Intersects (const Rectangle<T>& other) const { return !(other.Empty() || left > other.Right() || right < other.Left() || top > other.Bottom() || bottom < other.Top()); }

      bool Empty () const { return Width() > 0 && Height() > 0; }

      bool operator== (const Rectangle<T>& other) const { return left == other.Left() && top == other.Top() && right == other.Right() && bottom == other.Bottom(); }
      bool operator!= (const Rectangle<T>& other) const { return left != other.Left() || top != other.Top() || right != other.Right() || bottom != other.Bottom(); }

      Rectangle<T> operator% (const Rectangle<T>& other) const
      {
         Rectangle<T> rect(0, 0, 0, 0);
         if (!Intersects(other)) return rect;

         rect.Set(std::max(left, other.Left()), std::max(top, other.Top()), std::min(right, other.Right()), std::min(bottom, other.Bottom()));
         return rect;
      }
   };

}

