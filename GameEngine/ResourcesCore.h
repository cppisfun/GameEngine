
#pragma once

#include "DLL_DEF.h"


namespace ge {

   /// @brief Ressourcen-Basisklasse zur Verwaltung Text- und Bin�r-Ressourcen.
   /// Wird �ber Core::Resources() geliefert.
   class GEDLL ResourcesCore
   {
      typedef std::map<std::string, std::string>       StringMap;
      typedef std::map<std::string, std::vector<char>> BinaryMap;

      StringMap strings;
      StringMap scripts;
      StringMap xmls;

      BinaryMap binaries;
      BinaryMap musics;
      BinaryMap sounds;

      void Add (const std::string& id, const std::string& path, StringMap& map);
      void Add (const std::string& id, const std::string& path, BinaryMap& map);
      void Remove (const std::string& id, StringMap& map);
      void Remove (const std::string& id, BinaryMap& map);

      const std::string& Find (const std::string& id, const StringMap& map) const;
      const std::vector<char>& Find (const std::string& id, const BinaryMap& map) const;

   public:
      /// @brief Konstruktor.
      ResourcesCore () { }

      /// @brief Destruktor. Entfernt automatisch alle in ResourcesCore
      /// gehaltenen Text- und Bin�r-Ressourcen.
      virtual ~ResourcesCore () { }


      /// @brief F�gt eine String-Ressource aus einer Datei hinzu (Textdaten).
      ///
      /// Diese Ressourcen-Art sollte nur verwendet werden, wenn sich die Art
      /// der Daten nicht in direkter Form von ResourcesCore verwalten l�sst.
      /// @param id Eindeutiger Bezeichner der String-Ressource
      /// @param path Dateipfad
      ResourcesCore& AddString (const std::string& id, const std::string& path) { Add(id, path, strings); return *this; }

      /// @brief F�gt eine Script-Ressource aus einer Datei hinzu (Textdaten).
      /// @param id Eindeutiger Bezeichner der Script-Ressource
      /// @param path Dateipfad
      ResourcesCore& AddScript (const std::string& id, const std::string& path) { Add(id, path, scripts); return *this; }

      /// @brief F�gt eine XML-Ressource aus einer Datei hinzu (Textdaten).
      /// @param id Eindeutiger Bezeichner der XML-Ressource
      /// @param path Dateipfad
      ResourcesCore& AddXML (const std::string& id, const std::string& path) { Add(id, path, xmls); return *this; }


      /// @brief F�gt eine Bin�r-Ressource aus einer Datei hinzu (Bin�rdaten).
      ///
      /// Diese Ressourcen-Art sollte nur verwendet werden, wenn sich die Art
      /// der Daten nicht in direkter Form von ResourcesCore verwalten l�sst.
      /// @param id Eindeutiger Bezeichner der Bin�r-Ressource
      /// @param path Dateipfad
      ResourcesCore& AddBinary (const std::string& id, const std::string& path) { Add(id, path, binaries); return *this; }

      /// @brief F�gt eine Musik-Ressource aus einer Datei hinzu (Bin�rdaten).
      /// @param id Eindeutiger Bezeichner der Musik-Ressource
      /// @param path Dateipfad
      ResourcesCore& AddMusic (const std::string& id, const std::string& path) { Add(id, path, musics); return *this; }

      /// @brief F�gt eine Sound-Ressource aus einer Datei hinzu (Bin�rdaten).
      /// @param id Eindeutiger Bezeichner der Sound-Ressource
      /// @param path Dateipfad
      ResourcesCore& AddSound (const std::string& id, const std::string& path) { Add(id, path, sounds); return *this; }


      /// @brief Entfernt eine String-Ressource.
      ResourcesCore& RemoveString (const std::string& id) { Remove(id, strings); return *this; }

      /// @brief Entfernt eine Script-Ressource.
      ResourcesCore& RemoveScript (const std::string& id) { Remove(id, scripts); return *this; }

      /// @brief Entfernt eine XML-Ressource.
      ResourcesCore& RemoveXML (const std::string& id) { Remove(id, xmls); return *this; }


      /// @brief Entfernt eine Bin�r-Ressource.
      ResourcesCore& RemoveBinary (const std::string& id) { Remove(id, binaries); return *this; }

      /// @brief Entfernt eine Musik-Ressource.
      ResourcesCore& RemoveMusic (const std::string& id) { Remove(id, musics); return *this; }

      /// @brief Entfernt eine Sound-Ressource.
      ResourcesCore& RemoveSound (const std::string& id) { Remove(id, sounds); return *this; }


      /// @brief Entfernt alle String-Ressourcen.
      ResourcesCore& RemoveAllStrings () { strings.clear(); return *this; }

      /// @brief Entfernt alle Script-Ressourcen.
      ResourcesCore& RemoveAllScripts () { scripts.clear(); return *this; }

      /// @brief Entfernt alle XML-Ressourcen.
      ResourcesCore& RemoveAllXMLs () { xmls.clear(); return *this; }


      /// @brief Entfernt alle Bin�r-Ressourcen.
      ResourcesCore& RemoveAllBinaries () { binaries.clear(); return *this; }

      /// @brief Entfernt alle Musik-Ressourcen.
      ResourcesCore& RemoveAllMusic () { musics.clear(); return *this; }

      /// @brief Entfernt alle Sound-Ressourcen.
      ResourcesCore& RemoveAllSounds () { sounds.clear(); return *this; }


      /// @brief Liefert eine String-Ressource (Textdaten).
      const std::string& String (const std::string& id) const { return Find(id, strings); }

      /// @brief Liefert eine Script-Ressource (Textdaten).
      const std::string& Script (const std::string& id) const { return Find(id, scripts); }

      /// @brief Liefert eine XML-Ressource (Textdaten).
      const std::string& XML (const std::string& id) const { return Find(id, xmls); }


      /// @brief Liefert eine Bin�r-Ressource (Bin�rdaten).
      const std::vector<char>& Binary (const std::string& id) const { return Find(id, binaries); }

      /// @brief Liefert eine Musik-Ressource (Bin�rdaten).
      const std::vector<char>& Music (const std::string& id) const { return Find(id, musics); }

      /// @brief Liefert eine Sound-Ressource (Bin�rdaten).
      const std::vector<char>& Sound (const std::string& id) const { return Find(id, sounds); }
   };

}

