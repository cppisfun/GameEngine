
#pragma once

#include "DLL_DEF.h"

namespace irrklang {
   class ISoundEngine;
   class ISoundSource;
   class ISound;
}


namespace ge {

   class GEDLL AudioManager
   {
      irrklang::ISoundEngine* device;

      std::map<std::string, irrklang::ISoundSource*>       audioPool;
      std::map<std::string, irrklang::ISound*>             music;
      std::map<std::string, std::deque<irrklang::ISound*>> sounds;

      void Init ();

   public:
      AudioManager ();
      virtual ~AudioManager ();

      AudioManager& Add (const std::string& id, const std::string& audioFile);
      AudioManager& Add (const std::string& id, const Binary& resource);
      AudioManager& Remove (const std::string& id);

      AudioManager& RemoveAll ();
      AudioManager& StopAll ();
      AudioManager& PauseAll (bool pause = true);

      AudioManager& MasterVolume (int percent);
      AudioManager& DefaultVolume (const std::string& id, int percent);

      AudioManager& PlayMusic (const std::string& id, bool looped = false);
      AudioManager& StopMusic ();
      AudioManager& StopMusic (const std::string& id);
      AudioManager& PauseMusic (bool pause = true);
      AudioManager& PauseMusic (const std::string& id, bool pause = true);

      AudioManager& MusicVolume (float percent);
      AudioManager& MusicVolume (const std::string& id, float percent);
      AudioManager& MusicSpeed (float percent);
      AudioManager& MusicSpeed (const std::string& id, float percent);
      AudioManager& MusicPan (float percent);
      AudioManager& MusicPan (const std::string& id, float percent);
      AudioManager& MusicPosition (const std::string& id, size_t position);

      AudioManager& PlaySound (const std::string& id, bool looped = false);
      AudioManager& StopSound ();
      AudioManager& StopSound (const std::string& id);
      AudioManager& PauseSound (bool pause = true);
      AudioManager& PauseSound (const std::string& id, bool pause = true);

      AudioManager& SoundVolume (float percent);
      AudioManager& SoundVolume (const std::string& id, float percent);
      AudioManager& SoundSpeed (float percent);
      AudioManager& SoundSpeed (const std::string& id, float percent);
      AudioManager& SoundPan (float percent);
      AudioManager& SoundPan (const std::string& id, float percent);

      AudioManager& ResumeAll ()                        { return PauseAll(false); }
      AudioManager& ResumeMusic ()                      { return PauseMusic(false); }
      AudioManager& ResumeMusic (const std::string& id) { return PauseMusic(id, false); }
      AudioManager& ResumeSound ()                      { return PauseSound(false); }
      AudioManager& ResumeSound (const std::string& id) { return PauseSound(id, false); }

      irrklang::ISoundEngine* Device () const { return device; }

      float MasterVolume () const;
      float DefaultVolume (const std::string& id) const;

      bool IsPlaying (const std::string& id) const;

      bool IsMusicPaused (const std::string& id) const;
      bool IsMusicLooped (const std::string& id) const;
      bool IsMusicFinished (const std::string& id) const;

      float MusicVolume (const std::string& id) const;
      float MusicSpeed (const std::string& id) const;
      float MusicPan (const std::string& id) const;
      size_t MusicPosition (const std::string& id) const;
      size_t MusicLength (const std::string& id) const;

      bool IsSoundPaused (const std::string& id) const;
      bool IsSoundLooped (const std::string& id) const;
      bool IsSoundFinished (const std::string& id) const;

      float SoundVolume (const std::string& id) const;
      float SoundSpeed (const std::string& id) const;
      float SoundPan (const std::string& id) const;
      size_t SoundPosition (const std::string& id) const;
      size_t SoundLength (const std::string& id) const;

      const std::string FileName (const std::string& id) const;
   };

}

