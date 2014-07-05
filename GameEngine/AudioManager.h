
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

      AudioManager& MusicVolume (int percent);
      AudioManager& MusicVolume (const std::string& id, int percent);
      AudioManager& MusicSpeed (int percent);
      AudioManager& MusicSpeed (const std::string& id, int percent);
      AudioManager& MusicPan (int percent);
      AudioManager& MusicPan (const std::string& id, int percent);
      AudioManager& MusicPosition (const std::string& id, int position);

      AudioManager& PlaySound (const std::string& id, bool looped = false);
      AudioManager& StopSound ();
      AudioManager& StopSound (const std::string& id);
      AudioManager& PauseSound (bool pause = true);
      AudioManager& PauseSound (const std::string& id, bool pause = true);

      AudioManager& SoundVolume (int percent);
      AudioManager& SoundVolume (const std::string& id, int percent);
      AudioManager& SoundSpeed (int percent);
      AudioManager& SoundSpeed (const std::string& id, int percent);
      AudioManager& SoundPan (int percent);
      AudioManager& SoundPan (const std::string& id, int percent);

      AudioManager& ResumeAll ()                        { return PauseAll(false); }
      AudioManager& ResumeMusic ()                      { return PauseMusic(false); }
      AudioManager& ResumeMusic (const std::string& id) { return PauseMusic(id, false); }
      AudioManager& ResumeSound ()                      { return PauseSound(false); }
      AudioManager& ResumeSound (const std::string& id) { return PauseSound(id, false); }

      irrklang::ISoundEngine* Device () const { return device; }

      int MasterVolume () const;
      int DefaultVolume (const std::string& id) const;

      bool IsPlaying (const std::string& id) const;

      bool IsMusicPaused (const std::string& id) const;
      bool IsMusicLooped (const std::string& id) const;
      bool IsMusicFinished (const std::string& id) const;

      int MusicVolume (const std::string& id) const;
      int MusicSpeed (const std::string& id) const;
      int MusicPan (const std::string& id) const;
      int MusicPosition (const std::string& id) const;
      int MusicLength (const std::string& id) const;

      bool IsSoundPaused (const std::string& id) const;
      bool IsSoundLooped (const std::string& id) const;
      bool IsSoundFinished (const std::string& id) const;

      int SoundVolume (const std::string& id) const;
      int SoundSpeed (const std::string& id) const;
      int SoundPan (const std::string& id) const;
      int SoundPosition (const std::string& id) const;
      int SoundLength (const std::string& id) const;

      const std::string FileName (const std::string& id) const;
   };

}

