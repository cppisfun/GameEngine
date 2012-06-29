
#pragma once


class ResourcesCore
{
   std::map<std::string, std::string> strings;
   std::map<std::string, std::vector<char>> binaries;
   std::map<std::string, std::string> scripts;
   std::map<std::string, std::string> xmls;

   void Init ();

public:
   ResourcesCore ();
   virtual ~ResourcesCore ();

   ResourcesCore& AddString (const std::string& id, const std::string& path);
   ResourcesCore& AddBinary (const std::string& id, const std::string& path);
   ResourcesCore& AddScript (const std::string& id, const std::string& path);
   ResourcesCore& AddXML (const std::string& id, const std::string& path);

   ResourcesCore& RemoveString (const std::string& id);
   ResourcesCore& RemoveBinary (const std::string& id);
   ResourcesCore& RemoveScript (const std::string& id);
   ResourcesCore& RemoveXML (const std::string& id);

   const std::string& String (const std::string& id) const;
   const std::vector<char>& Binary (const std::string& id) const;
   const std::string& Script (const std::string& id) const;
   const std::string& XML (const std::string& id) const;
};

