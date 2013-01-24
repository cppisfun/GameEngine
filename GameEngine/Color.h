
#pragma once

#include "Precomp.h"

#include <SColor.h>
#include <SFML/Graphics/Color.hpp>

#include "DLL_DEF.h"


namespace ge {

   /// @brief Standard-Klasse für Farben.
   class GEDLL Color
   {
   public:
      /// @brief Auflistung der möglichen Farbwertangaben zur Verwendung mit
      /// Color::Value().
      enum What {
         RedValue = 0,
         GreenValue,
         BlueValue,
         AlphaValue
      };

   private:
      std::array<int, 4> values;

   public:
      /// @brief Konstruktor. Initialisierung über Zahlenangaben.
      /// @param red Rotanteil (0 - 255)
      /// @param green Grünanteil (0 - 255)
      /// @param blue Blauanteil (0 - 255)
      /// @param alpha Alphawert (0 - 255, Standard: 255)
      Color (int red, int green, int blue, int alpha = 255)
      {
         Set(red, green, blue, alpha);
      }

      /// @brief Konstruktor. Initialisierung über eine SFML-Farbe.
      Color (const sf::Color& color)
      {
         FromSFMLColor(color);
      }


      /// @brief Legt alle Farbanteile und den Alphawert über Zahlenwerte fest.
      /// @param red Rotanteil (0 - 255)
      /// @param green Grünanteil (0 - 255)
      /// @param blue Blauanteil (0 - 255)
      /// @param alpha Alphawert (0 - 255, Standard: 255)
      Color& Set (int red, int green, int blue, int alpha = 255) { Red(red); Green(green); Blue(blue); Alpha(alpha); return *this; }

      /// @brief Legt alle Farbanteile und den Alphawert über eine
      /// SFML-Farbe fest.
      Color& FromSFMLColor (const sf::Color& color) { return Set(color.r, color.g, color.b, color.a); }

      /// @brief Legt den Rotanteil fest.
      /// @param val Rotanteil (0 - 255)
      /// @param absolute _true_ = absolute Änderung / Zuweisung, _false_ =
      /// relative Änderung / Addition (Standard: _true_)
      Color& Red (int val, bool absolute = true) { return Value(RedValue, val, absolute); }

      /// @brief Legt den Grünanteil fest.
      /// @param val Grünanteil (0 - 255)
      /// @param absolute _true_ = absolute Änderung / Zuweisung, _false_ =
      /// relative Änderung / Addition (Standard: _true_)
      Color& Green (int val, bool absolute = true) { return Value(GreenValue, val, absolute); }

      /// @brief Legt den Blauanteil fest.
      /// @param val Blauanteil (0 - 255)
      /// @param absolute _true_ = absolute Änderung / Zuweisung, _false_ =
      /// relative Änderung / Addition (Standard: _true_)
      Color& Blue (int val, bool absolute = true) { return Value(BlueValue, val, absolute); }

      /// @brief Legt den Alphawert fest.
      /// @param val Alphawert (0 - 255)
      /// @param absolute _true_ = absolute Änderung / Zuweisung, _false_ =
      /// relative Änderung / Addition (Standard: _true_)
      Color& Alpha (int val, bool absolute = true) { return Value(AlphaValue, val, absolute); }

      /// @brief Legt den angegebenen Wert aus dem Farbobjekt fest.
      /// @param what Farbwertangabe aus Color::ValueType
      /// @param val Anteilswert (0 - 255)
      /// @param absolute _true_ = absolute Änderung / Zuweisung, _false_ =
      /// relative Änderung / Addition (Standard: _true_)
      Color& Value (const What& what, int val, bool absolute = true)
      {
         if (absolute) values[what] = val;
         else          values[what] += val;

         if (values[what] < 0)        values[what] = 0;
         else if (values[what] > 255) values[what] = 255;
         else                         values[what] = val;

         return *this;
      }


      /// @brief Liefert den Rotanteil.
      int Red () const { return values[RedValue]; }

      /// @brief Liefert den Grünanteil.
      int Green () const { return values[GreenValue]; }

      /// @brief Liefert den Blauanteil.
      int Blue () const { return values[BlueValue]; }

      /// @brief Liefert den Alphawert.
      int Alpha () const { return values[AlphaValue]; }

      /// @brief Liefert den angegebenen Wert aus dem Farbobjekt.
      /// @param what Farbwerteingabe aus Color::ValueType
      int Value (const What& what) const { return values[what]; }


      /// @brief Liefert die Farbanteile und den Alphawert als Daten-Pointer.
      const int* Get () const { return values.data(); }

      /// @brief Liefert ein entsprechendes SFML-Farbobjekt.
      const sf::Color AsSFMLColor () const { return sf::Color(values[RedValue], values[GreenValue], values[BlueValue], values[AlphaValue]); }


      /// @brief Operator + für zwei Color-Objekte
      Color operator+ (const Color& other) { return Color(Red() + other.Red(), Green() + other.Green(), Blue() + other.Blue(), Alpha() + other.Alpha()); }

      /// @brief Operator - für zwei Color-Objekte
      Color operator- (const Color& other) { return Color(Red() - other.Red(), Green() - other.Green(), Blue() - other.Blue(), Alpha() - other.Alpha()); }

      /// @brief Operator * für zwei Color-Objekte
      Color operator* (const Color& other) { return Color(Red() * other.Red(), Green() * other.Green(), Blue() * other.Blue(), Alpha() * other.Alpha()); }

      /// @brief Operator += für zwei Color-Objekte
      Color& operator+= (const Color& other) { Set(Red() + other.Red(), Green() + other.Green(), Blue() + other.Blue(), Alpha() + other.Alpha()); return *this; }

      /// @brief Operator -= für zwei Color-Objekte
      Color& operator-= (const Color& other) { Set(Red() - other.Red(), Green() - other.Green(), Blue() - other.Blue(), Alpha() - other.Alpha()); return *this; }

      /// @brief Operator *= für zwei Color-Objekte
      Color& operator*= (const Color& other) { Set(Red() * other.Red(), Green() * other.Green(), Blue() * other.Blue(), Alpha() * other.Alpha()); return *this; }


      /// @brief Operator *= für Color-Objekt und int
      Color& operator*= (int val) { Set(Red() * val, Green() * val, Blue() * val, Alpha() * val); return *this; }


      /// @brief Operator == für zwei Color-Objekte
      bool operator== (const Color& other) { return (Red() == other.Red() && Green() == other.Green() && Blue() == other.Blue() && Alpha() == other.Alpha()); }

      /// @brief Operator != für zwei Color-Objekte
      bool operator!= (const Color& other) { return !(Red() == other.Red() && Green() == other.Green() && Blue() == other.Blue() && Alpha() == other.Alpha()); }
   };

}

