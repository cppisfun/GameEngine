
#pragma once

#include "DLL_DEF.h"

namespace irrklang {
   class ISoundEngine;
   class ISoundSource;
   class ISound;
}


namespace ge {

   /// @brief Audio-Basisklasse zur Steuerung von Sound- und Musik-Wiedergabe.
   /// Wird über Core::Audio() geliefert.
   class GEDLL AudioCore
   {
      irrklang::ISoundEngine* device;

      std::map<std::string, irrklang::ISoundSource*>       audioPool;
      std::map<std::string, irrklang::ISound*>             music;
      std::map<std::string, std::deque<irrklang::ISound*>> sounds;

      void Init ();

   public:
      /// @brief Konstruktor.
      AudioCore ();

      /// @brief Destruktor. Gibt automatisch alle in AudioCore gehaltenen
      /// Audio-Ressourcen frei.
      virtual ~AudioCore ();


      /// @brief Erstellt eine Audio-Ressource direkt aus einer Datei (ohne den
      /// Einsatz von ResourceCore).
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param audioFile Dateipfad
      AudioCore& Add (const std::string& id, const std::string& audioFile);

      /// @brief Erstellt eine Audio-Ressource aus bereits im Speicher
      /// befindlichen Binärdaten (normalerweise im ResourceCore gehalten).
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param resource Binärdaten
      AudioCore& Add (const std::string& id, const Binary& resource);

      /// @brief Entfernt eine Audio-Ressource.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      AudioCore& Remove (const std::string& id);

      /// @brief Entfernt alle vorhandenen Audio-Ressourcen.
      AudioCore& RemoveAll ();


      /// @brief Stoppt die Wiedergabe aller vorhandenen Audio-Objekte.
      AudioCore& StopAll ();

      /// @brief Pausiert die Wiedergabe aller vorhandenen Audio-Objekte oder setzt diese fort.
      /// @param pause Gibt an, ob die Wiedergabe pausiert oder fortgesetzt werden soll (Standard: false)
      AudioCore& PauseAll (bool pause = true);


      /// @brief Legt die allgemeine Lautstärke für alle Audio-Ressourcen fest.
      /// @param percent Lautstärke in Prozent (0 = lautlos, 100 = volle Lautstärke)
      AudioCore& MasterVolume (int percent);

      /// @brief Legt die Lautstärke für eine bestimmte Audio-Ressource fest.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param percent Lautstärke in Prozent (0 = lautlos, 100 = volle Lautstärke)
      AudioCore& DefaultVolume (const std::string& id, int percent);


      /// @brief Erzeugt ein neues Musik-Objekt aus einer Audio-Ressource und startet die Wiedergabe.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param looped Gibt an, ob die Wiedergabe einfach oder endlos sein soll (Standard: false)
      AudioCore& PlayMusic (const std::string& id, bool looped = false);

      /// @brief Stoppt die Wiedergabe aller vorhandenen Musik-Objekte.
      AudioCore& StopMusic ();

      /// @brief Stoppt die Wiedergabe eines bestimmten Musik-Objekts.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      AudioCore& StopMusic (const std::string& id);

      /// @brief Pausiert die Wiedergabe aller vorhandenen Musik-Objekte oder setzt diese fort.
      /// @param pause Gibt an, ob die Wiedergabe pausiert oder fortgesetzt werden soll (Standard: false)
      AudioCore& PauseMusic (bool pause = true);

      /// @brief Pausiert die Wiedergabe eines bestimmten Musik-Objekts oder setzt diese fort.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param pause Gibt an, ob die Wiedergabe pausiert oder fortgesetzt werden soll (Standard: false)
      AudioCore& PauseMusic (const std::string& id, bool pause = true);

      /// @brief Legt die allgemeine Lautstärke für alle Musik-Objekte fest.
      /// @param percent Lautstärke in Prozent (0 = lautlos, 100 = volle Lautstärke)
      AudioCore& MusicVolume (int percent);

      /// @brief Legt die Lautstärke für ein bestimmtes Musik-Objekt fest.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param percent Lautstärke in Prozent (0 = lautlos, 100 = volle Lautstärke)
      AudioCore& MusicVolume (const std::string& id, int percent);

      /// @brief Legt die Abspiel-Geschwindigkeit aller Musik-Objekte fest.
      /// @param percent Geschwindigkeit in Prozent (1 = annähernd gestoppt, 400 = vierfache Geschwindigkeit)
      AudioCore& MusicSpeed (int percent);

