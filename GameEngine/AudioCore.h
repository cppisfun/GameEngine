
#pragma once

#include "DLL_DEF.h"

namespace irrklang {
   class ISoundEngine;
   class ISoundSource;
   class ISound;
}


class GEDLL AudioCore
{
   irrklang::ISoundEngine* device;

   std::map<std::string, irrklang::ISoundSource*> audioPool;

   void Init ();

public:
   AudioCore ();
   virtual ~AudioCore ();

   AudioCore& Add (const std::string& id, const std::string& audioFile);
   AudioCore& Add (const std::string& id, const std::vector<char>& resource);
   AudioCore& Remove (const std::string& id);

   AudioCore& Play (const std::string& id, bool looped = false);

   AudioCore& StopAll ();
   AudioCore& PauseAll (bool pause = true);
   AudioCore& ResumeAll ();

   irrklang::ISoundEngine* Device () const { return device; }
};

