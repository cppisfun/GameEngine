
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
   if (device != nullptr) device->drop();
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
   return *this;
}

AudioCore& AudioCore::Play (const std::string& id, bool looped)
{
   if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

   auto aud = audioPool.find(id);
   if (aud == audioPool.end()) return *this;

   device->play2D(aud->second, looped);
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

AudioCore& AudioCore::ResumeAll ()
{
   device->setAllSoundsPaused(false);
   return *this;
}

