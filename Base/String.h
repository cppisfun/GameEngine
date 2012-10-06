
#pragma once

#include "DLL_DEF.h"


namespace base {

   /// @brief Liefert einen String ohne linksseitige Leerzeichen.
   BASEDLL const std::string LTrim (const std::string& val);

   /// @brief Entfernt alle rechtsseitigen Leerzeichen.
   BASEDLL const std::string RTrim (const std::string& val);

   /// @brief Entfernt alle linksseitigen und alle rechtsseitigen Leerzeichen.
   BASEDLL const std::string Trim (const std::string& val);



   /// @brief Füllt einen String linksseitig bis zur gewünschten Länge mit einem oder mehr Zeichen auf.
   /// @param val Original-String
   /// @param length Füll-Länge
   /// @param filling Fäll-String
   BASEDLL const std::string LFill (const std::string& val, int length, const std::string& filling = " ");

   /// @brief Füllt einen String rechtsseitig bis zur gewünschten Länge mit einem oder mehr Zeichen auf.
   /// @param val Original-String
   /// @param length Füll-Länge
   /// @param filling Fäll-String
   BASEDLL const std::string RFill (const std::string& val, int length, const std::string& filling = " ");



   /// @brief Liefert einen linksseitigen Teilstring einer bestimmten Länge.
   /// @param val Original-String
   /// @param length Teilstring-Länge
   BASEDLL const std::string Left (const std::string& val, int length);

   /// @brief Liefert einen rechtsseitigen Teilstring einer bestimmten Länge.
   /// @param val Original-String
   /// @param length Teilstring-Länge
   BASEDLL const std::string Right (const std::string& val, int length);



   /// @brief Liefert den angegebenen String in Großbuchstaben.
   BASEDLL const std::string Upper (const std::string& val);

   /// @brief Liefert den angegebenen String in Kleinbuchstaben.
   BASEDLL const std::string Lower (const std::string& val);



   /// @brief Liefert alle Buchstaben aus einem String.
   BASEDLL const std::string Letters (const std::string& val);

   /// @brief Liefert alle Ziffern aus einem String.
   BASEDLL const std::string Digits (const std::string& val);

   /// @brief Liefert alle Buchstaben und alle Ziffern aus einem String.
   BASEDLL const std::string LettersDigits (const std::string& val);



   /// @brief Liefert den angegebenen String nach Ersetzung einer Zeichenfolge durch eine andere.
   /// @param src Original-String
   /// @param what Zu ersetzende Zeichenfolge
   /// @param with Zeichenfolge, die statt _what_ eingesetzt werden soll
   BASEDLL const std::string Replace (const std::string& src, const std::string& what, const std::string& with);

}

