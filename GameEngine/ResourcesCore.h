
#pragma once

#include "DLL_DEF.h"


namespace ge {

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
      BinaryMap textures;

      void Add (const std::string& id, const std::string& path, StringMap& map);
      void Add (const std::string& id, const std::string& path, BinaryMap& map);
      void Remove (const std::string& id, StringMap& map);
      void Remove (const std::string& id, BinaryMap& map);

      const std::string& Find (const std::string& id, const StringMap& map) const;
      const std::vector<char>& Find (const std::string& id, const BinaryMap& map) const;

   public:
      ResourcesCore ()          { }
      virtual ~ResourcesCore () { }

      ResourcesCore& AddString (const std::string& id, const std::string& path) { Add(id, path, strings); return *this; }
      ResourcesCore& AddScript (const std::string& id, const std::string& path) { Add(id, path, scripts); return *this; }
      ResourcesCore& AddXML (const std::string& id, const std::string& path)    { Add(id, path, xmls); return *this; }

      ResourcesCore& AddBinary (const std::string& id, const std::string& path)  { Add(id, path, binaries); return *this; }
      ResourcesCore& AddMusic (const std::string& id, const std::string& path)   { Add(id, path, musics); return *this; }
      ResourcesCore& AddSound (const std::string& id, const std::string& path)   { Add(id, path, sounds); return *this; }
      ResourcesCore& AddTexture (const std::string& id, const std::string& path) { Add(id, path, textures); return *this; }

      ResourcesCore& RemoveString (const std::string& id) { Remove(id, strings); return *this; }
      ResourcesCore& RemoveScript (const std::string& id) { Remove(id, scripts); return *this; }
      ResourcesCore& RemoveXML (const std::string& id)    { Remove(id, xmls); return *this; }

      ResourcesCore& RemoveBinary (const std::string& id)  { Remove(id, binaries); return *this; }
      ResourcesCore& RemoveMusic (const std::string& id)   { Remove(id, musics); return *this; }
      ResourcesCore& RemoveSound (const std::string& id)   { Remove(id, sounds); return *this; }
      ResourcesCore& RemoveTexture (const std::string& id) { Remove(id, textures); return *this; }

      ResourcesCore& RemoveAllStrings () { strings.clear(); return *this; }
      ResourcesCore& RemoveAllScripts () { scripts.clear(); return *this; }
      ResourcesCore& RemoveAllXMLs ()    { xmls.clear(); return *this; }

      ResourcesCore& RemoveAllBinaries () { binaries.clear(); return *this; }
      ResourcesCore& RemoveAllMusic ()    { musics.clear(); return *this; }
      ResourcesCore& RemoveAllSounds ()   { sounds.clear(); return *this; }
      ResourcesCore& RemoveAllTextures () { textures.clear(); return *this; }

      const std::string& String (const std::string& id) const { return Find(id, strings); }
      const std::string& Script (const std::string& id) const { return Find(id, scripts); }
      const std::string& XML (const std::string& id) const    { return Find(id, xmls); }

      const std::vector<char>& Binary (const std::string& id) const  { return Find(id, binaries); }
      const std::vector<char>& Music (const std::string& id) const   { return Find(id, musics); }
      const std::vector<char>& Sound (const std::string& id) const   { return Find(id, sounds); }
      const std::vector<char>& Texture (const std::string& id) const { return Find(id, textures); }
   };

}

