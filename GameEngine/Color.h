
#pragma once

#include "Precomp.h"


class Color
{
public:
   enum ValueType {
      RedValue = 0,
      GreenValue,
      BlueValue,
      AlphaValue
   };

private:
   std::array<float, 4> values;

public:
   Color (float red, float green, float blue, float alpha = 1.0f)
   {
      Set(red, green, blue, alpha);
   }

   Color (int red, int green, int blue, int alpha = 255)
   {
      Set(boost::numeric_cast<float>(red) / 255.0f, boost::numeric_cast<float>(green) / 255.0f, boost::numeric_cast<float>(blue) / 255.0f, boost::numeric_cast<float>(alpha) / 255.0f);
   }

   Color& Set (float red, float green, float blue, float alpha = 1.0f)
   {
      Red(red); Green(green); Blue(blue); Alpha(alpha);
      return *this;
   }

   Color& Red (float val, bool mode = ABS)   { return Value(RedValue, val, mode); }
   Color& Green (float val, bool mode = ABS) { return Value(GreenValue, val, mode); }
   Color& Blue (float val, bool mode = ABS)  { return Value(BlueValue, val, mode); }
   Color& Alpha (float val, bool mode = ABS) { return Value(AlphaValue, val, mode); }

   Color& Value (const ValueType& type, float val, bool mode = ABS)
   {
      if (mode == ABS) values[type] = val;
      else             values[type] += val;

      if (values[type] < 0.0f)      values[type] = 0.0f;
      else if (values[type] > 1.0f) values[type] = 1.0f;
      else                          values[type] = val;

      return *this;
   }

   float Red () const                        { return values[RedValue]; }
   float Green () const                      { return values[GreenValue]; }
   float Blue () const                       { return values[BlueValue]; }
   float Alpha () const                      { return values[AlphaValue]; }
   float Value (const ValueType& type) const { return values[type]; }

   const float* Get () const { return values.data(); }



   Color operator+ (const Color& other) { return Color(Red() + other.Red(), Green() + other.Green(), Blue() + other.Blue(), Alpha() + other.Alpha()); }
   Color operator- (const Color& other) { return Color(Red() - other.Red(), Green() - other.Green(), Blue() - other.Blue(), Alpha() - other.Alpha()); }
   Color operator* (const Color& other) { return Color(Red() * other.Red(), Green() * other.Green(), Blue() * other.Blue(), Alpha() * other.Alpha()); }

   Color& operator+= (const Color& other) { Set(Red() + other.Red(), Green() + other.Green(), Blue() + other.Blue(), Alpha() + other.Alpha()); return *this; }
   Color& operator-= (const Color& other) { Set(Red() - other.Red(), Green() - other.Green(), Blue() - other.Blue(), Alpha() - other.Alpha()); return *this; }
   Color& operator*= (const Color& other) { Set(Red() * other.Red(), Green() * other.Green(), Blue() * other.Blue(), Alpha() * other.Alpha()); return *this; }

   Color& operator*= (float val) { Set(Red() * val, Green() * val, Blue() * val, Alpha() * val); return *this; }

   bool operator== (const Color& other) { return (Red() == other.Red() && Green() == other.Green() && Blue() == other.Blue() && Alpha() == other.Alpha()); }
   bool operator!= (const Color& other) { return !(Red() == other.Red() && Green() == other.Green() && Blue() == other.Blue() && Alpha() == other.Alpha()); }
};

