
#pragma once

#include "Precomp.h"

#include <vector2d.h>
#include <rect.h>

#include "Point.h"

#include "DLL_DEF.h"


namespace ge {

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
      Rectangle (int left, int top, int right, int bottom)
      {
         Set(left, top, right, bottom);
      }

      Rectangle (const Point& topLeft, const Point& bottomRight)
      {
         Set(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y());
      }

      Rectangle (const irr::core::vector2d<int>& topLeft, irr::core::vector2d<int>& bottomRight)
      {
         Set(topLeft.X, topLeft.Y, bottomRight.X, bottomRight.Y);
      }

      Rectangle (const irr::core::rect<int>& rect)
      {
         Set(rect.UpperLeftCorner.X, rect.UpperLeftCorner.Y, rect.LowerRightCorner.X, rect.LowerRightCorner.Y);
      }

      Rectangle& Left (int val)   { left = val; Adjust(); return *this; }
      Rectangle& Top (int val)    { top = val; Adjust(); return *this; }
      Rectangle& Right (int val)  { right = val; Adjust(); return *this; }
      Rectangle& Bottom (int val) { bottom = val; Adjust(); return *this; }

      Rectangle& Set (int leftVal, int topVal, int rightVal, int bottomVal)
      {
         left   = leftVal;
         top    = topVal;
         right  = rightVal;
         bottom = bottomVal;

         Adjust();
         return *this;
      }

      Rectangle& Width (int val)  { right = left + val; Adjust(); return *this; }
      Rectangle& Height (int val) { bottom = top + val; Adjust(); return *this; }

      int Left () const   { return left; }
      int Top () const    { return top; }
      int Right () const  { return right; }
      int Bottom () const { return bottom; }

      int Width () const  { return right - left; }
      int Height () const { return bottom - top; }

      const std::pair<Point, Point> AsPoints () const { return std::make_pair(Point(left, top), Point(right, bottom)); }

      const std::pair<irr::core::vector2d<int>, irr::core::vector2d<int>> AsIrrVectors () const
      {
         return std::make_pair(irr::core::vector2d<int>(left, top), irr::core::vector2d<int>(right, bottom));
      }

      const irr::core::rect<int> AsIrrRect () const { irr::core::rect<int>(left, top, right, bottom); }
   };

}

