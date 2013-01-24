
#include "Precomp.h"

#include "Core.h"

#include "../Base/Error.h"


namespace ge {

   Core::Core ()
   : hasFocus(true), eventController(nullptr), graphics(nullptr),
     input(nullptr), audio(nullptr), resources(nullptr)
   {
      window.reset(new sf::RenderWindow);
      if (window == nullptr) throw error::Create("Failed to create application window!", __FUNCTION__);

      window->create(sf::VideoMode(800, 600), "GameEngine 0.0.5");
      window->clear(sf::Color::Blue);
      window->display();

      eventController.reset(new EventController);
      if (eventController == nullptr) throw error::Create("Failed to create event controller!", __FUNCTION__);

      eventController->WindowCallback(std::bind(&Core::OnEvent, this, std::placeholders::_1));
   }

}

