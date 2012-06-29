
#pragma once

#include "DLL_DEF.h"


namespace base {

   BASEDLL void CurrentDir (const std::string& path);
   BASEDLL void CreateDir (const std::string& path, bool removeExisting = false);
   BASEDLL void RemoveDir (const std::string& path, bool removeContents = false);

   BASEDLL void CreateFile (const std::string& path, bool removeExisting = false);
   BASEDLL void RemoveFile (const std::string& path);
   BASEDLL void CopyFile (const std::string& srcPath, const std::string& dstPath, bool removeExisting = false);
   BASEDLL void MoveFile (const std::string& srcPath, const std::string& dstPath, bool removeExisting = false);
   BASEDLL void RenameFile (const std::string& oldName, const std::string& newName, const std::string& path = "", bool removeExisting = false);
   BASEDLL void Save (const std::string& path, const std::string& content, bool append = false, bool removeExisting = false);
   BASEDLL void Save (const std::string& path, const std::vector<char>& content, bool append = false, bool removeExisting = false);

   BASEDLL const std::string CurrentDir ();
   BASEDLL bool ExistDir (const std::string& path);

   BASEDLL bool ExistFile (const std::string& path);
   BASEDLL const std::string LoadString (const std::string& path);
   BASEDLL const std::vector<char> LoadBinary (const std::string& path);

}

