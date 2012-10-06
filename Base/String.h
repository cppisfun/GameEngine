
#pragma once

#include "DLL_DEF.h"


namespace base {

   /// @brief Liefert einen String ohne linksseitige Leerzeichen.
   BASEDLL const std::string LTrim (const std::string& val);

   /// @brief Entfernt alle rechtsseitigen Leerzeichen.
   BASEDLL const std::string RTrim (const std::string& val);

   /// @brief Entfernt alle linksseitigen und alle rechtsseitigen Leerzeichen.
   BASEDLL const std::string Trim (const std::string& val);



   /// @brief F�llt einen String linksseitig bis zur gew�nschten L�nge mit einem oder mehr Zeichen auf.
   /// @param val Original-String
   /// @param length F�ll-L�nge
   /// @param filling F�ll-String
   BASEDLL const std::string LFill (const std::string& val, int length, const std::string& filling = " ");

   /// @brief F�llt einen String rechtsseitig bis zur gew�nschten L�nge mit einem oder mehr Zeichen auf.
   /// @param val Original-String
   /// @param length F�ll-L�nge
   /// @param filling F�ll-String
   BASEDLL const std::string RFill (const std::string& val, int length, const std::string& filling = " ");



   /// @brief Liefert einen linksseitigen Teilstring einer bestimmten L�nge.
   /// @param val Original-String
   /// @param length Teilstring-L�nge
   BASEDLL const std::string Left (const std::string& val, int length);

   /// @brief Liefert einen rechtsseitigen Teilstring einer bestimmten L�nge.
   /// @param val Original-String
   /// @param length Teilstring-L�nge
   BASEDLL const std::string Right (const std::string& val, int length);



   /// @brief Liefert den angegebenen String in Gro�buchstaben.
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

