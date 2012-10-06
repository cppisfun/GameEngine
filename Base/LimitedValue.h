
#pragma once

#include "Precomp.h"

#include "DLL_DEF.h"


/// @brief Namespace für Hilfsklassen und -funktionen, die dem Status einer
/// Basisfunktion nicht ganz gerecht werden.
namespace misc {

   /// @brief Template-Klasse, die einen Wert unter Berücksichtigung einer Ober-
   /// und Untergrenze ändert. Die Klasse darf nur in Verbindung mit
   /// arithmetischen Datentypen verwendet werden.
   ///
   /// Bei nicht-zyklischer Verwendung wird der Wert des Objektes nie größer als
   /// seine Obergrenze und nie kleiner als seine Untergrenze.
   ///
   /// Bei zyklischer Verwendung läuft der Wert ggf. über die Obergrenze hinaus
   /// und wird von der Untergrenze aus weiter erhöht, bis die angegebene
   /// Änderung komplett erfolgt ist (als wäre der Intervallbereich ein
   /// Papierstreifen, dessen beiden Enden zusammen geklebt wurden, so dass ein
   /// Ring entsteht).
   template<typename T>
   class BASEDLL LimitedValue
   {
      bool isCyclic;
      T minimum;
      T maximum;
      T value;

      void Adjust ()
      {
         if (minimum > maximum) std::swap(minimum, maximum);

         if (minimum == maximum) {
            value = minimum;
         }
         else if (isCyclic) {
            if (value < minimum)      while (value < minimum) value = value + maximum - minimum + 1;
            else if (value > maximum) while (value > maximum) value = value - maximum + minimum - 1;
         }
         else {
            if (value < minimum)      value = minimum;
            else if (value > maximum) value = maximum;
         }
      }

   public:
      /// @brief Konstruktor.
      /// @param minimum Untergrenze
      /// @param maximum Obergrenze
      /// @param isCyclic Gibt an, ob sich das Objekt zyklisch verhalten soll (Standard: false)
      /// @param value Wert (Standard: 0)
      LimitedValue (T minimum, T maximum, bool isCyclic = false, T value = 0) : isCyclic(isCyclic), minimum(minimum), maximum(maximum), value(value)
      {
         static_assert(std::is_arithmetic<T>::value, "LimitedValue<> only supports integral or floating point types!");
         Adjust();
      }


      /// @brief Stellt das Verhalten des Objektes zyklisch bzw. nicht-zyklisch ein.
      LimitedValue& IsCyclic (bool val) { isCyclic = val; Adjust(); return *this; }

      /// @brief Setzt die Obergrenze.
      LimitedValue& Minimum (T val) { minimum = val; Adjust(); return *this; }

      /// @brief Setzt die Untergrenze.
      LimitedValue& Maximum (T val) { maximum = val; Adjust(); return *this; }

      /// @brief Setzt den Wert.
      LimitedValue& Value (T val) { value = val; Adjust(); return *this; }


      /// @brief Liefert das aktuelle Verhalten des Objekts (zyklisch oder nicht-zyklisch).
      bool IsCyclic () const { return isCyclic; }

      /// @brief Liefert die aktuelle Obergrenze.
      T Minimum () const { return minimum; }

      /// @brief Liefert die aktuelle Untergrenze.
      T Maximum () const { return maximum; }

      /// @brief Liefert den aktuellen Wert.
      T Value () const { return value; }


      /// @brief Operator == für zwei LimitedValue-Objekte
      bool operator== (const LimitedValue& other) { return (value == other.Value()); }

      /// @brief Operator != für zwei LimitedValue-Objekte
      bool operator!= (const LimitedValue& other) { return (value != other.Value()); }

      /// @brief Operator < für zwei LimitedValue-Objekte
      bool operator< (const LimitedValue& other) { return (value < other.Value()); }

      /// @brief Operator <= für zwei LimitedValue-Objekte
      bool operator<= (const LimitedValue& other) { return (value <= other.Value()); }

      /// @brief Operator > für zwei LimitedValue-Objekte
      bool operator> (const LimitedValue& other) { return (value > other.Value()); }

      /// @brief Operator >= für zwei LimitedValue-Objekte
      bool operator>= (const LimitedValue& other) { return (value >= other.Value()); }


      /// @brief Operator == für LimitedValue-Objekt und passenden Datentyp
      bool operator== (T val) { return (value == val); }

      /// @brief Operator != für LimitedValue-Objekt und passenden Datentyp
      bool operator!= (T val) { return (value != val); }

      /// @brief Operator < für LimitedValue-Objekt und passenden Datentyp
      bool operator< (T val) { return (value < val); }

      /// @brief Operator <= für LimitedValue-Objekt und passenden Datentyp
      bool operator<= (T val) { return (value <= val); }

      /// @brief Operator > für LimitedValue-Objekt und passenden Datentyp
      bool operator> (T val) { return (value > val); }

      /// @brief Operator >= für LimitedValue-Objekt und passenden Datentyp
      bool operator>= (T val) { return (value >= val); }


      /// @brief Operator += für zwei LimitedValue-Objekte
      LimitedValue<T>& operator+= (const LimitedValue& other) { value += other.Value(); Adjust(); return *this; }

      /// @brief Operator -= für zwei LimitedValue-Objekte
      LimitedValue<T>& operator-= (const LimitedValue& other) { value -= other.Value(); Adjust(); return *this; }

      /// @brief Operator *= für zwei LimitedValue-Objekte
      LimitedValue<T>& operator*= (const LimitedValue& other) { value *= other.Value(); Adjust(); return *this; }

      /// @brief Operator /= für zwei LimitedValue-Objekte
      LimitedValue<T>& operator/= (const LimitedValue& other) { value /= other.Value(); Adjust(); return *this; }


      /// @brief Operator += für LimitedValue-Objekt und passenden Datentyp
      LimitedValue<T>& operator+= (T val) { value += val; Adjust(); return *this; }

      /// @brief Operator -= für LimitedValue-Objekt und passenden Datentyp
      LimitedValue<T>& operator-= (T val) { value -= val; Adjust(); return *this; }

      /// @brief Operator *= für LimitedValue-Objekt und passenden Datentyp
      LimitedValue<T>& operator*= (T val) { value *= val; Adjust(); return *this; }

      /// @brief Operator /= für LimitedValue-Objekt und passenden Datentyp
      LimitedValue<T>& operator/= (T val) { value /= val; Adjust(); return *this; }


      /// @brief Operator für Pre-Inkrementierung
      LimitedValue<T> operator++ (T) { LimitedValue<T> tmp(*this); ++value; Adjust(); return tmp; }

      /// @brief Operator für Pre-Dekrementierung
      LimitedValue<T> operator-- (T) { LimitedValue<T> tmp(*this); --value; Adjust(); return tmp; }

      /// @brief Operator für Post-Inkrementierung
      LimitedValue<T>& operator++ () { ++value; Adjust(); return *this; }

      /// @brief Operator für Post-Dekrementierung
      LimitedValue<T>& operator-- () { --value; Adjust(); return *this; }
   };



   /// @brief int-Variante von LimitedValue
   typedef LimitedValue<int> LimitedInt;

   /// @brief long-Variante von LimitedValue
   typedef LimitedValue<long> LimitedLong;

   /// @brief long long-Variante von LimitedValue
   typedef LimitedValue<long long> LimitedLongLong;

   /// @brief float-Variante von LimitedValue
   typedef LimitedValue<float> LimitedFloat;

   /// @brief double-Variante von LimitedValue
   typedef LimitedValue<double> LimitedDouble;
}

