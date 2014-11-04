
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

         for (const auto& mus : music) mus.second->drop();

         for (const auto& snds : sounds) {
            for (const auto& snd : snds.second) snd->drop();
         }

         for (const auto& aud : audioPool) aud.second->drop();
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
      for (const auto& mus : music) mus.second->stop();
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
      for (const auto& mus : music) mus.second->setIsPaused(pause);
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

   AudioManager& AudioManager::MusicVolume (float percent)
   {
      percent /= 100.0f;

      if (percent < 0.0f)      percent = 0.0f;
      else if (percent > 1.0f) percent = 1.0f;

      for (const auto& mus : music) mus.second->setVolume(percent);
      return *this;
   }

   AudioManager& AudioManager::MusicVolume (const std::string& id, float percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return *this;

      percent /= 100.0f;

      if (percent < 0.0f) percent      = 0.0f;
      else if (percent > 1.0f) percent = 1.0f;

      mus->second->setVolume(percent);
      return *this;
   }

   AudioManager& AudioManager::MusicSpeed (float percent)
   {
      percent /= 100.0f;

      if (percent < 0.01f)     percent = 0.01f;
      else if (percent > 4.0f) percent = 4.0f;

      for (const auto& mus : music) mus.second->setPlaybackSpeed(percent);
      return *this;
   }

   AudioManager& AudioManager::MusicSpeed (const std::string& id, float percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return *this;

      percent /= 100.0f;

      if (percent < 0.01f)     percent = 0.01f;
      else if (percent > 4.0f) percent = 4.0f;

      mus->second->setPlaybackSpeed(percent);
      return *this;
   }

   AudioManager& AudioManager::MusicPan (float percent)
   {
      percent /= 100.0f;

      if (percent < -1.0f)     percent = -1.0f;
      else if (percent > 1.0f) percent = 1.0f;

      for (const auto& mus : music) mus.second->setPan(percent);
      return *this;
   }

   AudioManager& AudioManager::MusicPan (const std::string& id, float percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return *this;

      percent /= 100.0f;

      if (percent < -1.0f)     percent = -1.0f;
      else if (percent > 1.0f) percent = 1.0f;

      mus->second->setPan(percent);
      return *this;
   }

   AudioManager& AudioManager::MusicPosition (const std::string& id, size_t position)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return *this;

      if (position > mus->second->getPlayLength() - 1) position = mus->second->getPlayLength() - 1;

      mus->second->setPlayPosition(position);
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
      for (const auto& snds : sounds) {
         for (const auto& snd : snds.second) {
            snd->stop();
            snd->drop();
         }
      }

      sounds.clear();
      return *this;
   }

   AudioManager& AudioManager::StopSound (const std::string& id)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snds = sounds.find(id);
      if (snds == sounds.end()) return *this;

      for (const auto& snd : snds->second) {
         snd->stop();
         snd->drop();
      }

      sounds.erase(snds);
      return *this;
   }

   AudioManager& AudioManager::PauseSound (bool pause)
   {
      for (const auto& snds : sounds) {
         for (const auto& snd : snds.second) snd->setIsPaused(pause);
      }

      return *this;
   }

   AudioManager& AudioManager::PauseSound (const std::string& id, bool pause)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snds = sounds.find(id);
      if (snds == sounds.end()) return *this;

      for (const auto& snd : snds->second) snd->setIsPaused(pause);
      return *this;
   }

   AudioManager& AudioManager::SoundVolume (float percent)
   {
      percent /= 100.0f;

      if (percent < 0.0f)      percent = 0.0f;
      else if (percent > 1.0f) percent = 1.0f;

      for (const auto& snds : sounds) {
         for (const auto& snd : snds.second) snd->setVolume(percent);
      }

      return *this;
   }

   AudioManager& AudioManager::SoundVolume (const std::string& id, float percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snds = sounds.find(id);
      if (snds == sounds.end() || snds->second.empty()) return *this;

      percent /= 100.0f;

      if (percent < 0.0f)      percent = 0.0f;
      else if (percent > 1.0f) percent = 1.0f;

      for (const auto& snd : snds->second) snd->setVolume(percent);
      return *this;
   }

   AudioManager& AudioManager::SoundSpeed (float percent)
   {
      percent /= 100.0f;

      if (percent < 0.01f)     percent = 0.01f;
      else if (percent > 4.0f) percent = 4.0f;

      for (const auto& snds : sounds) {
         for (const auto& snd : snds.second) snd->setPlaybackSpeed(percent);
      }

      return *this;
   }

   AudioManager& AudioManager::SoundSpeed (const std::string& id, float percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snds = sounds.find(id);
      if (snds == sounds.end() || snds->second.empty()) return *this;

      percent /= 100.0f;

      if (percent < 0.01f)     percent = 0.01f;
      else if (percent > 4.0f) percent = 4.0f;

      for (const auto& snd : snds->second) snd->setPlaybackSpeed(percent);
      return *this;
   }

   AudioManager& AudioManager::SoundPan (float percent)
   {
      percent /= 100.0f;

      if (percent < -1.0f)     percent = -1.0f;
      else if (percent > 1.0f) percent = 1.0f;

      for (const auto& snds : sounds) {
         for (const auto& snd : snds.second) snd->setPan(percent);
      }

      return *this;
   }

   AudioManager& AudioManager::SoundPan (const std::string& id, float percent)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snds = sounds.find(id);
      if (snds == sounds.end() || snds->second.empty()) return *this;

      percent /= 100.0f;

      if (percent < -1.0f)     percent = -1.0f;
      else if (percent > 1.0f) percent = 1.0f;

      for (const auto& snd : snds->second) snd->setPan(percent);
      return *this;
   }

   float AudioManager::MasterVolume () const
   {
      return device->getSoundVolume() * 100.0f;
   }

   float AudioManager::DefaultVolume (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto aud = audioPool.find(id);
      if (aud == audioPool.end()) return 0.0f;

      return aud->second->getDefaultVolume() * 100.0f;
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

   float AudioManager::MusicVolume (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return 0.0f;

      return mus->second->getVolume() * 100.0f;
   }

   float AudioManager::MusicSpeed (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return 0.0f;

      return mus->second->getPlaybackSpeed() * 100.0f;
   }

   float AudioManager::MusicPan (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return 0.0f;

      return mus->second->getPan() * 100.0f;
   }

   size_t AudioManager::MusicPosition (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return 0;

      return mus->second->getPlayPosition();
   }

   size_t AudioManager::MusicLength (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto mus = music.find(id);
      if (mus == music.end()) return 0;

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

   float AudioManager::SoundVolume (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return 0.0f;

      return snd->second.back()->getVolume() * 100.0f;
   }

   float AudioManager::SoundSpeed (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return 0.0f;

      return snd->second.back()->getPlaybackSpeed() * 100.0f;
   }

   float AudioManager::SoundPan (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return 0.0f;

      return snd->second.back()->getPan() * 100.0f;
   }

   size_t AudioManager::SoundPosition (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return 0;

      return snd->second.back()->getPlayPosition();
   }

   size_t AudioManager::SoundLength (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto snd = sounds.find(id);
      if (snd == sounds.end() || snd->second.empty()) return 0;

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

