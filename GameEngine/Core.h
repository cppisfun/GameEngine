
#pragma once

#include <irrlicht.h>

#include "GraphicsCore.h"
#include "InputCore.h"
#include "AudioCore.h"
#include "ResourcesCore.h"

#include "DLL_DEF.h"

class EventController;


class GEDLL Core
{
public:
   enum What {
      NoInterface        = 0,
      GraphicsInterface  = 1,
      InputInterface     = 2,
      AudioInterface     = 4,
      ResourcesInterface = 8,
      AllInterfaces      = 15
   };

private:
   static Core* instance;

   std::unique_ptr<irr::IrrlichtDevice> device;
   std::unique_ptr<EventController> eventController;

   std::unique_ptr<GraphicsCore>  graphics;
   std::unique_ptr<InputCore>     input;
   std::unique_ptr<AudioCore>     audio;
   std::unique_ptr<ResourcesCore> resources;

   Core () : device(nullptr), eventController(nullptr), graphics(nullptr), input(nullptr), audio(nullptr), resources(nullptr)
   {
      Init();
   }

   Core (const Core&);
   Core& operator= (const Core&);

   void Init ();

public:
   ~Core ()
   {
      ShutDown(AllInterfaces);
   }

   static Core* Instance ()
   {
      if (!instance) instance = new Core;
      return instance;
   }

   Core& Reset (const What& what)
   {
      if (what & GraphicsInterface)  graphics.reset(new GraphicsCore(device.get()));
      if (what & InputInterface)     input.reset(new InputCore(eventController.get()));
      if (what & AudioInterface)     audio.reset(new AudioCore);
      if (what & ResourcesInterface) resources.reset(new ResourcesCore);

      return *this;
   }

   Core& ShutDown (const What& what)
   {
      if (what & ResourcesInterface) resources.reset();
      if (what & AudioInterface)     audio.reset();
      if (what & InputInterface)     input.reset();
      if (what & GraphicsInterface)  graphics.reset();

      return *this;
   }

   Core& WindowTitle (const std::string& title);

   GraphicsCore* Graphics ()      { if (graphics == nullptr) Reset(GraphicsInterface); return graphics.get(); }
   InputCore* Input ()            { if (input == nullptr) Reset(InputInterface); return input.get(); }
   AudioCore* Audio ()            { if (audio == nullptr) Reset(AudioInterface); return audio.get(); }
   ResourcesCore* Resources ()    { if (resources == nullptr) Reset(ResourcesInterface); return resources.get(); }
   irr::IrrlichtDevice* Device () { return device.get(); }

   bool IsRunning () const { return device->run(); }
};



Core* Core::instance = nullptr;

