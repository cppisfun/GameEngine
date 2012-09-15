
#pragma once

#include "DLL_DEF.h"

namespace irrklang {
   class ISoundEngine;
   class ISoundSource;
   class ISound;
}


namespace ge {

   class GEDLL AudioCore
   {
      irrklang::ISoundEngine* device;

      std::map<std::string, irrklang::ISoundSource*>       audioPool;
      std::map<std::string, irrklang::ISound*>             music;
      std::map<std::string, std::deque<irrklang::ISound*>> sounds;

      void Init ();

   public:
      AudioCore ();
      virtual ~AudioCore ();

      AudioCore& Add (const std::string& id, const std::string& audioFile);
      AudioCore& Add (const std::string& id, const std::vector<char>& resource);
      AudioCore& Remove (const std::string& id);
      AudioCore& RemoveAll ();

      AudioCore& StopAll ();
      AudioCore& PauseAll (bool pause = true);

      AudioCore& MasterVolume (int percent);
      AudioCore& DefaultVolume (const std::string& id, int percent);

      AudioCore& PlayMusic (const std::string& id, bool looped = false);
      AudioCore& StopMusic ();
      AudioCore& StopMusic (const std::string& id);
      AudioCore& PauseMusic (bool pause = true);
      AudioCore& PauseMusic (const std::string& id, bool pause = true);
      AudioCore& MusicVolume (int percent);
      AudioCore& MusicVolume (const std::string& id, int percent);
      AudioCore& MusicSpeed (int percent);
      AudioCore& MusicSpeed (const std::string& id, int percent);
      AudioCore& MusicPan (int percent);
      AudioCore& MusicPan (const std::string& id, int percent);
      AudioCore& MusicPosition (const std::string& id, int position);

      AudioCore& PlaySound (const std::string& id, bool looped = false);
      AudioCore& StopSound ();
      AudioCore& StopSound (const std::string& id);
      AudioCore& PauseSound (bool pause = true);
      AudioCore& PauseSound (const std::string& id, bool pause = true);
      AudioCore& SoundVolume (int percent);
      AudioCore& SoundVolume (const std::string& id, int percent);
      AudioCore& SoundSpeed (int percent);
      AudioCore& SoundSpeed (const std::string& id, int percent);
      AudioCore& SoundPan (int percent);
      AudioCore& SoundPan (const std::string& id, int percent);

      AudioCore& ResumeAll ()                        { return PauseAll(false); }
      AudioCore& ResumeMusic ()                      { return PauseMusic(false); }
      AudioCore& ResumeMusic (const std::string& id) { return PauseMusic(id, false); }
      AudioCore& ResumeSound ()                      { return PauseSound(false); }
      AudioCore& ResumeSound (const std::string& id) { return PauseSound(id, false); }

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