      /// @brief Legt die Abspiel-Geschwindigkeit eines bestimmten Musik-Objekts fest.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param percent Geschwindigkeit in Prozent (1 = annähernd gestoppt, 400 = vierfache Geschwindigkeit)
      AudioCore& MusicSpeed (const std::string& id, int percent);

      /// @brief Legt die horizontale Position aller Musik-Objekte bei Stereo-Wiedergabe fest.
      /// @param percent Position in Prozent (-100 = nur links, 100 = nur rechts)
      AudioCore& MusicPan (int percent);

      /// @brief Legt die horizontale Position eines bestimmten Musik-Objekts bei Stereo-Wiedergabe fest.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param percent Position in Prozent (-100 = nur links, 100 = nur rechts)
      AudioCore& MusicPan (const std::string& id, int percent);

      /// @brief Legt die aktuelle Abspiel-Position eines bestimmten Musik-Objekts fest.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param position Position (0 = Anfang, [Länge der Musik-Ressource] = Ende)
      AudioCore& MusicPosition (const std::string& id, int position);


      /// @brief Erzeugt ein neues Sound-Objekt aus einer Audio-Ressource und startet die Wiedergabe.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param looped Gibt an, ob die Wiedergabe einfach oder endlos sein soll (Standard: false)
      AudioCore& PlaySound (const std::string& id, bool looped = false);

      /// @brief Stoppt die Wiedergabe aller vorhandenen Sound-Objekte.
      AudioCore& StopSound ();

      /// @brief Stoppt die Wiedergabe eines bestimmten Sound-Objekts.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      AudioCore& StopSound (const std::string& id);

      /// @brief Pausiert die Wiedergabe aller vorhandenen Sound-Objekte oder setzt diese fort.
      /// @param pause Gibt an, ob die Wiedergabe pausiert oder fortgesetzt werden soll (Standard: false)
      AudioCore& PauseSound (bool pause = true);

      /// @brief Pausiert die Wiedergabe eines bestimmten Sound-Objekts oder setzt diese fort.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param pause Gibt an, ob die Wiedergabe pausiert oder fortgesetzt werden soll (Standard: false)
      AudioCore& PauseSound (const std::string& id, bool pause = true);

      /// @brief Legt die allgemeine Lautstärke für alle Sound-Objekte fest.
      /// @param percent Lautstärke in Prozent (0 = lautlos, 100 = volle Lautstärke)
      AudioCore& SoundVolume (int percent);

      /// @brief Legt die Lautstärke für ein bestimmtes Sound-Objekt fest.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param percent Lautstärke in Prozent (0 = lautlos, 100 = volle Lautstärke)
      AudioCore& SoundVolume (const std::string& id, int percent);

      /// @brief Legt die Abspiel-Geschwindigkeit aller Sound-Objekte fest.
      /// @param percent Geschwindigkeit in Prozent (1 = annähernd gestoppt, 400 = vierfache Geschwindigkeit)
      AudioCore& SoundSpeed (int percent);

      /// @brief Legt die Abspiel-Geschwindigkeit eines bestimmten Sound-Objekts fest.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param percent Geschwindigkeit in Prozent (1 = annähernd gestoppt, 400 = vierfache Geschwindigkeit)
      AudioCore& SoundSpeed (const std::string& id, int percent);

      /// @brief Legt die horizontale Position aller Sound-Objekte bei Stereo-Wiedergabe fest.
      /// @param percent Position in Prozent (-100 = nur links, 100 = nur rechts)
      AudioCore& SoundPan (int percent);

      /// @brief Legt die horizontale Position eines bestimmten Sound-Objekts bei Stereo-Wiedergabe fest.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @param percent Position in Prozent (-100 = nur links, 100 = nur rechts)
      AudioCore& SoundPan (const std::string& id, int percent);


      /// @brief Setzt die Wiedergabe aller gestoppten Audio-Objekte fort.
      AudioCore& ResumeAll () { return PauseAll(false); }

      /// @brief Setzt die Wiedergabe aller gestoppten Musik-Objekte fort.
      AudioCore& ResumeMusic () { return PauseMusic(false); }

      /// @brief Setzt die Wiedergabe eines bestimmten gestoppten Musik-Objekts fort.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      AudioCore& ResumeMusic (const std::string& id) { return PauseMusic(id, false); }

      /// @brief Setzt die Wiedergabe aller gestoppten Sound-Objekte fort.
      AudioCore& ResumeSound () { return PauseSound(false); }

