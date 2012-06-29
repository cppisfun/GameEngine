
#include "Precomp.h"

#include <boost/filesystem.hpp>
#include <Windows.h>

#include "File.h"

#include "../Base/Error.h"

using namespace boost;


namespace base {

   void CurrentDir (const std::string& path)
   {
      if (path.empty())        throw error::InvalidParam("No path specified!", __FUNCTION__);
      else if (ExistDir(path)) filesystem::current_path(path);
   }

   void CreateDir (const std::string& path, bool removeExisting)
   {
      if (path.empty()) throw error::InvalidParam("No path specified!", __FUNCTION__);

      if (ExistDir(path)) {
         if (!removeExisting) return;
         filesystem::remove_all(path);
      }

      if (!filesystem::create_directories(path)) throw error::Create("Failed to create directory path!", __FUNCTION__);
   }

   void RemoveDir (const std::string& path, bool removeContents)
   {
      if (path.empty())                                        throw error::InvalidParam("No path specified!", __FUNCTION__);
      else if (!ExistDir(path))                                return;
      else if (!filesystem::is_empty(path) && !removeContents) throw error::Delete("Specified path is not empty!", __FUNCTION__);

      filesystem::remove_all(path);
   }

   void CreateFile (const std::string& path, bool removeExisting)
   {
      if (path.empty())                            throw error::InvalidParam("No path specified!", __FUNCTION__);
      else if (ExistFile(path) && !removeExisting) return;

      Save(path, "", false, true);
   }

   void RemoveFile (const std::string& path)
   {
      if (path.empty())          throw error::InvalidParam("No path specified!", __FUNCTION__);
      else if (!ExistFile(path)) return;

      if (!filesystem::remove(path)) throw error::Delete("Failed to delete file!", __FUNCTION__);
   }

   void CopyFile (const std::string& srcPath, const std::string& dstPath, bool removeExisting)
   {
      if (srcPath.empty())                            throw error::InvalidParam("No source path specified!", __FUNCTION__);
      else if (dstPath.empty())                       throw error::InvalidParam("No destination path specified!", __FUNCTION__);
      else if (!ExistFile(srcPath))                   throw error::NotFound("Specified source path does not exist!", __FUNCTION__);
      else if (ExistFile(dstPath) && !removeExisting) throw error::AlreadyExists("Specified destination path already exists!", __FUNCTION__);

      filesystem::copy_file(srcPath, dstPath, filesystem::copy_option::overwrite_if_exists);
   }

   void MoveFile (const std::string& srcPath, const std::string& dstPath, bool removeExisting)
   {
      if (srcPath.empty())          throw error::InvalidParam("No source path specified!", __FUNCTION__);
      else if (dstPath.empty())     throw error::InvalidParam("No destination path specified!", __FUNCTION__);
      else if (!ExistFile(srcPath)) throw error::NotFound("Specified source path does not exist!", __FUNCTION__);

      if (ExistFile(dstPath)) {
         if (!removeExisting)                   throw error::AlreadyExists("Specified destination path already exists!", __FUNCTION__);
         else if (!filesystem::remove(dstPath)) throw error::Delete("Failed to delete file!", __FUNCTION__);
      }

      filesystem::rename(srcPath, dstPath);
   }

   void RenameFile (const std::string& srcName, const std::string& dstName, const std::string& path, bool removeExisting)
   {
      if (srcName.empty())      throw error::InvalidParam("No source file name specified!", __FUNCTION__);
      else if (dstName.empty()) throw error::InvalidParam("No destination file name specified!", __FUNCTION__);

      const std::string srcPath((path.empty()) ? (CurrentDir() + "\\" + srcName) : (path + "\\" + srcName));
      const std::string dstPath((path.empty()) ? (CurrentDir() + "\\" + dstName) : (path + "\\" + dstName));

      MoveFile(srcPath, dstPath, removeExisting);
   }

   void Save (const std::string& path, const std::string& content, bool append, bool removeExisting)
   {
      if (path.empty()) throw error::InvalidParam("No path specified!", __FUNCTION__);

      if (ExistFile(path)) {
         if (removeExisting) CreateFile(path, true);
         else if (!append)   throw error::AlreadyExists("Specified path already exists!", __FUNCTION__);
      }

      HANDLE file = ::CreateFile(path.c_str(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
      if (file == nullptr) throw error::Create("Failed to create file handle!", __FUNCTION__);

      DWORD bytesWritten = 0;

      if (!::WriteFile(file, content.c_str(), content.size(), &bytesWritten, nullptr)) {
         if (file != nullptr) ::CloseHandle(file);
         throw error::Write("Failed to write to file!", __FUNCTION__);
      }

      if (file != nullptr) ::CloseHandle(file);
   }

   void Save (const std::string& path, const std::vector<char>& content, bool append, bool removeExisting)
   {
      Save(path, std::string(content.begin(), content.end()), append, removeExisting);
   }

   const std::string CurrentDir ()
   {
      return filesystem::current_path().string();
   }

   bool ExistDir (const std::string& path)
   {
      if (path.empty()) throw error::InvalidParam("No path specified!", __FUNCTION__);

      filesystem::path tmp(path);
      if (filesystem::exists(tmp)) {
         if (!filesystem::is_directory(tmp)) throw error::InvalidParam("Specified path is not a directory!", __FUNCTION__);
         else                                return true;
      }

      return false;
   }

   bool ExistFile (const std::string& path)
   {
      if (path.empty()) throw error::InvalidParam("No path specified!", __FUNCTION__);

      filesystem::path tmp(path);
      if (filesystem::exists(tmp)) {
         if (!filesystem::is_regular_file(tmp)) throw error::InvalidParam("Specified path is not a file!", __FUNCTION__);
         else                                   return true;
      }

      return false;
   }

   const std::string LoadString (const std::string& path)
   {
      const auto content = LoadBinary(path);
      return std::string(content.begin(), content.end());
   }

   const std::vector<char> LoadBinary (const std::string& path)
   {
      if (path.empty()) throw error::InvalidParam("No path specified!", __FUNCTION__);
      else if (!ExistFile(path)) throw error::NotFound("Specified path does not exist!", __FUNCTION__);

      HANDLE file = ::CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
      if (file == nullptr) throw error::Create("Failed to create file handle!", __FUNCTION__);

      DWORD fileSize  = ::GetFileSize(file, nullptr);
      DWORD bytesRead = 0;
      void* buffer    = malloc(fileSize);

      if (buffer == nullptr) {
         if (file != nullptr) ::CloseHandle(file);
         throw error::OutOfMemory("Not enough memory available for binary resource!", __FUNCTION__);
      }

      ZeroMemory(buffer, fileSize);

      if (!::ReadFile(file, buffer, fileSize, &bytesRead, nullptr)) {
         if (buffer != nullptr) delete buffer;
         if (file != nullptr) ::CloseHandle(file);
         throw error::Read("Failed to read from file!", __FUNCTION__);
      }

      char* charBuffer = (char*)buffer;
      std::vector<char> content(charBuffer, charBuffer + fileSize);

      if (buffer != nullptr) delete buffer;
      if (file != nullptr) ::CloseHandle(file);

      return content;
   }

}

