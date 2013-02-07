
#pragma once

#include "DLL_DEF.h"


namespace base {

   /// @brief Ändert das aktuelle Arbeitsverzeichnis.
   /// @param path Verzeichnispfad
   BASEDLL void CurrentDir (const std::string& path);

   /// @brief Legt ein Verzeichnis an.
   /// @param path Verzeichnispfad
   /// @param removeExisting Gibt an, ob gleichlautende Verzeichnisse entfernt werden sollen (Standard: false)
   BASEDLL void CreateDir (const std::string& path, bool removeExisting = false);

   /// @brief Entfernt ein Verzeichnis.
   /// @param path Verzeichnispfad
   /// @param removeContents Gibt an, ob das Verzeichnis entfernt werden soll, wenn es nicht leer ist (Standard: false)
   BASEDLL void RemoveDir (const std::string& path, bool removeContents = false);



   /// @brief Legt eine Datei an.
   /// @param path Dateipfad
   /// @param removeExisting Gibt an, ob gleichlautende Dateien entfernt werden sollen (Standard: false)
   BASEDLL void CreateFile (const std::string& path, bool removeExisting = false);

   /// @brief Entfernt eine Datei.
   /// @param path Dateipfad
   BASEDLL void RemoveFile (const std::string& path);

   /// @brief Kopiert eine Datei.
   /// @param srcPath Quell-Dateipfad
   /// @param dstPath Ziel-Dateipfad
   /// @param removeExisting Gibt an, ob gleichlautende Dateien gelöscht werden sollen (Standard: false)
   BASEDLL void CopyFile (const std::string& srcPath, const std::string& dstPath, bool removeExisting = false);

   /// @brief Verschiebt eine Datei.
   /// @param srcPath Quell-Dateipfad
   /// @param dstPath Ziel-Dateipfad
   /// @param removeExisting Gibt an, ob gleichlautende Dateien gelöscht werden sollen (Standard: false)
   BASEDLL void MoveFile (const std::string& srcPath, const std::string& dstPath, bool removeExisting = false);

   /// @brief Ändert den Namen einer Datei.
   /// @param oldName Quell-Dateiname
   /// @param newName Ziel-Dateiname
   /// @param path Verzeichnispfad zur Datei (Standard: aktuelles Verzeichnis)
   /// @param removeExisting Gibt an, ob gleichlautende Dateien gelöscht werden sollen (Standard: false)
   BASEDLL void RenameFile (const std::string& oldName, const std::string& newName, const std::string& path = "", bool removeExisting = false);

   /// @brief Speichert Textdaten in einer Datei.
   /// @param path Dateipfad
   /// @param content Zu speichernde Daten
   /// @param append Gibt an, ob die Daten angehängt werden sollen, wenn eine gleichlautende Datei existiert (Standard: false)
   /// @param removeExisting Gibt an, ob gleichlautende Dateien entfernt werden sollen (Standard: false)
   BASEDLL void Save (const std::string& path, const std::string& content, bool append = false, bool removeExisting = false);

   /// @brief Speichert Binärdaten in einer Datei.
   /// @param path Dateipfad
   /// @param content Zu speichernde Daten
   /// @param append Gibt an, ob die Daten angehängt werden sollen, wenn eine gleichlautende Datei existiert (Standard: false)
   /// @param removeExisting Gibt an, ob gleichlautende Dateien entfernt werden sollen (Standard: false)
   BASEDLL void Save (const std::string& path, const Binary& content, bool append = false, bool removeExisting = false);



   /// @brief Liefert das aktuelle Arbeitsverzeichnis.
   BASEDLL const std::string CurrentDir ();

   /// @brief Ermittelt, ob ein Verzeichnis existiert.
   /// @param path Verzeichnispfad
   /// @retval true wenn der Pfad existiert und ein Verzeichnis ist
   /// @retval false in allen anderen Fällen
   BASEDLL bool ExistDir (const std::string& path);



   /// @brief Ermittelt, ob eine Datei existiert.
   /// @param path Dateipfad
   /// @retval true wenn der Pfad existiert und eine Datei ist
   /// @retval false in allen anderen Fällen
   BASEDLL bool ExistFile (const std::string& path);

   /// @brief Liefert Textdaten aus einer Datei.
   /// @param path Dateipfad
   BASEDLL const std::string LoadString (const std::string& path);

   /// @brief Liefert Binärdaten aus einer Datei.
   /// @param path Dateipfad
   BASEDLL const Binary LoadBinary (const std::string& path);

}

