
#include "Precomp.h"

#include "ResourcesManager.h"

#include "../Base/File.h"
#include "../Base/Error.h"

using namespace base;


namespace ge {

   void ResourcesManager::Add (const std::string& id, const std::string& path, std::map<std::string, std::string>& map)
   {
      if (id.empty())                     throw error::InvalidParam("No id specified!", ERROR_LOCATION);
      else if (path.empty())              throw error::InvalidParam("No path specified!", ERROR_LOCATION);
      else if (map.find(id) != map.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in map!", ERROR_LOCATION);

      map.insert(std::make_pair(id, LoadString(path)));
   }

   void ResourcesManager::Add (const std::string& id, const std::string& path, std::map<std::string, Binary>& map)
   {
      if (id.empty())                     throw error::InvalidParam("No id specified!", ERROR_LOCATION);
      else if (path.empty())              throw error::InvalidParam("No path specified!", ERROR_LOCATION);
      else if (map.find(id) != map.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in map!", ERROR_LOCATION);

      map.insert(std::make_pair(id, LoadBinary(path)));
   }

   void ResourcesManager::Remove (const std::string& id, std::map<std::string, std::string>& map)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      const auto res = map.find(id);
      if (res != map.end()) map.erase(res);
   }

   void ResourcesManager::Remove (const std::string& id, std::map<std::string, Binary>& map)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      const auto res = map.find(id);
      if (res != map.end()) map.erase(res);
   }

   const std::string& ResourcesManager::Find (const std::string& id, const std::map<std::string, std::string>& map) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      const auto res = map.find(id);
      if (res == map.end()) throw error::NotFound("Resource with id \"" + id + "\" does not exist!", ERROR_LOCATION);

      return res->second;
   }

   const Binary& ResourcesManager::Find (const std::string& id, const std::map<std::string, Binary>& map) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      const auto res = map.find(id);
      if (res == map.end()) throw error::NotFound("Resource with id \"" + id + "\" does not exist!", ERROR_LOCATION);

      return res->second;
   }

}

