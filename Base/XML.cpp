
#include "Precomp.h"

#include <tinyxml2.h>

#include "XML.h"

#include "../Base/File.h"
#include "../Base/Error.h"

using namespace tinyxml2;


namespace xml {

   XMLDocument& XMLDocument::Parse (const std::string& xml)
   {
      if (xml.empty()) throw error::InvalidParam("No XML string specified!", __FUNCTION__);

      CheckResult(doc.Parse(xml.c_str(), xml.size()));
      return *this;
   }

   XMLDocument& XMLDocument::Load (const std::string& filePath)
   {
      if (filePath.empty()) throw error::InvalidParam("No XML file path specified!", __FUNCTION__);

      CheckResult(doc.LoadFile(filePath.c_str()));
      return *this;
   }

   XMLDocument& XMLDocument::Save (const std::string& filePath)
   {
      if (filePath.empty()) throw error::InvalidParam("No XML file path specified!", __FUNCTION__);

      CheckResult(doc.SaveFile(filePath.c_str()));
      return *this;
   }

   void XMLDocument::CheckResult (const tinyxml2::XMLError& result)
   {
      if (result == tinyxml2::XML_SUCCESS || result == tinyxml2::XML_NO_ERROR) return;

      std::string err = "An error was thrown by TinyXML-2!\n\nError type:\n";

      switch (result) {
         case tinyxml2::XML_CAN_NOT_CONVERT_TEXT:           err += "Cannot convert text";       break;
         case tinyxml2::XML_ERROR_ELEMENT_MISMATCH:         err += "Element mismatch";          break;
         case tinyxml2::XML_ERROR_EMPTY_DOCUMENT:           err += "Empty document";            break;
         case tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED: err += "File could not be opened";  break;
         case tinyxml2::XML_ERROR_FILE_NOT_FOUND:           err += "File not found";            break;
         case tinyxml2::XML_ERROR_FILE_READ_ERROR:          err += "File read error";           break;
         case tinyxml2::XML_ERROR_IDENTIFYING_TAG:          err += "Error identifying tag";     break;
         case tinyxml2::XML_ERROR_MISMATCHED_ELEMENT:       err += "Mismatched element";        break;
         case tinyxml2::XML_ERROR_PARSING:                  err += "Parsing error";             break;
         case tinyxml2::XML_ERROR_PARSING_ATTRIBUTE:        err += "Error parsing attribute";   break;
         case tinyxml2::XML_ERROR_PARSING_CDATA:            err += "Error parsing CDATA";       break;
         case tinyxml2::XML_ERROR_PARSING_COMMENT:          err += "Error parsing comment";     break;
         case tinyxml2::XML_ERROR_PARSING_DECLARATION:      err += "Error parsing declaration"; break;
         case tinyxml2::XML_ERROR_PARSING_ELEMENT:          err += "Error parsing element";     break;
         case tinyxml2::XML_ERROR_PARSING_TEXT:             err += "Error parsing text";        break;
         case tinyxml2::XML_ERROR_PARSING_UNKNOWN:          err += "Error parsing unknown";     break;
         case tinyxml2::XML_NO_TEXT_NODE:                   err += "No text node";              break;
         case tinyxml2::XML_WRONG_ATTRIBUTE_TYPE:           err += "Wrong attribute type";      break;
         default:                                           err += "Unknown";
      }

      err += "\n\nFirst error string:\n";
      err += doc.GetErrorStr1();
      err += "\n\nSecond error string:\n";
      err += doc.GetErrorStr2();

      throw error::Error("XML Error", err, __FUNCTION__, __FILE__, __LINE__);
   }

   XMLDocument& XMLDocument::Clear ()       { doc.Clear(); return *this; }
   XMLDocument& XMLDocument::BOM (bool set) { doc.SetBOM(set); return *this; }

   bool XMLDocument::HasBOM () const { return doc.HasBOM(); }
   bool XMLDocument::Valid () const  { return !doc.Error(); }

}