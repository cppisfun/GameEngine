
#pragma once

#include "DLL_DEF.h"


namespace error {

   BASEDLL std::exception Error (const std::string& type, const std::string& message, const std::string& function, const std::string& file, int line);

   BASEDLL std::exception AlreadyExists (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   BASEDLL std::exception Create (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception Read (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception Write (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception Execute (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception Delete (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception Copy (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception Move (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   BASEDLL std::exception OutOfMemory (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   BASEDLL std::exception InvalidParam (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception NullPointer (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception BadReference (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception BadFormat (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception Query (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   BASEDLL std::exception NotAvailable (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception NotFound (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception NoData (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);

   BASEDLL std::exception NotAllowed (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);
   BASEDLL std::exception NotImplemented (const std::string& what, const std::string& function, const std::string& file = "", int line = 0);



   #define ERROR_LOCATION __FUNCTION__, __FILE__, __LINE__

}

