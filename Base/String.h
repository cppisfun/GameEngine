
#pragma once

#include "DLL_DEF.h"


namespace base {

   /// @brief Entfernt linksseitige Leerzeichen aus dem String.
   BASEDLL void LTrim (std::string& val);

   /// @brief Entfernt rechtsseitige Leerzeichen aus dem String.
   BASEDLL void RTrim (std::string& val);

   /// @brief Entfernt links- und rechtsseitige Leerzeichen aus dem String.
   BASEDLL void Trim (std::string& val);

   /// @brief Ändert im String alle Buchstaben in Großbuchstaben.
   BASEDLL void Upper (std::string& val);

   /// @brief Ändert im String alle Buchstaben in Kleinbuchstaben.
   BASEDLL void Lower (std::string& val);

   /// @brief Ersetzt im String eine angegebene Zeichenfolge durch eine andere.
   /// @param src Zu Ändernder String
   /// @param what Zu ersetzende Zeichenfolge
   /// @param with Zeichenfolge, die statt _what_ eingesetzt werden soll
   BASEDLL void Replace (std::string& src, const std::string& what, const std::string& with);

   /// @brief Verkürzt den String auf den linksseitigen Teilstring einer
   /// bestimmten Länge.
   /// @param val Zu ändernder String
   /// @param length Teilstring-Länge
   BASEDLL void Left (std::string& val, int length);

   /// @brief Verkürzt den String auf den rechtsseitigen Teilstring einer
   /// bestimmten Länge.
   /// @param val Zu ändernder String
   /// @param length Teilstring-Länge
   BASEDLL void Right (std::string& val, int length);

   /// @brief Füllt einen String linksseitig bis zur gewünschten Länge mit
   /// einem oder mehreren Zeichen auf.
   /// @param val Zu ändernder String
   /// @param length Füll-Länge
   /// @param filling Füll-String
   BASEDLL void LFill (std::string& val, int length, const std::string& filling = " ");

   /// @brief Füllt einen String rechtsseitig bis zur gewünschten Länge mit
   /// einem oder mehreren Zeichen auf.
   /// @param val Zu ändernder String
   /// @param length Füll-Länge
   /// @param filling Füll-String
   BASEDLL void RFill (std::string& val, int length, const std::string& filling = " ");



   /// @brief Liefert eine Kopie des Strings ohne linksseitige Leerzeichen.
   BASEDLL std::string LTrim (const std::string& val);

   /// @brief Liefert eine Kopie des Strings ohne rechtsseitige Leerzeichen.
   BASEDLL std::string RTrim (const std::string& val);

   /// @brief Liefert eine Kopie des Strings ohne links- und rechtsseitige
   /// Leerzeichen.
   BASEDLL std::string Trim (const std::string& val);

   /// @brief Liefert eine Kopie des Strings in Großbuchstaben.
   BASEDLL std::string Upper (const std::string& val);

   /// @brief Liefert eine Kopie des Strings in Kleinbuchstaben.
   BASEDLL std::string Lower (const std::string& val);

   /// @brief Liefert eine Kopie des Strings, in dem die angegebene
   /// Zeichenfolge durch eine andere ersetzt wurde.
   /// @param src Original-String
   /// @param what Zu ersetzende Zeichenfolge
   /// @param with Zeichenfolge, die statt _what_ eingesetzt werden soll
   BASEDLL std::string Replace (const std::string& src, const std::string& what, const std::string& with);

   /// @brief Liefert einen linksseitigen Teilstring einer bestimmten Länge.
   /// @param val Original-String
   /// @param length Teilstring-Länge
   BASEDLL std::string Left (const std::string& val, int length);

   /// @brief Liefert einen rechtsseitigen Teilstring einer bestimmten Länge.
   /// @param val Original-String
   /// @param length Teilstring-Länge
   BASEDLL std::string Right (const std::string& val, int length);

   /// @brief Liefert eine Kopie des Strings, die linksseitig bis zur
   /// gewünschten Länge mit einem oder mehreren Zeichen aufgefüllt wurde.
   /// @param val Original-String
   /// @param length Füll-Länge
   /// @param filling Füll-String
   BASEDLL std::string LFill (const std::string& val, int length, const std::string& filling = " ");

   /// @brief Liefert eine Kopie des Strings, die rechtsseitig bis zur
   /// gewünschten Länge mit einem oder mehreren Zeichen aufgefüllt wurde.
   /// @param val Original-String
   /// @param length Füll-Länge
   /// @param filling Füll-String
   BASEDLL std::string RFill (const std::string& val, int length, const std::string& filling = " ");

   /// @brief Liefert alle Buchstaben aus einem String.
   BASEDLL std::string Letters (const std::string& val);

   /// @brief Liefert alle Ziffern aus einem String.
   BASEDLL std::string Digits (const std::string& val);

   /// @brief Liefert alle Buchstaben und alle Ziffern aus einem String.
   BASEDLL std::string LettersDigits (const std::string& val);

   /// @brief Zerlegt einen String unter Berücksichtingung eines Trenners und
   /// gibt die Teilstrings als Vektor zurück.
   /// @param val Zu zerlegender String
   /// @param seperator Trenner
   BASEDLL std::vector<std::string> Split (const std::string& val, const std::string& seperator = "\n");

   /// @brief Fügt einzelne Strings aus einem String-Vektor unter Verwendung
   /// eines Trenners zu einem String zusammen und gibt diesen zurück.
   /// @param vals Zusammenzufügender String-Vektor
   /// @param seperator Trenner
   BASEDLL std::string Join (const std::vector<std::string>& vals, const std::string& seperator = "\n");

}

