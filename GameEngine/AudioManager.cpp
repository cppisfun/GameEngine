
#include "Precomp.h"

#include <irrKlang.h>

#include "AudioManager.h"

#include "../Base/Error.h"


namespace ge {

   AudioManager::AudioManager () : device(nullptr)
   {
      Init();
   }

   AudioManager::~AudioManager ()
   {
      if (device != nullptr) {
         device->stopAllSounds();

         std::for_each(music.begin(), music.end(), [] (const std::pair<std::string, irrklang::ISound*> mus) {
            mus.second->drop();
         });

         for (auto it = sounds.begin(); it != sounds.end(); ++it) {
            std::for_each(it->second.begin(), it->second.end(), [] (irrklang::ISound* snd) {
               snd->drop();
            });
         }

         std::for_each(audioPool.begin(), audioPool.end(), [] (const std::pair<std::string, irrklang::ISoundSource*> aud) {
            aud.second->drop();
         });
      }
   }

   void AudioManager::Init ()
   {
      device = irrklang::createIrrKlangDevice();
      if (device == nullptr) throw error::Create("Failed to create irrKlang audio device!", ERROR_LOCATION);
   }

   AudioManager& AudioManager::Add (const std::string& id, const std::string& audioFile)
   {
      if (id.empty())                                 throw error::InvalidParam("No id specified!", ERROR_LOCATION);
      else if (audioFile.empty())                     throw error::InvalidParam("No audio file specified!", ERROR_LOCATION);
      else if (audioPool.find(id) != audioPool.end()) throw error::AlreadyExists("Audio resource with specified id already exists!", ERROR_LOCATION);

      auto aud = device->addSoundSourceFromFile(audioFile.c_str(), irrklang::ESM_AUTO_DETECT, true);
      if (aud == nullptr) throw error::Read("Failed to read audio file!", ERROR_LOCATION);

      audioPool[id] = aud;
      return *this;
   }

   AudioManager& AudioManager::Add (const std::string& id, const Binary& resource)
   {
      if (id.empty())                                 throw error::InvalidParam("No id specified!", ERROR_LOCATION);
      else if (resource.empty())                      throw error::InvalidParam("No resource data specified!", ERROR_LOCATION);
      else if (audioPool.find(id) != audioPool.end()) throw error::AlreadyExists("Audio resource with specified id already exists!", ERROR_LOCATION);

      auto aud = device->addSoundSourceFromMemory((void*)&resource[0], resource.size(), id.c_str());
      if (aud == nullptr) throw error::Query("Failed to query resource data!", ERROR_LOCATION);

      audioPool[id] = aud;
      return *this;
   }

   AudioManager& AudioManager::Remove (const std::string& id)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto aud = audioPool.find(id);
      if (aud == audioPool.end()) return *this;

      device->removeSoundSource(aud->second);
      audioPool.erase(aud);

