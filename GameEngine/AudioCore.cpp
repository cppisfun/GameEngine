
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

const std::string AudioCore::FileName (const std::string& id) const
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto aud = audioPool.find(id);
   if (aud == audioPool.end()) return "";

   return std::string(aud->second->getName());
}

