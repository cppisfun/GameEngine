
#pragma once

namespace ticpp {
   class Document;
   class Node;
   class Element;
}


namespace xml {

   class Node
   {
      ticpp::Node*    parent;
      ticpp::Node*    node;
      ticpp::Element* element;

   public:
      Node (const std::string& nodeName);
      Node (const std::string& nodeName, const Node& parent);

      Node& AddChild (const Node& child);
      Node& AddChild (const std::string& childName);
      Node& RemoveChild (const Node& child);
      Node& RemoveChild (const std::string& childName);
      Node& Parent (const Node& parent);
      Node& Clear ();

      bool IsEditable () const { return element != nullptr; }
      bool HasChildren () const;

      Node Clone ();
      std::vector<Node> Children () const;
   };

   class Document
   {
      ticpp::Document doc;
      Node            node;

   public:
      Document () : node("") { }

      Document& Parse (const std::string& xml);
      Document& Load (const std::string& filePath);
      Document& Save (const std::string& filePath);
   };

}

