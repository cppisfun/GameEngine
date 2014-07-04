
#include "Precomp.h"

#include "XML.h"

#include "../Base/Error.h"


namespace xml {

   Node& Node::RemoveChild (const std::string& name)
   {
      if (name.empty()) throw error::InvalidParam("No child name specified!", ERROR_LOCATION);

      auto child = std::find_if(children.begin(), children.end(), [&name] (const Node& child) {
         return child.Name() == name;
      });

      if (child != children.end()) children.erase(child);
      return *this;
   }

   Node& Node::RemoveChild (size_t pos)
   {
      if (pos >= children.size()) throw error::InvalidParam("Invalid child position!", ERROR_LOCATION);

      children.erase(children.begin() + pos);
      return *this;
   }

   Node& Node::RemoveAttribute (const std::string& name)
   {
      if (name.empty()) throw error::InvalidParam("No attribute name specified!", ERROR_LOCATION);

      auto attribute = attributes.find(name);
      if (attribute != attributes.end()) attributes.erase(attribute);

      return *this;
   }

   bool Node::HasChild (const std::string& name) const
   {
      if (name.empty()) throw error::InvalidParam("No child name specified!", ERROR_LOCATION);

      auto child = std::find_if(children.begin(), children.end(), [&name] (const Node& child) {
         return child.Name() == name;
      });

      return child != children.end();
   }

   bool Node::HasAttribute (const std::string& name) const
   {
      if (name.empty()) throw error::InvalidParam("No attribute name specified!", ERROR_LOCATION);
      return attributes.find(name) != attributes.end();
   }

   Node& Node::Child (const std::string& name)
   {
      if (name.empty()) throw error::InvalidParam("No child name specified!", ERROR_LOCATION);

      auto child = std::find_if(children.begin(), children.end(), [&name] (const Node& child) {
         return child.Name() == name;
      });

      if (child == children.end()) throw error::NotFound("Child node with name \"" + name + "\" does not exist!", ERROR_LOCATION);
      return *child;
   }

   Node& Node::Child (size_t pos)
   {
      if (pos >= children.size()) throw error::InvalidParam("Invalid child position!", ERROR_LOCATION);
      return children[pos];
   }

   std::string Node::AttributeValue (const std::string& name) const
   {
      if (name.empty()) throw error::InvalidParam("No attribute name specified!", ERROR_LOCATION);

      auto attribute = attributes.find(name);
      if (attribute != attributes.end()) return attribute->second;

      return "";
   }

}