      /// @brief Setzt die Wiedergabe eines bestimmten gestoppten Sound-Objekts fort.
      AudioCore& ResumeSound (const std::string& id) { return PauseSound(id, false); }


      /// @brief Liefert den Pointer zum irrKlang-Objekt, welches vom AudioCore-Objekt verwendet wird.
      irrklang::ISoundEngine* Device () const { return device; }


      /// @brief Liefert die Lautstärke, die für alle Audio-Ressourcen gilt.
      /// @return Lautstärke in Prozent (0 = lautlos, 100 = volle Lautstärke)
      int MasterVolume () const;

      /// @brief Liefert die Lautstärke, die für eine bestimmte Audio-Ressource gilt.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @return Lautstärke in Prozent (0 = lautlos, 100 = volle Lautstärke)
      int DefaultVolume (const std::string& id) const;

      /// @brief Ermittelt, ob eine bestimmte Audio-Ressource gerade wiedergegeben wird.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      bool IsPlaying (const std::string& id) const;


      /// @brief Ermittelt, ob ein bestimmtes Musik-Objekt gerade wiedergegeben wird.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      bool IsMusicPaused (const std::string& id) const;

      /// @brief Ermittelt, ob ein bestimmtes Musik-Objekt endlos wiedergegeben wird.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      bool IsMusicLooped (const std::string& id) const;

      /// @brief Ermittelt, ob die Wiedergabe eines bestimmten Musik-Objektes abgeschlossen ist.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      bool IsMusicFinished (const std::string& id) const;

      /// @brief Liefert die Lautstärke eines bestimmten Musik-Objekts.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @return Lautstärke in Prozent (0 = lautlos, 100 = volle Lautstärke)
      int MusicVolume (const std::string& id) const;

      /// @brief Liefert die Abspiel-Geschwindigkeit eines bestimmten Musik-Objekts.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @return Geschwindigkeit in Prozent (1 = annähernd gestoppt, 400 = vierfache Geschwindigkeit)
      int MusicSpeed (const std::string& id) const;

      /// @brief Liefert die horizontale Position eines bestimmten Musik-Objekts (Stereo).
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @return Position in Prozent (-100 = nur links, 100 = nur rechts)
      int MusicPan (const std::string& id) const;

      /// @brief Liefert die aktuelle Abspiel-Position eines bestimmten Musik-Objekts.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @return Position (0 = Anfang, [Länge der Musik-Ressource] = Ende)
      int MusicPosition (const std::string& id) const;

      /// @brief Liefert die Länge eines bestimmten Musik-Objekts.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      int MusicLength (const std::string& id) const;


      /// @brief Ermittelt, ob ein bestimmtes Sound-Objekt gerade wiedergegeben wird.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      bool IsSoundPaused (const std::string& id) const;

      /// @brief Ermittelt, ob ein bestimmtes Sound-Objekt endlos wiedergegeben wird.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      bool IsSoundLooped (const std::string& id) const;

      /// @brief Ermittelt, ob die Wiedergabe eines bestimmten Sound-Objektes abgeschlossen ist.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      bool IsSoundFinished (const std::string& id) const;

      /// @brief Liefert die Lautstärke eines bestimmten Sound-Objekts.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @return Lautstärke in Prozent (0 = lautlos, 100 = volle Lautstärke)
      int SoundVolume (const std::string& id) const;

      /// @brief Liefert die Abspiel-Geschwindigkeit eines bestimmten Sound-Objekts.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @return Geschwindigkeit in Prozent (1 = annähernd gestoppt, 400 = vierfache Geschwindigkeit)
      int SoundSpeed (const std::string& id) const;

      /// @brief Liefert die horizontale Position eines bestimmten Sound-Objekts (Stereo).
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @return Position in Prozent (-100 = nur links, 100 = nur rechts)
      int SoundPan (const std::string& id) const;

      /// @brief Liefert die aktuelle Abspiel-Position eines bestimmten Sound-Objekts.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      /// @return Position (0 = Anfang, [Länge der Sound-Ressource] = Ende)
      int SoundPosition (const std::string& id) const;

      /// @brief Liefert die Länge eines bestimmten Sound-Objekts.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      int SoundLength (const std::string& id) const;


      /// @brief Liefert den Namen/Dateipfad einer bestimmten Audio-Ressource.
      /// @param id Eindeutiger Bezeichner der Audio-Ressource
      const std::string FileName (const std::string& id) const;
   };

}

