
#pragma once

#include "Precomp.h"

#include "DLL_DEF.h"


namespace ge {

   /// @brief Standard-Klasse für Vektoren (Koordinaten).
   class GEDLL Vector
   {
   public:
      /// @brief Auflistung der möglichen Koordinatenangaben zur Verwendung mit
      /// Vector::Value().
      enum What {
         XValue = 0,
         YValue,
         ZValue
      };

   private:
      std::array<float, 3> values;

   public:
      /// @brief Standard-Konstruktor. Alle Werte werden mit 0 initialisiert.
      Vector ()
      {
         Set(0.0f, 0.0f, 0.0f);
      }

      /// @brief Konstruktor. Initialisierung über Zahlenwerte.
      /// @param x X-Position
      /// @param y Y-Position
      /// @param z Z-Position (Standard: 0)
      Vector (float x, float y, float z = 0.0f)
      {
         Set(x, y, z);
      }


      /// @brief Legt alle Koordinaten über Zahlenwerte fest.
      /// @param x X-Position
      /// @param y Y-Position
      /// @param z Z-Position (Standard: 0)
      Vector& Set (float x, float y, float z = 0.0f)
      {
         X(x); Y(y); Z(z);
         return *this;
      }

      /// @brief Legt die X-Koordinate fest.
      /// @param val X-Position
      /// @param mode ABS = absolute Änderung / Zuweisung, REL = relative Änderung / Addition (Standard: ABS)
      Vector& X (float val, bool mode = ABS) { return Value(XValue, val, mode); }

      /// @brief Legt die Y-Koordinate fest.
      /// @param val Y-Position
      /// @param mode ABS = absolute Änderung / Zuweisung, REL = relative Änderung / Addition (Standard: ABS)
      Vector& Y (float val, bool mode = ABS) { return Value(YValue, val, mode); }

      /// @brief Legt die Z-Koordinate fest.
      /// @param val Z-Position
      /// @param mode ABS = absolute Änderung / Zuweisung, REL = relative Änderung / Addition (Standard: ABS)
      Vector& Z (float val, bool mode = ABS) { return Value(ZValue, val, mode); }

      /// @brief Legt den angegebenen Wert aus dem Vector-Objekt fest.
      /// @param what Koordinatenangabe aus Vector::What
      /// @param val Positionswert
      /// @param mode ABS = absolute Änderung / Zuweisung, REL = relative Änderung / Addition (Standard: ABS)
      Vector& Value (const What& what, float val, bool mode = ABS)
      {
         if (mode == ABS) values[what] = val;
         else             values[what] += val;

         return *this;
      }


      /// @brief Liefert die X-Koordinate.
      float X () const { return values[XValue]; }

      /// @brief Liefert die X-Koordinate.
      float Y () const { return values[YValue]; }

      /// @brief Liefert die X-Koordinate.
      float Z () const { return values[ZValue]; }

      /// @brief Liefert den angegebenen Wert aus dem Vector-Objekt.
      /// @param what Koordinatenangabe aus Vector::What
      float Value (const What& what) const { values[what]; }

      /// @brief Ermittelt, ob es sich um einen Nullvektor handelt.
      bool IsZero () const  { return (values[XValue] == 0.0f && values[YValue] == 0.0f && values[ZValue] == 0.0f); }

      /// @brief Ermittelt die Länge des Vektors ohne Berücksichtigung der Z-Dimension.
      float Length2D () const { return std::sqrt(values[XValue] * values[XValue] + values[YValue] * values[YValue]); }

      /// @brief Ermittelt die Länge des Vektors unter Berücksichtigung der Z-Dimension.
      float Length3D () const { return std::sqrt(values[XValue] * values[XValue] + values[YValue] * values[YValue] + values[ZValue] * values[ZValue]); }

      /// @brief Liefert die Koordinaten als Daten-Pointer.
      const float* Get () const { return values.data(); }


      /// @brief Operator + für zwei Vector-Objekte.
      Vector operator+ (const Vector& other) { return Vector(X() + other.X(), Y() + other.Y(), Z() + other.Z()); }

      /// @brief Operator - für zwei Vector-Objekte.
      Vector operator- (const Vector& other) { return Vector(X() - other.X(), Y() - other.Y(), Z() - other.Z()); }

      /// @brief Operator * für zwei Vector-Objekte.
      Vector operator* (const Vector& other) { return Vector(X() * other.X(), Y() * other.Y(), Z() * other.Z()); }

      /// @brief Operator += für zwei Vector-Objekte.
      Vector& operator+= (const Vector& other) { Set(X() + other.X(), Y() + other.Y(), Z() + other.Z()); return *this; }

      /// @brief Operator -= für zwei Vector-Objekte.
      Vector& operator-= (const Vector& other) { Set(X() - other.X(), Y() - other.Y(), Z() - other.Z()); return *this; }

      /// @brief Operator *= für zwei Vector-Objekte.
      Vector& operator*= (const Vector& other) { Set(X() * other.X(), Y() * other.Y(), Z() * other.Z()); return *this; }


      /// @brief Operator *= für Vector-Objekt und float.
      Vector& operator*= (float val) { Set(X() * val, Y() * val, Z() * val); return *this; }


      /// @brief Operator == für zwei Vector-Objekte.
      bool operator== (const Vector& other) { return (X() == other.X() && Y() == other.Y() && Z() == other.Z()); }

      /// @brief Operator != für zwei Vector-Objekte.
      bool operator!= (const Vector& other) { return !(X() == other.X() && Y() == other.Y() && Z() == other.Z()); }
   };

}

