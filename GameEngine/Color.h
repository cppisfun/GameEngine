
#pragma once

#include "Precomp.h"

#include "DLL_DEF.h"


namespace ge {

   class GEDLL Color
   {
   public:
      enum What {
         RedValue = 0,
         GreenValue,
         BlueValue,
         AlphaValue
      };

   private:
      std::array<int, 4> values;

   public:
      Color (int red, int green, int blue, int alpha = 255) { Set(red, green, blue, alpha); }

      Color& Set (int red, int green, int blue, int alpha = 255) { Red(red); Green(green); Blue(blue); Alpha(alpha); return *this; }
      Color& Red (int val, bool absolute = true)                 { return Value(RedValue, val, absolute); }
      Color& Green (int val, bool absolute = true)               { return Value(GreenValue, val, absolute); }
      Color& Blue (int val, bool absolute = true)                { return Value(BlueValue, val, absolute); }
      Color& Alpha (int val, bool absolute = true)               { return Value(AlphaValue, val, absolute); }

      Color& Value (const What& what, int val, bool absolute = true)
      {
         if (absolute) values[what] = val;
         else          values[what] += val;

         if (values[what] < 0)        values[what] = 0;
         else if (values[what] > 255) values[what] = 255;
         else                         values[what] = val;

         return *this;
      }

      int Red () const                   { return values[RedValue]; }
      int Green () const                 { return values[GreenValue]; }
      int Blue () const                  { return values[BlueValue]; }
      int Alpha () const                 { return values[AlphaValue]; }
      int Value (const What& what) const { return values[what]; }

      const int* Get () const { return values.data(); }

      Color operator+ (const Color& other) { return Color(Red() + other.Red(), Green() + other.Green(), Blue() + other.Blue(), Alpha() + other.Alpha()); }
      Color operator- (const Color& other) { return Color(Red() - other.Red(), Green() - other.Green(), Blue() - other.Blue(), Alpha() - other.Alpha()); }
      Color operator* (const Color& other) { return Color(Red() * other.Red(), Green() * other.Green(), Blue() * other.Blue(), Alpha() * other.Alpha()); }

      Color& operator+= (const Color& other) { Set(Red() + other.Red(), Green() + other.Green(), Blue() + other.Blue(), Alpha() + other.Alpha()); return *this; }
      Color& operator-= (const Color& other) { Set(Red() - other.Red(), Green() - other.Green(), Blue() - other.Blue(), Alpha() - other.Alpha()); return *this; }
      Color& operator*= (const Color& other) { Set(Red() * other.Red(), Green() * other.Green(), Blue() * other.Blue(), Alpha() * other.Alpha()); return *this; }

      Color& operator*= (int val) { Set(Red() * val, Green() * val, Blue() * val, Alpha() * val); return *this; }

      bool operator== (const Color& other) { return (Red() == other.Red() && Green() == other.Green() && Blue() == other.Blue() && Alpha() == other.Alpha()); }
      bool operator!= (const Color& other) { return !(Red() == other.Red() && Green() == other.Green() && Blue() == other.Blue() && Alpha() == other.Alpha()); }
   };

}

