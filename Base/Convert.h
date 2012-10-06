
#pragma once

#include "DLL_DEF.h"


/// @brief Namespace für allgemeine Basisfunktionen aus verschiedenen Bereichen.
namespace base {

   /// @brief Konvertiert std::string in bool.
   /// @retval true wenn der Inhalt des Strings mit einer Vorgabe in constants::checkBool übereinstimmt
   /// @retval false in allen anderen Fällen
   BASEDLL bool AsBool (const std::string& val);

   /// @brief Konvertiert int in bool.
   /// @retval true wenn val ungleich 0 ist
   /// @retval false wenn val den Wert 0 hat
   BASEDLL bool AsBool (int val);

   /// @brief Konvertiert long in bool.
   /// @retval true wenn val ungleich 0 ist
   /// @retval false wenn val den Wert 0 hat
   BASEDLL bool AsBool (long val);

   /// @brief Konvertiert long long in bool.
   /// @retval true wenn val ungleich 0 ist
   /// @retval false wenn val den Wert 0 hat
   BASEDLL bool AsBool (long long val);

   /// @brief Konvertiert float in bool.
   /// @retval true wenn val ungleich 0 ist
   /// @retval false wenn val den Wert 0 hat
   BASEDLL bool AsBool (float val);

   /// @brief Konvertiert double in bool.
   /// @retval true wenn val ungleich 0 ist
   /// @retval false wenn val den Wert 0 hat
   BASEDLL bool AsBool (double val);

   /// @brief Konvertiert const char* in bool.
   /// @retval true wenn der Inhalt des Strings mit einer Vorgabe in constants::checkBool übereinstimmt
   /// @retval false in allen anderen Fällen
   BASEDLL bool AsBool (const char* val);



   /// @brief Konvertiert std::string in int.
   BASEDLL int AsInt (const std::string& val);

   /// @brief Konvertiert bool in int.
   /// @retval 0 wenn val den Wert false hat
   /// @retval 1 wenn val den Wert true hat
   BASEDLL int AsInt (bool val);

   /// @brief Konvertiert long in int.
   BASEDLL int AsInt (long val);

   /// @brief Konvertiert long long in int.
   BASEDLL int AsInt (long long val);

   /// @brief Konvertiert float in int.
   BASEDLL int AsInt (float val);

   /// @brief Konvertiert double in int.
   BASEDLL int AsInt (double val);

   /// @brief Konvertiert const char* in int.
   BASEDLL int AsInt (const char* val);



   /// @brief Konvertiert std::string in long.
   BASEDLL long AsLong (const std::string& val);

   /// @brief Konvertiert bool in long.
   /// @retval 0 wenn val den Wert false hat
   /// @retval 1 wenn val den Wert true hat
   BASEDLL long AsLong (bool val);

   /// @brief Konvertiert int in long.
   BASEDLL long AsLong (int val);

   /// @brief Konvertiert long long in long.
   BASEDLL long AsLong (long long val);

   /// @brief Konvertiert float in long.
   BASEDLL long AsLong (float val);

   /// @brief Konvertiert double in long.
   BASEDLL long AsLong (double val);

   /// @brief Konvertiert const char* in long.
   BASEDLL long AsLong (const char* val);



   /// @brief Konvertiert std::string in long long.
   BASEDLL long long AsLongLong (const std::string& val);

   /// @brief Konvertiert bool in long long.
   /// @retval 0 wenn val den Wert false hat
   /// @retval 1 wenn val den Wert true hat
   BASEDLL long long AsLongLong (bool val);

   /// @brief Konvertiert int in long long.
   BASEDLL long long AsLongLong (int val);

   /// @brief Konvertiert long in long long.
   BASEDLL long long AsLongLong (long val);

   /// @brief Konvertiert float in long long.
   BASEDLL long long AsLongLong (float val);

   /// @brief Konvertiert double in long long.
   BASEDLL long long AsLongLong (double val);

