
#include "Precomp.h"

#include <irrKlang.h>

#include "AudioCore.h"

#include "../Base/Error.h"

using namespace irrklang;


AudioCore::AudioCore () : device(nullptr)
{
   Init();
}

AudioCore::~AudioCore ()
{
   if (device != nullptr) {
      device->stopAllSounds();

      std::for_each(music.begin(), music.end(), [] (const std::pair<std::string, ISound*> mus) {
         mus.second->drop();
      });

      for (auto it = sounds.begin(); it != sounds.end(); ++it) {
         std::for_each(it->second.begin(), it->second.end(), [] (ISound* snd) {
            snd->drop();
         });
      }

      std::for_each(audioPool.begin(), audioPool.end(), [] (const std::pair<std::string, ISoundSource*> aud) {
         aud.second->drop();
      });
   }
}

void AudioCore::Init ()
{
   device = createIrrKlangDevice();
   if (device == nullptr) throw error::Create("Failed to create irrKlang audio device!", __FUNCTION__);
}

AudioCore& AudioCore::Add (const std::string& id, const std::string& audioFile)
{
   if (id.empty())                                 throw error::InvalidParam("No id specified!", __FUNCTION__);
   else if (audioFile.empty())                     throw error::InvalidParam("No audio file specified!", __FUNCTION__);
   else if (audioPool.find(id) != audioPool.end()) throw error::AlreadyExists("Audio resource with specified id already exists!", __FUNCTION__);

   auto aud = device->addSoundSourceFromFile(audioFile.c_str(), ESM_AUTO_DETECT, true);
   if (aud == nullptr) throw error::Read("Failed to read audio file!", __FUNCTION__);

   audioPool[id] = aud;
   return *this;
}

AudioCore& AudioCore::Add (const std::string& id, const std::vector<char>& resource)
{
   if (id.empty())                                 throw error::InvalidParam("No id specified!", __FUNCTION__);
   else if (resource.empty())                      throw error::InvalidParam("No resource data specified!", __FUNCTION__);
   else if (audioPool.find(id) != audioPool.end()) throw error::AlreadyExists("Audio resource with specified id already exists!", __FUNCTION__);

   auto aud = device->addSoundSourceFromMemory((void*)&resource[0], resource.size(), id.c_str());
   if (aud == nullptr) throw error::Query("Failed to query resource data!", __FUNCTION__);

   audioPool[id] = aud;
   return *this;
}

AudioCore& AudioCore::Remove (const std::string& id)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto aud = audioPool.find(id);
   if (aud == audioPool.end()) return *this;

   device->removeSoundSource(aud->second);
   audioPool.erase(aud);

   return *this;
}

AudioCore& AudioCore::RemoveAll ()
{
   device->removeAllSoundSources();
   audioPool.clear();

   return *this;
}

AudioCore& AudioCore::StopAll ()
{
   device->stopAllSounds();
   return *this;
}

AudioCore& AudioCore::PauseAll (bool pause)
{
   device->setAllSoundsPaused(pause);
   return *this;
}

AudioCore& AudioCore::MasterVolume (int percent)
{
   float vol = boost::numeric_cast<float>(percent) / 100.0f;

   if (vol < 0.0f) vol      = 0.0f;
   else if (vol > 1.0f) vol = 1.0f;

   device->setSoundVolume(vol);
   return *this;
}

AudioCore& AudioCore::DefaultVolume (const std::string& id, int percent)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto aud = audioPool.find(id);
   if (aud == audioPool.end()) return *this;

   float vol = boost::numeric_cast<float>(percent) / 100.0f;

   if (vol < 0.0f)      vol = 0.0f;
   else if (vol > 1.0f) vol = 1.0f;

   aud->second->setDefaultVolume(vol);
   return *this;
}

AudioCore& AudioCore::PlayMusic (const std::string& id, bool looped)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);
   else if (music.find(id) != music.end()) return *this;

   auto aud = audioPool.find(id);
   if (aud == audioPool.end()) return *this;

   auto mus = device->play2D(aud->second, looped, false, true, false);
   if (mus == nullptr) return *this;

   music[id] = mus;
   return *this;
}

AudioCore& AudioCore::StopMusic ()
{
   std::for_each(music.begin(), music.end(), [] (const std::pair<std::string, ISound*> mus) {
      mus.second->stop();
   });

   return *this;
}

AudioCore& AudioCore::StopMusic (const std::string& id)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return *this;

   mus->second->stop();
   return *this;
}

AudioCore& AudioCore::PauseMusic (bool pause)
{
   std::for_each(music.begin(), music.end(), [&pause] (const std::pair<std::string, ISound*> mus) {
      mus.second->setIsPaused(pause);
   });

   return *this;
}

AudioCore& AudioCore::PauseMusic (const std::string& id, bool pause)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return *this;

   mus->second->setIsPaused(pause);
   return *this;
}

