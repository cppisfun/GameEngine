
#include "Precomp.h"

#include "Core.h"

#include "../Base/Error.h"


namespace ge {

   Core::Core ()
   : eventController(nullptr), graphics(nullptr), input(nullptr),
     audio(nullptr), resources(nullptr)
   {
      eventController.reset(new EventController);
      if (eventController == nullptr) throw error::Create("Failed to create event controller!", __FUNCTION__);

      window.create(sf::VideoMode(800, 600), "GameEngine 0.4");
      window.clear(sf::Color::Blue);
      window.display();
   }

}

