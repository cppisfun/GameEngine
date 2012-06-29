
#include "Precomp.h"

#include "Error.h"
#include "Convert.h"


namespace error {

   std::exception Error (const std::string& type, const std::string& message, const std::string& function, const std::string& file, int line)
   {
      std::string error =
         type + " Error in function \"" + function + "\":\n\n"
         "Message:\n" + message;

#ifdef DEBUG
      if (!file.empty()) {
         error += "\n\nFile:\n" + file;
         if (line > 0) error += "\n\nLine:\n" + base::AsString(line);
      }
#endif

      return std::exception(error.c_str());
   }

   std::exception AlreadyExists  (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Already Exists", what, function, file, line); }

   std::exception Create         (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Create", what, function, file, line); }
   std::exception Read           (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Read", what, function, file, line); }
   std::exception Write          (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Write", what, function, file, line); }
   std::exception Execute        (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Execute", what, function, file, line); }
   std::exception Delete         (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Delete", what, function, file, line); }
   std::exception Copy           (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Copy", what, function, file, line); }
   std::exception Move           (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Move", what, function, file, line); }

   std::exception OutOfMemory    (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Out Of Memory", what, function, file, line); }

   std::exception InvalidParam   (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Invalid Param", what, function, file, line); }
   std::exception NullPointer    (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Null Pointer", what, function, file, line); }
   std::exception BadReference   (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Bad Reference", what, function, file, line); }
   std::exception Query          (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Query", what, function, file, line); }

   std::exception NotAvailable   (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Not Available", what, function, file, line); }
   std::exception NotFound       (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Not Found", what, function, file, line); }
   std::exception NoData         (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("No Data", what, function, file, line); }

   std::exception NotAllowed     (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Not Allowed", what, function, file, line); }
   std::exception NotImplemented (const std::string& what, const std::string& function, const std::string& file, int line) { return Error("Not Implemented", what, function, file, line); }

}