AudioCore& AudioCore::MusicVolume (int percent)
{
   float vol = boost::numeric_cast<float>(percent) / 100.0f;

   if (vol < 0.0f)      vol = 0.0f;
   else if (vol > 1.0f) vol = 1.0f;

   std::for_each(music.begin(), music.end(), [&vol] (const std::pair<std::string, ISound*>& mus) {
      mus.second->setVolume(vol);
   });

   return *this;
}

AudioCore& AudioCore::MusicVolume (const std::string& id, int percent)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return *this;

   float vol = boost::numeric_cast<float>(percent) / 100.0f;

   if (vol < 0.0f) vol      = 0.0f;
   else if (vol > 1.0f) vol = 1.0f;

   mus->second->setVolume(vol);
   return *this;
}

AudioCore& AudioCore::MusicSpeed (int percent)
{
   float spd = boost::numeric_cast<float>(percent) / 100.0f;

   std::for_each(music.begin(), music.end(), [&spd] (const std::pair<std::string, ISound*>& mus) {
      mus.second->setPlaybackSpeed(spd);
   });

   return *this;
}

AudioCore& AudioCore::MusicSpeed (const std::string& id, int percent)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return *this;

   mus->second->setPlaybackSpeed(boost::numeric_cast<float>(percent) / 100.0f);
   return *this;
}

AudioCore& AudioCore::MusicPan (int percent)
{
   float pan = boost::numeric_cast<float>(percent) / 100.0f;

   if (pan < -1.0f)     pan = -1.0f;
   else if (pan > 1.0f) pan = 1.0f;

   std::for_each(music.begin(), music.end(), [&pan] (const std::pair<std::string, ISound*>& mus) {
      mus.second->setPan(pan);
   });

   return *this;
}

AudioCore& AudioCore::MusicPan (const std::string& id, int percent)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return *this;

   float pan = boost::numeric_cast<float>(percent) / 100.0f;

   if (pan < -1.0f)     pan = -1.0f;
   else if (pan > 1.0f) pan = 1.0f;

   mus->second->setPan(pan);
   return *this;
}

AudioCore& AudioCore::MusicPosition (const std::string& id, int position)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return *this;

   size_t pos;

   if (position < 0)                                     pos = 0;
   else if (position > mus->second->getPlayLength() - 1) pos = mus->second->getPlayLength() - 1;
   else                                                  pos = position;

   mus->second->setPlayPosition(pos);
   return *this;
}

AudioCore& AudioCore::PlaySound (const std::string& id, bool looped)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto aud = audioPool.find(id);
   if (aud == audioPool.end()) return *this;

   auto snd = device->play2D(aud->second, looped, false, true, false);
   if (snd == nullptr) return *this;

   sounds[id].push_back(snd);
   return *this;
}

AudioCore& AudioCore::StopSound ()
{
   for (auto it = sounds.begin(); it != sounds.end(); ++it) {
      std::for_each(it->second.begin(), it->second.end(), [] (ISound* snd) {
         snd->stop();
         snd->drop();
      });
   }

   sounds.clear();
   return *this;
}

AudioCore& AudioCore::StopSound (const std::string& id)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end()) return *this;

   std::for_each(snd->second.begin(), snd->second.end(), [] (ISound* snd) {
      snd->stop();
      snd->drop();
   });

   sounds.erase(snd);
   return *this;
}

AudioCore& AudioCore::PauseSound (bool pause)
{
   for (auto it = sounds.begin(); it != sounds.end(); ++it) {
      std::for_each(it->second.begin(), it->second.end(), [&pause] (ISound* snd) {
         snd->setIsPaused(pause);
      });
   }

   return *this;
}

AudioCore& AudioCore::PauseSound (const std::string& id, bool pause)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end()) return *this;

   std::for_each(snd->second.begin(), snd->second.end(), [&pause] (ISound* snd) {
      snd->setIsPaused(pause);
   });

   return *this;
}

AudioCore& AudioCore::SoundVolume (int percent)
{
   float vol = boost::numeric_cast<float>(percent) / 100.0f;

   if (vol < 0.0f)      vol = 0.0f;
   else if (vol > 1.0f) vol = 1.0f;

   for (auto it = sounds.begin(); it != sounds.end(); ++it) {
      std::for_each(it->second.begin(), it->second.end(), [&vol] (ISound* snd) {
         snd->setVolume(vol);
      });
   }

   return *this;
}

AudioCore& AudioCore::SoundVolume (const std::string& id, int percent)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end() || snd->second.empty()) return *this;

   float vol = boost::numeric_cast<float>(percent) / 100.0f;

   if (vol < 0.0f)      vol = 0.0f;
   else if (vol > 1.0f) vol = 1.0f;

   std::for_each(snd->second.begin(), snd->second.end(), [&vol] (ISound* sound) {
      sound->setVolume(vol);
   });

   return *this;
}

AudioCore& AudioCore::SoundSpeed (int percent)
{
   float spd = boost::numeric_cast<float>(percent) / 100.0f;

   for (auto it = sounds.begin(); it != sounds.end(); ++it) {
      std::for_each(it->second.begin(), it->second.end(), [&spd] (ISound* snd) {
         snd->setPlaybackSpeed(spd);
      });
   }

   return *this;
}

