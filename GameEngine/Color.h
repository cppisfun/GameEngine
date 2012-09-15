
#pragma once

#include "Precomp.h"

#include <SColor.h>

#include "DLL_DEF.h"


namespace ge {

   class GEDLL Color
   {
   public:
      enum ValueType {
         RedValue = 0,
         GreenValue,
         BlueValue,
         AlphaValue
      };

   private:
      std::array<int, 4> values;

   public:
      Color (int red, int green, int blue, int alpha = 255)
      {
         Set(red, green, blue, alpha);
      }

      Color (const irr::video::SColor& color)
      {
         FromIrrColor(color);
      }

      Color& Set (int red, int green, int blue, int alpha = 255)
      {
         Red(red); Green(green); Blue(blue); Alpha(alpha);
         return *this;
      }

      Color& FromIrrColor (const irr::video::SColor& color)
      {
         return Set(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
      }

      Color& Red (int val, bool mode = ABS)   { return Value(RedValue, val, mode); }
      Color& Green (int val, bool mode = ABS) { return Value(GreenValue, val, mode); }
      Color& Blue (int val, bool mode = ABS)  { return Value(BlueValue, val, mode); }
      Color& Alpha (int val, bool mode = ABS) { return Value(AlphaValue, val, mode); }

      Color& Value (const ValueType& type, int val, bool mode = ABS)
      {
         if (mode == ABS) values[type] = val;
         else             values[type] += val;

         if (values[type] < 0)        values[type] = 0;
         else if (values[type] > 255) values[type] = 255;
         else                         values[type] = val;

         return *this;
      }

      int Red () const                        { return values[RedValue]; }
      int Green () const                      { return values[GreenValue]; }
      int Blue () const                       { return values[BlueValue]; }
      int Alpha () const                      { return values[AlphaValue]; }
      int Value (const ValueType& type) const { return values[type]; }

      const int* Get () const { return values.data(); }

      const irr::video::SColor AsIrrColor () const
      {
         return irr::video::SColor(values[AlphaValue], values[RedValue], values[GreenValue], values[BlueValue]);
      }

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

