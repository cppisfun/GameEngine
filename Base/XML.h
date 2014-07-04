
#pragma once

#include "DLL_DEF.h"


namespace xml {

   class BASEDLL Node
   {
      Node*       parent;
      std::string name;
      std::string value;

      std::map<std::string, std::string> attributes;
      std::vector<Node>                  children;

   public:
      Node (const std::string& name, Node& parent) : name(name), parent(&parent) { }

      Node& Name (const std::string& val)                                  { name = val; return *this; }
      Node& Value (const std::string& val)                                 { value = val; return *this; }
      Node& AddChild (const Node& childNode)                               { children.push_back(childNode); return *this; }
      Node& AddAttribute (const std::string& name, const std::string& val) { attributes[name] = val; return *this; }
      Node& RemoveValue ()                                                 { value.clear(); return *this; }
      Node& RemoveChildren ()                                              { children.clear(); return *this; }
      Node& RemoveAttributes ()                                            { attributes.clear(); return *this; }

      Node& RemoveChild (const std::string& name);
      Node& RemoveChild (size_t pos);
      Node& RemoveAttribute (const std::string& name);

      Node& Parent () const                             { return *parent; }
      const std::string& Name () const                  { return name; }
      const std::string& Value () const                 { return value; }
      size_t ChildCount () const                        { return children.size(); }

      bool HasChild (const std::string& name) const;
      bool HasAttribute (const std::string& name) const;
      Node& Child (const std::string& name);
      Node& Child (size_t pos);
      std::string AttributeValue (const std::string& name) const;
   };

/*   class BASEDLL Document
   {

   public:
      Document (const std::string& )*/

      /* will be useful here:
      Name (2x)
      AddChild
      RemoveChildren
      RemoveChild (2x)
      ChildCount
      HasChild
      Child (2x)
      */

      /* will cause trouble here:
      Value (2x)
      AddAttribute
      RemoveValue
      RemoveAttributes
      RemoveAttribute
      Parent
      HasAttribute
      AttributeValue
      */
//   };

}

