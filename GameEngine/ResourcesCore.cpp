
#include "Precomp.h"

#include <irrKlang.h>

#include "ResourcesCore.h"

#include "../Base/File.h"
#include "../Base/Error.h"

using namespace base;


namespace ge {

   void ResourcesCore::Add (const std::string& id, const std::string& path, std::map<std::string, std::string>& map)
   {
      if (id.empty())                     throw error::InvalidParam("No id specified!", __FUNCTION__);
      else if (path.empty())              throw error::InvalidParam("No path specified!", __FUNCTION__);
      else if (map.find(id) != map.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in map!", __FUNCTION__);

      map.insert(std::make_pair(id, LoadString(path)));
   }

   void ResourcesCore::Add (const std::string& id, const std::string& path, std::map<std::string, std::vector<char>>& map)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);
      else if (path.empty()) throw error::InvalidParam("No path specified!", __FUNCTION__);
      else if (map.find(id) != map.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in map!", __FUNCTION__);

      map.insert(std::make_pair(id, LoadBinary(path)));
   }

   void ResourcesCore::Remove (const std::string& id, std::map<std::string, std::string>& map)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      const auto res = map.find(id);
      if (res != map.end()) map.erase(res);
   }

   void ResourcesCore::Remove (const std::string& id, std::map<std::string, std::vector<char>>& map)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      const auto res = map.find(id);
      if (res != map.end()) map.erase(res);
   }

   const std::string& ResourcesCore::Find (const std::string& id, const std::map<std::string, std::string>& map) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      const auto res = map.find(id);
      if (res == map.end()) throw error::NotFound("Resource with id \"" + id + "\" does not exist!", __FUNCTION__);

      return res->second;
   }

   const std::vector<char>& ResourcesCore::Find (const std::string& id, const std::map<std::string, std::vector<char>>& map) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      const auto res = map.find(id);
      if (res == map.end()) throw error::NotFound("Resource with id \"" + id + "\" does not exist!", __FUNCTION__);

      return res->second;
   }

}

