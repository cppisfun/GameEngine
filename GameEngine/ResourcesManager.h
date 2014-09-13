
#pragma once

#include "DLL_DEF.h"


namespace ge {

   class GEDLL ResourcesManager
   {
      typedef std::map<std::string, std::string> StringMap;
      typedef std::map<std::string, Binary>      BinaryMap;

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
      const Binary& Find (const std::string& id, const BinaryMap& map) const;

   public:
      ResourcesManager ()          { }
      virtual ~ResourcesManager () { }

      ResourcesManager& AddStringResource (const std::string& id, const std::string& path) { Add(id, path, strings); return *this; }
      ResourcesManager& AddScript (const std::string& id, const std::string& path)         { Add(id, path, scripts); return *this; }
      ResourcesManager& AddXML (const std::string& id, const std::string& path)            { Add(id, path, xmls); return *this; }

      ResourcesManager& AddBinaryResource (const std::string& id, const std::string& path) { Add(id, path, binaries); return *this; }
      ResourcesManager& AddMusic (const std::string& id, const std::string& path)          { Add(id, path, musics); return *this; }
      ResourcesManager& AddSound (const std::string& id, const std::string& path)          { Add(id, path, sounds); return *this; }

      ResourcesManager& RemoveStringResource (const std::string& id) { Remove(id, strings); return *this; }
      ResourcesManager& RemoveScript (const std::string& id)         { Remove(id, scripts); return *this; }
      ResourcesManager& RemoveXML (const std::string& id)            { Remove(id, xmls); return *this; }

      ResourcesManager& RemoveBinaryResource (const std::string& id) { Remove(id, binaries); return *this; }
      ResourcesManager& RemoveMusic (const std::string& id)          { Remove(id, musics); return *this; }
      ResourcesManager& RemoveSound (const std::string& id)          { Remove(id, sounds); return *this; }

      ResourcesManager& RemoveAllStringResources () { strings.clear(); return *this; }
      ResourcesManager& RemoveAllScripts ()         { scripts.clear(); return *this; }
      ResourcesManager& RemoveAllXMLs ()            { xmls.clear(); return *this; }

      ResourcesManager& RemoveAllBinaryResources () { binaries.clear(); return *this; }
      ResourcesManager& RemoveAllMusic ()           { musics.clear(); return *this; }
      ResourcesManager& RemoveAllSounds ()          { sounds.clear(); return *this; }

      const std::string& StringResource (const std::string& id) const { return Find(id, strings); }
      const std::string& Script (const std::string& id) const         { return Find(id, scripts); }
      const std::string& XML (const std::string& id) const            { return Find(id, xmls); }

      const Binary& BinaryResource (const std::string& id) const { return Find(id, binaries); }
      const Binary& Music (const std::string& id) const          { return Find(id, musics); }
      const Binary& Sound (const std::string& id) const          { return Find(id, sounds); }
   };

}

