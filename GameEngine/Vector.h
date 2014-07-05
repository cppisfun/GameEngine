
#pragma once

#include "Precomp.h"

#include "DLL_DEF.h"


namespace ge {

   class GEDLL Vector
   {
   public:
      enum What {
         XValue = 0,
         YValue,
         ZValue
      };

   private:
      std::array<float, 3> values;

   public:
      Vector ()                                 { Set(0.0f, 0.0f, 0.0f); }
      Vector (float x, float y, float z = 0.0f) { Set(x, y, z); }

      Vector& Set (float x, float y, float z = 0.0f) { X(x); Y(y); Z(z); return *this; }

      Vector& X (float val, bool absolute = true) { return Value(XValue, val, absolute); }
      Vector& Y (float val, bool absolute = true) { return Value(YValue, val, absolute); }
      Vector& Z (float val, bool absolute = true) { return Value(ZValue, val, absolute); }

      Vector& Value (const What& what, float val, bool absolute = true)
      {
         if (absolute) values[what] = val;
         else          values[what] += val;

         return *this;
      }

      float X () const                     { return values[XValue]; }
      float Y () const                     { return values[YValue]; }
      float Z () const                     { return values[ZValue]; }
      float Value (const What& what) const { values[what]; }

      bool IsZero () const { return (values[XValue] == 0.0f && values[YValue] == 0.0f && values[ZValue] == 0.0f); }

      float Length2D () const { return std::sqrt(values[XValue] * values[XValue] + values[YValue] * values[YValue]); }
      float Length3D () const { return std::sqrt(values[XValue] * values[XValue] + values[YValue] * values[YValue] + values[ZValue] * values[ZValue]); }

      const float* Get () const { return values.data(); }

      Vector operator+ (const Vector& other) { return Vector(X() + other.X(), Y() + other.Y(), Z() + other.Z()); }
      Vector operator- (const Vector& other) { return Vector(X() - other.X(), Y() - other.Y(), Z() - other.Z()); }
      Vector operator* (const Vector& other) { return Vector(X() * other.X(), Y() * other.Y(), Z() * other.Z()); }

      Vector& operator+= (const Vector& other) { Set(X() + other.X(), Y() + other.Y(), Z() + other.Z()); return *this; }
      Vector& operator-= (const Vector& other) { Set(X() - other.X(), Y() - other.Y(), Z() - other.Z()); return *this; }
      Vector& operator*= (const Vector& other) { Set(X() * other.X(), Y() * other.Y(), Z() * other.Z()); return *this; }

      Vector& operator*= (float val) { Set(X() * val, Y() * val, Z() * val); return *this; }

      bool operator== (const Vector& other) { return (X() == other.X() && Y() == other.Y() && Z() == other.Z()); }
      bool operator!= (const Vector& other) { return !(X() == other.X() && Y() == other.Y() && Z() == other.Z()); }
   };

}

