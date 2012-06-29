
#pragma once

#include "WindowsCore.h"
#include "GraphicsCore.h"
#include "InputCore.h"
#include "AudioCore.h"
#include "ResourcesCore.h"

#include "../Base/Error.h"


class Core
{
public:
   enum What {
      NoInterface        = 0,
      WindowsInterface   = 1,
      GraphicsInterface  = 2,
      InputInterface     = 4,
      AudioInterface     = 8,
      ResourcesInterface = 16,
      AllInterfaces      = 31
   };

private:
   static Core* instance;

   HINSTANCE instanceHandle;

   Core (HINSTANCE inst)
   : instanceHandle(inst), windows(nullptr), graphics(nullptr), input(nullptr), audio(nullptr), resources(nullptr)
   {
      Reset(WindowsInterface);
   }

   Core (const Core&);
   Core& operator= (const Core&);

   std::unique_ptr<WindowsCore> windows;
   std::unique_ptr<GraphicsCore> graphics;
   std::unique_ptr<InputCore> input;
   std::unique_ptr<AudioCore> audio;
   std::unique_ptr<ResourcesCore> resources;

public:
   ~Core ()
   {
      ShutDown(AllInterfaces);
   }

   static Core* Instance (HINSTANCE inst = nullptr)
   {
      if (!inst) throw error::InvalidParam("Valid instance handle needed when calling initially!", __FUNCTION__);
      else if (!instance) instance = new Core(inst);

      return instance;
   }

   Core& Reset (const What& what)
   {
      if (what & WindowsInterface)   windows.reset(new WindowsCore(instanceHandle));
      if (what & GraphicsInterface)  graphics.reset(new GraphicsCore(instanceHandle, Windows()->WindowHandle()));
      if (what & InputInterface)     input.reset(new InputCore(instanceHandle, Windows()->WindowHandle()));
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
      if (what & WindowsInterface)   windows.reset();

      return *this;
   }

   HINSTANCE InstanceHandle () const { return instanceHandle; }

   WindowsCore* Windows ()     { if (windows == nullptr) Reset(WindowsInterface); return windows.get(); }
   GraphicsCore* Graphics ()   { if (graphics == nullptr) Reset(GraphicsInterface); return graphics.get(); }
   InputCore* Input ()         { if (input == nullptr) Reset(InputInterface); return input.get(); }
   AudioCore* Audio ()         { if (audio == nullptr) Reset(AudioInterface); return audio.get(); }
   ResourcesCore* Resources () { if (resources == nullptr) Reset(ResourcesInterface); return resources.get(); }
};



Core* Core::instance = nullptr;

