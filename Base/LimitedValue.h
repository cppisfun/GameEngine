
#pragma once

#include "Precomp.h"

#include "DLL_DEF.h"


namespace misc {

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
      LimitedValue (T minimum, T maximum, bool isCyclic = false, T value = 0) : isCyclic(isCyclic), minimum(minimum), maximum(maximum), value(value)
      {
         static_assert(std::is_arithmetic<T>::value, "LimitedValue<> only supports integral or floating point types!");
         Adjust();
      }

      LimitedValue& IsCyclic (bool val) { isCyclic = val; Adjust(); return *this; }
      LimitedValue& Minimum (T val)     { minimum = val; Adjust(); return *this; }
      LimitedValue& Maximum (T val)     { maximum = val; Adjust(); return *this; }
      LimitedValue& Value (T val)       { value = val; Adjust(); return *this; }

      bool IsCyclic () const { return isCyclic; }
      T Minimum () const     { return minimum; }
      T Maximum () const     { return maximum; }
      T Value () const       { return value; }

      bool operator== (const LimitedValue& other) { return (value == other.Value()); }
      bool operator!= (const LimitedValue& other) { return (value != other.Value()); }
      bool operator<  (const LimitedValue& other) { return (value < other.Value()); }
      bool operator<= (const LimitedValue& other) { return (value <= other.Value()); }
      bool operator>  (const LimitedValue& other) { return (value > other.Value()); }
      bool operator>= (const LimitedValue& other) { return (value >= other.Value()); }

      bool operator== (T val) { return (value == val); }
      bool operator!= (T val) { return (value != val); }
      bool operator< (T val)  { return (value < val); }
      bool operator<= (T val) { return (value <= val); }
      bool operator> (T val)  { return (value > val); }
      bool operator>= (T val) { return (value >= val); }

      LimitedValue<T>& operator+= (const LimitedValue& other) { value += other.Value(); Adjust(); return *this; }
      LimitedValue<T>& operator-= (const LimitedValue& other) { value -= other.Value(); Adjust(); return *this; }
      LimitedValue<T>& operator*= (const LimitedValue& other) { value *= other.Value(); Adjust(); return *this; }
      LimitedValue<T>& operator/= (const LimitedValue& other) { value /= other.Value(); Adjust(); return *this; }

      LimitedValue<T>& operator+= (T val) { value += val; Adjust(); return *this; }
      LimitedValue<T>& operator-= (T val) { value -= val; Adjust(); return *this; }
      LimitedValue<T>& operator*= (T val) { value *= val; Adjust(); return *this; }
      LimitedValue<T>& operator/= (T val) { value /= val; Adjust(); return *this; }

      LimitedValue<T> operator++ (T) { LimitedValue<T> tmp(*this); ++value; Adjust(); return tmp; }
      LimitedValue<T> operator-- (T) { LimitedValue<T> tmp(*this); --value; Adjust(); return tmp; }

      LimitedValue<T>& operator++ () { ++value; Adjust(); return *this; }
      LimitedValue<T>& operator-- () { --value; Adjust(); return *this; }
   };



   typedef LimitedValue<int>       LimitedInt;
   typedef LimitedValue<long>      LimitedLong;
   typedef LimitedValue<long long> LimitedLongLong;
   typedef LimitedValue<float>     LimitedFloat;
   typedef LimitedValue<double>    LimitedDouble;
}

