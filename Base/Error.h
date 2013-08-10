
#pragma once

#include "DLL_DEF.h"


/// @brief Namespace für Basisfunktionen zur Fehlerbehandlung.
namespace error {

   /// @brief Erzeugt ein Objekt vom Typ std::exception mit entsprechenden Zusatz-Informationen. Alle anderen Funktionen im Namespace error verwenden diese Funktion.
   /// @param type Fehlertyp
   /// @param message Fehlertext
   /// @param function Funktion, in welcher der Fehler aufgetreten ist. Für diesen Parameter sollte grundsätzlich \__FUNCTION__ oder das Makro ERROR_LOCATION verwendet werden.
   /// @param file Datei, in welcher der Fehler aufgetreten ist. Für diesen Parameter sollte grundsätzlich \__FILE__ verwendet werden. Der Wert wird nur im Debug-Build berücksichtigt.
   /// @param line Zeile, in welcher der Fehler aufgetreten ist. Für diesen Parameter sollte grundsätzlich \__LINE__ verwendet werden. Der Wert wird nur im Debug-Build berücksichtigt.
   BASEDLL std::exception Error (const std::string& type, const std::string& message, const std::string& function, const std::string& file, int line);



   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "already exists error".
   BASEDLL std::exception AlreadyExists (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);



   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "create error".
   BASEDLL std::exception Create (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "read error".
   BASEDLL std::exception Read (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "write error".
   BASEDLL std::exception Write (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "execute error".
   BASEDLL std::exception Execute (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "delete error".
   BASEDLL std::exception Delete (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "copy error".
   BASEDLL std::exception Copy (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "move error".
   BASEDLL std::exception Move (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);



   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "out of memory error".
   BASEDLL std::exception OutOfMemory (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);



   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "invalid parameter error".
   BASEDLL std::exception InvalidParam (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "invalid pointer error".
   BASEDLL std::exception NullPointer (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "bad reference error".
   BASEDLL std::exception BadReference (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "bad format error".
   BASEDLL std::exception BadFormat (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "query error".
   BASEDLL std::exception Query (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);



   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "not available error".
   BASEDLL std::exception NotAvailable (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "not found error".
   BASEDLL std::exception NotFound (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "no data error".
   BASEDLL std::exception NoData (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);



   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "not allowed error".
   BASEDLL std::exception NotAllowed (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   /// @brief Erzeugt eine Ausnahme für den Fehlerfall "not implemented error".
   BASEDLL std::exception NotImplemented (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);



   /// @brief Kurzschreibweise für die zu übergebenden Zusatzattribute (Funktionsname, Datei, Zeile).
   #define ERROR_LOCATION __FUNCTION__, __FILE__, __LINE__

}