AudioCore& AudioCore::SoundSpeed (const std::string& id, int percent)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end() || snd->second.empty()) return *this;

   float spd = boost::numeric_cast<float>(percent) / 100.0f;

   std::for_each(snd->second.begin(), snd->second.end(), [&spd] (ISound* sound) {
      sound->setPlaybackSpeed(spd);
   });

   return *this;
}

AudioCore& AudioCore::SoundPan (int percent)
{
   float pan = boost::numeric_cast<float>(percent) / 100.0f;

   if (pan < -1.0f)     pan = -1.0f;
   else if (pan > 1.0f) pan = 1.0f;

   for (auto it = sounds.begin(); it != sounds.end(); ++it) {
      std::for_each(it->second.begin(), it->second.end(), [&pan] (ISound* snd) {
         snd->setPan(pan);
      });
   }

   return *this;
}

AudioCore& AudioCore::SoundPan (const std::string& id, int percent)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end() || snd->second.empty()) return *this;

   float pan = boost::numeric_cast<float>(percent) / 100.0f;

   if (pan < -1.0f)     pan = -1.0f;
   else if (pan > 1.0f) pan = 1.0f;

   std::for_each(snd->second.begin(), snd->second.end(), [&pan] (ISound* sound) {
      sound->setPan(pan);
   });

   return *this;
}

int AudioCore::MasterVolume () const
{
   int vol = boost::numeric_cast<int>(device->getSoundVolume() * 100.0f);

   if (vol < 0)        vol = 0;
   else if (vol > 100) vol = 100;

   return vol;
}

int AudioCore::DefaultVolume (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto aud = audioPool.find(id);
   if (aud == audioPool.end()) return 0;

   int vol = boost::numeric_cast<int>(aud->second->getDefaultVolume() * 100.0f);

   if (vol < 0)        vol = 0;
   else if (vol > 100) vol = 100;

   return vol;
}

bool AudioCore::IsPlaying (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto aud = audioPool.find(id);
   if (aud == audioPool.end()) return false;

   return device->isCurrentlyPlaying(aud->second);
}

bool AudioCore::IsMusicPaused (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return false;

   return mus->second->getIsPaused();
}

bool AudioCore::IsMusicLooped (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return false;

   return mus->second->isLooped();
}

bool AudioCore::IsMusicFinished (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return true;

   return mus->second->isFinished();
}

int AudioCore::MusicVolume (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return 0;

   int vol = boost::numeric_cast<int>(mus->second->getVolume() * 100.0f);

   if (vol < 0)        vol = 0;
   else if (vol > 100) vol = 100;

   return vol;
}

int AudioCore::MusicSpeed (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return 0;

   return boost::numeric_cast<int>(mus->second->getPlaybackSpeed() * 100.0f);
}

int AudioCore::MusicPan (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return 0;

   int pan = boost::numeric_cast<int>(mus->second->getPan() * 100.0f);

   if (pan < -100)     pan = -100;
   else if (pan > 100) pan = 100;

   return pan;
}

int AudioCore::MusicPosition (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return -1;

   return mus->second->getPlayPosition();
}

int AudioCore::MusicLength (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto mus = music.find(id);
   if (mus == music.end()) return -1;

   return mus->second->getPlayLength();
}

bool AudioCore::IsSoundPaused (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end() || snd->second.empty()) return false;

   return snd->second.back()->getIsPaused();
}

bool AudioCore::IsSoundLooped (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end() || snd->second.empty()) return false;

   return snd->second.back()->isLooped();
}

bool AudioCore::IsSoundFinished (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end() || snd->second.empty()) return true;

   return snd->second.back()->isFinished();
}

int AudioCore::SoundVolume (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end() || snd->second.empty()) return 0;

   int vol = boost::numeric_cast<int>(snd->second.back()->getVolume() * 100.0f);

   if (vol < 0)        vol = 0;
   else if (vol > 100) vol = 100;

   return vol;
}

int AudioCore::SoundSpeed (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end() || snd->second.empty()) return 0;

   return boost::numeric_cast<int>(snd->second.back()->getPlaybackSpeed() * 100.0f);
}

int AudioCore::SoundPan (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end() || snd->second.empty()) return 0;

   int pan = boost::numeric_cast<int>(snd->second.back()->getPan() * 100.0f);

   if (pan < -100)     pan = -100;
   else if (pan > 100) pan = 100;

   return pan;
}

int AudioCore::SoundPosition (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end() || snd->second.empty()) return -1;

   return snd->second.back()->getPlayPosition();
}

int AudioCore::SoundLength (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto snd = sounds.find(id);
   if (snd == sounds.end() || snd->second.empty()) return -1;

   return snd->second.back()->getPlayLength();
}

const std::string AudioCore::FileName (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto aud = audioPool.find(id);
   if (aud == audioPool.end()) return "";

   return std::string(aud->second->getName());
}