      return *this;
   }

   AudioManager& AudioManager::RemoveAll ()
   {
      device->removeAllSoundSources();
      audioPool.clear();

      return *this;
   }

   AudioManager& AudioManager::StopAll ()
   {
      device->stopAllSounds();
      return *this;
   }

   AudioManager& AudioManager::PauseAll (bool pause)
   {
      device->setAllSoundsPaused(pause);
      return *this;
   }

   AudioManager& AudioManager::MasterVolume (int percent)
   {
      float vol = boost::numeric_cast<float>(percent) / 100.0f;

      if (vol < 0.0f) vol      = 0.0f;
      else if (vol > 1.0f) vol = 1.0f;

      device->setSoundVolume(vol);
      return *this;
   }

   AudioManager& AudioManager::DefaultVolume (const std::string& id, int percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto aud = audioPool.find(id);
      if (aud == audioPool.end()) return *this;

      float vol = boost::numeric_cast<float>(percent) / 100.0f;

      if (vol < 0.0f)      vol = 0.0f;
      else if (vol > 1.0f) vol = 1.0f;

      aud->second->setDefaultVolume(vol);
      return *this;
   }

   AudioManager& AudioManager::PlayMusic (const std::string& id, bool looped)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);
      else if (music.find(id) != music.end()) return *this;

      auto aud = audioPool.find(id);
      if (aud == audioPool.end()) return *this;

      auto mus = device->play2D(aud->second, looped, false, true, false);
      if (mus == nullptr) return *this;

      music[id] = mus;
      return *this;
   }

   AudioManager& AudioManager::StopMusic ()
   {
      std::for_each(music.begin(), music.end(), [] (const std::pair<std::string, irrklang::ISound*> mus) {
         mus.second->stop();
      });

      return *this;
   }

   AudioManager& AudioManager::StopMusic (const std::string& id)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return *this;

      mus->second->stop();
      return *this;
   }

   AudioManager& AudioManager::PauseMusic (bool pause)
   {
      std::for_each(music.begin(), music.end(), [&pause] (const std::pair<std::string, irrklang::ISound*> mus) {
         mus.second->setIsPaused(pause);
      });

      return *this;
   }

   AudioManager& AudioManager::PauseMusic (const std::string& id, bool pause)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return *this;

      mus->second->setIsPaused(pause);
      return *this;
   }

   AudioManager& AudioManager::MusicVolume (int percent)
   {
      float vol = boost::numeric_cast<float>(percent) / 100.0f;

      if (vol < 0.0f)      vol = 0.0f;
      else if (vol > 1.0f) vol = 1.0f;

      std::for_each(music.begin(), music.end(), [&vol] (const std::pair<std::string, irrklang::ISound*>& mus) {
         mus.second->setVolume(vol);
      });

      return *this;
   }

   AudioManager& AudioManager::MusicVolume (const std::string& id, int percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return *this;

      float vol = boost::numeric_cast<float>(percent) / 100.0f;

      if (vol < 0.0f) vol      = 0.0f;
      else if (vol > 1.0f) vol = 1.0f;

      mus->second->setVolume(vol);
      return *this;
   }

   AudioManager& AudioManager::MusicSpeed (int percent)
   {
      float spd = boost::numeric_cast<float>(percent) / 100.0f;

      if (spd < 0.01f)     spd = 0.01f;
      else if (spd > 4.0f) spd = 4.0f;

      std::for_each(music.begin(), music.end(), [&spd] (const std::pair<std::string, irrklang::ISound*>& mus) {
         mus.second->setPlaybackSpeed(spd);
      });

      return *this;
   }

   AudioManager& AudioManager::MusicSpeed (const std::string& id, int percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return *this;

      float spd = boost::numeric_cast<float>(percent) / 100.0f;

      if (spd < 0.01f)     spd = 0.01f;
      else if (spd > 4.0f) spd = 4.0f;

      mus->second->setPlaybackSpeed(spd);
      return *this;
   }

   AudioManager& AudioManager::MusicPan (int percent)
   {
      float pan = boost::numeric_cast<float>(percent) / 100.0f;

      if (pan < -1.0f)     pan = -1.0f;
      else if (pan > 1.0f) pan = 1.0f;

      std::for_each(music.begin(), music.end(), [&pan] (const std::pair<std::string, irrklang::ISound*>& mus) {
         mus.second->setPan(pan);
      });

      return *this;
   }

   AudioManager& AudioManager::MusicPan (const std::string& id, int percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return *this;

      float pan = boost::numeric_cast<float>(percent) / 100.0f;

      if (pan < -1.0f)     pan = -1.0f;
      else if (pan > 1.0f) pan = 1.0f;

      mus->second->setPan(pan);
      return *this;
   }

   AudioManager& AudioManager::MusicPosition (const std::string& id, int position)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return *this;

      size_t pos;

      if (position < 0)                                             pos = 0;
      else if ((size_t)position > mus->second->getPlayLength() - 1) pos = mus->second->getPlayLength() - 1;
      else                                                          pos = position;

      mus->second->setPlayPosition(pos);
      return *this;
   }

   AudioManager& AudioManager::PlaySound (const std::string& id, bool looped)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto aud = audioPool.find(id);
      if (aud == audioPool.end()) return *this;

      auto snd = device->play2D(aud->second, looped, false, true, false);
      if (snd == nullptr) return *this;

      sounds[id].push_back(snd);
      return *this;
   }

   AudioManager& AudioManager::StopSound ()
   {
      for (auto it = sounds.begin(); it != sounds.end(); ++it) {
         std::for_each(it->second.begin(), it->second.end(), [] (irrklang::ISound* snd) {
            snd->stop();
            snd->drop();
         });
      }

      sounds.clear();
      return *this;
   }

   AudioManager& AudioManager::StopSound (const std::string& id)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end()) return *this;

      std::for_each(snd->second.begin(), snd->second.end(), [] (irrklang::ISound* snd) {
         snd->stop();
         snd->drop();
      });

      sounds.erase(snd);
      return *this;
   }

   AudioManager& AudioManager::PauseSound (bool pause)
   {
      for (auto it = sounds.begin(); it != sounds.end(); ++it) {
         std::for_each(it->second.begin(), it->second.end(), [&pause] (irrklang::ISound* snd) {
            snd->setIsPaused(pause);
         });
      }

      return *this;
   }

   AudioManager& AudioManager::PauseSound (const std::string& id, bool pause)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end()) return *this;

      std::for_each(snd->second.begin(), snd->second.end(), [&pause] (irrklang::ISound* snd) {
         snd->setIsPaused(pause);
      });

      return *this;
   }

   AudioManager& AudioManager::SoundVolume (int percent)
   {
      float vol = boost::numeric_cast<float>(percent) / 100.0f;

      if (vol < 0.0f)      vol = 0.0f;
      else if (vol > 1.0f) vol = 1.0f;

      for (auto it = sounds.begin(); it != sounds.end(); ++it) {
         std::for_each(it->second.begin(), it->second.end(), [&vol] (irrklang::ISound* snd) {
            snd->setVolume(vol);
         });
      }

      return *this;
   }

   AudioManager& AudioManager::SoundVolume (const std::string& id, int percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return *this;

      float vol = boost::numeric_cast<float>(percent) / 100.0f;

      if (vol < 0.0f)      vol = 0.0f;
      else if (vol > 1.0f) vol = 1.0f;

      std::for_each(snd->second.begin(), snd->second.end(), [&vol] (irrklang::ISound* sound) {
         sound->setVolume(vol);
      });

      return *this;
   }

   AudioManager& AudioManager::SoundSpeed (int percent)
   {
      float spd = boost::numeric_cast<float>(percent) / 100.0f;

      if (spd < 0.01f)     spd = 0.01f;
      else if (spd > 4.0f) spd = 4.0f;

      for (auto it = sounds.begin(); it != sounds.end(); ++it) {
         std::for_each(it->second.begin(), it->second.end(), [&spd] (irrklang::ISound* snd) {
            snd->setPlaybackSpeed(spd);
         });
      }

      return *this;
   }

   AudioManager& AudioManager::SoundSpeed (const std::string& id, int percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return *this;

      float spd = boost::numeric_cast<float>(percent) / 100.0f;

      if (spd < 0.01f)     spd = 0.01f;
      else if (spd > 4.0f) spd = 4.0f;

      std::for_each(snd->second.begin(), snd->second.end(), [&spd] (irrklang::ISound* sound) {
         sound->setPlaybackSpeed(spd);
      });

      return *this;
   }

   AudioManager& AudioManager::SoundPan (int percent)
   {
      float pan = boost::numeric_cast<float>(percent) / 100.0f;

      if (pan < -1.0f)     pan = -1.0f;
      else if (pan > 1.0f) pan = 1.0f;

      for (auto it = sounds.begin(); it != sounds.end(); ++it) {
         std::for_each(it->second.begin(), it->second.end(), [&pan] (irrklang::ISound* snd) {
            snd->setPan(pan);
         });
      }

      return *this;
   }

   AudioManager& AudioManager::SoundPan (const std::string& id, int percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return *this;

      float pan = boost::numeric_cast<float>(percent) / 100.0f;

      if (pan < -1.0f)     pan = -1.0f;
      else if (pan > 1.0f) pan = 1.0f;

      std::for_each(snd->second.begin(), snd->second.end(), [&pan] (irrklang::ISound* sound) {
         sound->setPan(pan);
      });

      return *this;
   }

   int AudioManager::MasterVolume () const
   {
      int vol = boost::numeric_cast<int>(device->getSoundVolume() * 100.0f);

      if (vol < 0)        vol = 0;
      else if (vol > 100) vol = 100;

      return vol;
   }

   int AudioManager::DefaultVolume (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto aud = audioPool.find(id);
      if (aud == audioPool.end()) return 0;

      int vol = boost::numeric_cast<int>(aud->second->getDefaultVolume() * 100.0f);

      if (vol < 0)        vol = 0;
      else if (vol > 100) vol = 100;

      return vol;
   }

   bool AudioManager::IsPlaying (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto aud = audioPool.find(id);
      if (aud == audioPool.end()) return false;

      return device->isCurrentlyPlaying(aud->second);
   }

   bool AudioManager::IsMusicPaused (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return false;

      return mus->second->getIsPaused();
   }

   bool AudioManager::IsMusicLooped (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return false;

      return mus->second->isLooped();
   }

   bool AudioManager::IsMusicFinished (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return true;

      return mus->second->isFinished();
   }

   int AudioManager::MusicVolume (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return 0;

      int vol = boost::numeric_cast<int>(mus->second->getVolume() * 100.0f);

      if (vol < 0)        vol = 0;
      else if (vol > 100) vol = 100;

      return vol;
   }

   int AudioManager::MusicSpeed (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return 0;

      return boost::numeric_cast<int>(mus->second->getPlaybackSpeed() * 100.0f);
   }

   int AudioManager::MusicPan (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return 0;

      int pan = boost::numeric_cast<int>(mus->second->getPan() * 100.0f);

      if (pan < -100)     pan = -100;
      else if (pan > 100) pan = 100;

      return pan;
   }

   int AudioManager::MusicPosition (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return -1;

      return mus->second->getPlayPosition();
   }

   int AudioManager::MusicLength (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return -1;

      return mus->second->getPlayLength();
   }

   bool AudioManager::IsSoundPaused (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return false;

      return snd->second.back()->getIsPaused();
   }

   bool AudioManager::IsSoundLooped (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return false;

      return snd->second.back()->isLooped();
   }

   bool AudioManager::IsSoundFinished (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return true;

      return snd->second.back()->isFinished();
   }

   int AudioManager::SoundVolume (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return 0;

      int vol = boost::numeric_cast<int>(snd->second.back()->getVolume() * 100.0f);

      if (vol < 0)        vol = 0;
      else if (vol > 100) vol = 100;

      return vol;
   }

   int AudioManager::SoundSpeed (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return 0;

      return boost::numeric_cast<int>(snd->second.back()->getPlaybackSpeed() * 100.0f);
   }

   int AudioManager::SoundPan (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return 0;

      int pan = boost::numeric_cast<int>(snd->second.back()->getPan() * 100.0f);

      if (pan < -100)     pan = -100;
      else if (pan > 100) pan = 100;

      return pan;
   }

   int AudioManager::SoundPosition (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return -1;

      return snd->second.back()->getPlayPosition();
   }

   int AudioManager::SoundLength (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return -1;

      return snd->second.back()->getPlayLength();
   }

   const std::string AudioManager::FileName (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto aud = audioPool.find(id);
      if (aud == audioPool.end()) return "";

      return std::string(aud->second->getName());
   }

}

