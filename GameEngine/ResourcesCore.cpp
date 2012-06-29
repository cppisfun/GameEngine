
#include "Precomp.h"

#include <irrKlang.h>

#include "ResourcesCore.h"

#include "../Base/File.h"
#include "../Base/Error.h"

using namespace base;


ResourcesCore::ResourcesCore ()
{
   Init();
}

ResourcesCore::~ResourcesCore ()
{
}

void ResourcesCore::Init ()
{
}

ResourcesCore& ResourcesCore::AddString (const std::string& id, const std::string& path)
{
   if (id.empty())                             throw error::InvalidParam("No id specified!", __FUNCTION__);
   else if (path.empty())                      throw error::InvalidParam("No path specified!", __FUNCTION__);
   else if (strings.find(id) != strings.end()) throw error::AlreadyExists("String resource with specified id already exists!", __FUNCTION__);

   strings[id] = LoadString(path);
   return *this;
}

ResourcesCore& ResourcesCore::AddBinary (const std::string& id, const std::string& path)
{
   if (id.empty())                               throw error::InvalidParam("No id specified!", __FUNCTION__);
   else if (path.empty())                        throw error::InvalidParam("No path specified!", __FUNCTION__);
   else if (binaries.find(id) != binaries.end()) throw error::AlreadyExists("String resource with specified id already exists!", __FUNCTION__);

   binaries[id] = LoadBinary(path);
   return *this;
}

ResourcesCore& ResourcesCore::AddScript (const std::string& id, const std::string& path)
{
   if (id.empty())                             throw error::InvalidParam("No id specified!", __FUNCTION__);
   else if (path.empty())                      throw error::InvalidParam("No path specified!", __FUNCTION__);
   else if (scripts.find(id) != scripts.end()) throw error::AlreadyExists("String resource with specified id already exists!", __FUNCTION__);

   scripts[id] = LoadString(path);
   return *this;
}

ResourcesCore& ResourcesCore::AddXML (const std::string& id, const std::string& path)
{
   if (id.empty())                       throw error::InvalidParam("No id specified!", __FUNCTION__);
   else if (path.empty())                throw error::InvalidParam("No path specified!", __FUNCTION__);
   else if (xmls.find(id) != xmls.end()) throw error::AlreadyExists("String resource with specified id already exists!", __FUNCTION__);

   xmls[id] = LoadString(path);
   return *this;
}

ResourcesCore& ResourcesCore::RemoveString (const std::string& id)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto res = strings.find(id);
   if (res != strings.end()) strings.erase(res);

   return *this;
}

ResourcesCore& ResourcesCore::RemoveBinary (const std::string& id)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto res = binaries.find(id);
   if (res != binaries.end()) binaries.erase(res);

   return *this;
}

ResourcesCore& ResourcesCore::RemoveScript (const std::string& id)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto res = scripts.find(id);
   if (res != scripts.end()) scripts.erase(res);

   return *this;
}

ResourcesCore& ResourcesCore::RemoveXML (const std::string& id)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto res = xmls.find(id);
   if (res != xmls.end()) xmls.erase(res);

   return *this;
}

const std::string& ResourcesCore::String (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto res = strings.find(id);
   if (res == strings.end()) throw error::NotFound("String resource with specified id does not exist!", __FUNCTION__);

   return res->second;
}

const std::vector<char>& ResourcesCore::Binary (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto res = binaries.find(id);
   if (res == binaries.end()) throw error::NotFound("String resource with specified id does not exist!", __FUNCTION__);

   return res->second;
}

const std::string& ResourcesCore::Script (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto res = scripts.find(id);
   if (res == scripts.end()) throw error::NotFound("String resource with specified id does not exist!", __FUNCTION__);

   return res->second;
}

const std::string& ResourcesCore::XML (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto res = xmls.find(id);
   if (res == xmls.end()) throw error::NotFound("String resource with specified id does not exist!", __FUNCTION__);

   return res->second;
}

