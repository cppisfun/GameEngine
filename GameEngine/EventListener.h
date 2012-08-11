
#pragma once

namespace irr {
   struct SEvent;
}


class EventListener
{
   bool enabled;

   virtual void OnEvent (const irr::SEvent& event) = 0;

public:
   EventListener () : enabled(true) { }
   virtual ~EventListener ()        { }

   void Enable (bool enable) { enabled = enable; }
   void Disable ()           { enabled = false; }

   bool Enabled () const { return enabled; }
};

