
#pragma once

namespace tinyxml2 {
   class XMLDocument;
   enum XMLError;
}


namespace xml {

   class XMLDocument
   {
      tinyxml2::XMLDocument doc;

      void CheckResult (const tinyxml2::XMLError& result);

   public:
      XMLDocument () { }

      XMLDocument& Parse (const std::string& xml);
      XMLDocument& Load (const std::string& filePath);
      XMLDocument& Save (const std::string& filePath);
      XMLDocument& Clear ();

      XMLDocument& BOM (bool set = true);

      bool HasBOM () const;
      bool Valid () const;
   };

}

