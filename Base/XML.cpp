
#include "Precomp.h"

#include <ticpp.h>

#include "XML.h"

#include "../Base/File.h"
#include "../Base/Error.h"


namespace xml {

   Document& Document::Parse (const std::string& xml)     { doc.Parse(xml); return *this; }
   Document& Document::Load (const std::string& filePath) { doc.LoadFile(filePath); return *this; }
   Document& Document::Save (const std::string& filePath) { doc.SaveFile(filePath); return *this; }

}


/*
namespace xml {

   Node::Node (const std::string& name, Node& parent) : parent(nullptr), node(nullptr)
   {
      if (parent.node == nullptr) throw error::NullPointer("Invalid tinyxml2::XMLElement pointer!", ERROR_LOCATION);

      this->parent = parent.node;
      node         = parent.node->GetDocument()->NewElement(name.c_str());
   }

   Node& Node::Name (const std::string& val) { node->SetName(val.c_str()); return *this; }

   std::string Node::Name () const { return node->Name(); }





   void Document::CheckResult (const tinyxml2::XMLError& result)
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

      throw error::BadFormat(err, ERROR_LOCATION);
   }

   Document& Document::Clear ()       { doc.Clear(); return *this; }
   Document& Document::BOM (bool use) { doc.SetBOM(use); return *this; }

   bool Document::HasBOM () const { return doc.HasBOM(); }
   bool Document::Valid () const  { return !doc.Error(); }

   Node Document::Child (const std::string& name) const
   {
      if (doc.NoChildren()) throw error::InvalidParam("XML child node position is out of range!", ERROR_LOCATION);
      auto node = doc.

   }

}

*/