   /// @brief Konvertiert const char* in long long.
   BASEDLL long long AsLongLong (const char* val);



   /// @brief Konvertiert std::string in double.
   BASEDLL double AsDouble (const std::string& val);

   /// @brief Konvertiert bool in double.
   /// @retval 0.0 wenn val den Wert false hat
   /// @retval 1.0 wenn val den Wert true hat
   BASEDLL double AsDouble (bool val);

   /// @brief Konvertiert int in double.
   BASEDLL double AsDouble (int val);

   /// @brief Konvertiert long in double.
   BASEDLL double AsDouble (long val);

   /// @brief Konvertiert long long in double.
   BASEDLL double AsDouble (long long val);

   /// @brief Konvertiert float in double.
   BASEDLL double AsDouble (float val);

   /// @brief Konvertiert const char* in double.
   BASEDLL double AsDouble (const char* val);



   /// @brief Konvertiert std::string in float.
   BASEDLL float AsFloat (const std::string& val);

   /// @brief Konvertiert bool in float.
   /// @retval 0.0f wenn val den Wert false hat
   /// @retval 1.0f wenn val den Wert true hat
   BASEDLL float AsFloat (bool val);

   /// @brief Konvertiert int in float.
   BASEDLL float AsFloat (int val);

   /// @brief Konvertiert long in float.
   BASEDLL float AsFloat (long val);

   /// @brief Konvertiert long long in float.
   BASEDLL float AsFloat (long long val);

   /// @brief Konvertiert double in float.
   BASEDLL float AsFloat (double val);

   /// @brief Konvertiert const char* in float.
   BASEDLL float AsFloat (const char* val);



   /// @brief Konvertiert bool in std::string.
   /// @retval False wenn val den Wert false hat
   /// @retval True wenn val den Wert true hat
   BASEDLL const std::string AsString (bool val);

   /// @brief Konvertiert int in std::string.
   /// @param val Zu konvertierender Wert
   /// @param pretty Gibt an, ob der Rückgabewert mit Tausenderpunkten verkleidet werden soll (Standard: true).
   BASEDLL const std::string AsString (int val, bool pretty = true);

   /// @brief Konvertiert long in std::string.
   /// @param val Zu konvertierender Wert
   /// @param pretty Gibt an, ob der Rückgabewert mit Tausenderpunkten verkleidet werden soll (Standard: true).
   BASEDLL const std::string AsString (long val, bool pretty = true);

   /// @brief Konvertiert long long in std::string.
   /// @param val Zu konvertierender Wert
   /// @param pretty Gibt an, ob der Rückgabewert mit Tausenderpunkten verkleidet werden soll (Standard: true).
   BASEDLL const std::string AsString (long long val, bool pretty = true);

   /// @brief Konvertiert float in std::string.
   /// @param val Zu konvertierender Wert
   /// @param decimals Gibt an, wie viele Nachkommastellen im Rückgabewert angegeben werden sollen (Standard: 2).
   /// @param pretty Gibt an, ob der Rückgabewert mit Tausenderpunkten verkleidet werden soll (Standard: true).
   BASEDLL const std::string AsString (float val, int decimals = 2, bool pretty = true);

   /// @brief Konvertiert double in std::string.
   /// @param val Zu konvertierender Wert
   /// @param decimals Gibt an, wie viele Nachkommastellen im Rückgabewert angegeben werden sollen (Standard: 2).
   /// @param pretty Gibt an, ob der Rückgabewert mit Tausenderpunkten verkleidet werden soll (Standard: true).
   BASEDLL const std::string AsString (double val, int decimals = 2, bool pretty = true);



   /// @brief Konvertiert Binärdaten in Stringdaten.
   BASEDLL const std::string AsString (const std::vector<char>& val);

   /// @brief Konvertiert Stringdaten in Binärdaten.
   BASEDLL const std::vector<char> AsBinary (const std::string& val);

   /// @brief Konvertiert std::string in std::wstring.
   BASEDLL const std::wstring AsWString (const std::string& val);
}

