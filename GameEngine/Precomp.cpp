
#include "Precomp.h"

/**
 * \mainpage �ber dieses Projekt
 *
 * \section ShortDesc 1. Kurzbeschreibung
 *
 * Ziel des Projektes GameEngine ist es, eine simpel gehaltene Plattform f�r
 * zweidimensionale RPG-Spiele umzusetzen, die bereits �ber alle n�tigen
 * Grundfunktionen verf�gt. In den meisten F�llen wird es n�tig sein, eigene
 * Funktionen hinzuzuf�gen, da die Engine sehr allgemein gehalten wird.
 *
 * Es handelt sich hierbei um ein reines Freizeitprojekt, daher wird sich
 * immer wieder vieles �ndern und viel Zeit vergehen, bis das Porjekt einen
 * Stand erreicht, mit dem sich etwas anfangen l�sst.
 *
 * \section whatsInside 2. Komponenten
 *
 * Es gibt zwei gro�e Bereiche, in welche sich das Projekt unterteilen l�sst,
 * Base und GameEngine. In Base sind einige Funktionen untergebracht, die
 * unabh�ngig von der Engine sinnvoll sein k�nnen. GameEngine beinhaltet die
 * eigentliche Grundlage zur Umsetzung eines Spiels.
 *
 * \subsection whatsInBase 2.1 Base
 *
 * Base unterteilt sich in verschiedene Namespaces, um die Funktionalit�t zu
 * kategorisieren.
 *
 * \subsubsection baseBase 2.1.1 Namespace base
 *
 * Beinhaltet Basisfunktionen aus den Bereichen Konvertierung, Manipulation
 * von Strings und Zahlenwerten, Filesystem-Funktionen usw.
 *
 * \subsubsection baseError 2.1.2 Namespace error
 * Beinhaltet von std::exception abgeleitete Fehlerspezifikationen, die es
 * leichter machen, im Fehlerfall sprechende Ausgaben bzw. Logging zu erzeugen.
 *
 * \subsubsection baseMisc 2.1.3 Namespace misc
 * Beinhaltet Funktionen, die nicht direkt dem Kern zugeschrieben werden k�nnen,
 * sich aber im praktischen Einsatz als n�tzliche Basisfunktionen erwiesen
 * haben. Hierunter fallen beispielsweise Hilfsklassen wie LimitedValue.
 *
 * \subsection whatsInGE 2.2 GameEngine
 *
 * Hier befinden sich das Fundament f�r das Erstellen eines Spiels. Um
 * Namenskonflikte zu vermeiden, wurde f�r alle GameEngine-Inhalte der
 * Namespace __ge__ verwendet.
 *
 * Zentraler Bestandteil der GameEngine ist die Singleton-Klasse __Core__.
 * Diese liefert die im Folgenden beschriebenen Einzelkomponenten und beinhaltet
 * ansonsten nur wenige Zusatzfunktionen, beispielsweise das Umschalten.
 * zwischen Fenster- und Fullscreen-Modus.
 *
 * \subsubsection geAudio 2.2.1 AudioCore
 *
 * Beinhaltet alle Basisfunktionen, die in den Bereich Audio fallen. Hierzu
 * geh�ren sowohl Sound- als auch Musik-Wiedergabe. Das Aufzeichnen von Sounds
 * ist nicht vorgesehen und auch nicht geplant.
 *
 * \subsubsection geGraphics 2.2.2 GraphicsCore
 *
 * Beinhaltet alle Basisfunktionen, die mit elementaren Zeichenoperationen zu
 * tun haben. So gibt es beispielsweise Funktionen zum Verwalten und Zeichnen
 * von Texturen, die Funktionalit�t f�r Sprites, Maps und (scrollende)
 * Hintergr�nde wird jedoch in anderen Klassen zur Verf�gung gestellt.
 *
 * \subsubsection geInput 2.2.3 InputCore
 *
 * Liefert die n�tigen Klassen f�r die Behandlung der Eingaben �ber Taststur,
 * Maus und Gamepads und unter anderem eine Update-Funktion f�r alle genannten
 * und verwendeten Eingabeger�te.
 *
 * __2.2.3.1 InputKeyboard__
 *
 * Dient der Behandlung von Taststureingaben.
 *
 * __2.2.3.2 InputMouse__
 *
 * Dient der Behandlung von Mauseingaben.
 *
 * __2.2.3.3 InputGamepad__
 *
 * Dient der Behandlung von Eingaben �ber vorhandene Gamepads. Es werden
 * mehrere Modi unterst�tzt, beispielsweise NES, SNES oder SEGA MegaDrive.
 *
 * \subsubsection geResources 2.2.4 ResourcesCore
 *
 * Verwaltet Spielressourcen in String- oder Bin�rform, z.B. Scripts, XMLs oder
 * Musik-Daten. Ausnahmen bestehen bei Textur- und Font-Ressourcen; diese werden
 * direkt im GraphicsCore verwaltet.
 *
 * \section Foreign 3. Fremdkomponenten
 *
 * Das Projekt GameEngine st�tzt sich im Bereich der Basisklassen auf drei
 * Fremdkomponenten, die bereits einige lang erprobte und komfortable Funktionen
 * aufweisen k�nnen.
 *
 * \subsection foreignBoost 3.1 boost
 *
 * Die in Base vorhandenen Funktionen sowie Teile der GameEngine-DLL verwenden
 * die Funktionalit�t von boost 1.80, insbesondere boost::filesystem wird an
 * allen passenden Stellen eingesetzt.
 *
 * \subsection foreignIrrlicht 3.2 irrlicht
 *
 * Hinter den Basisklassen Core, GraphicsCore und InputCore verbirgt sich an
 * vielen Stellen die leistungsstarke Funktionalit�t von irrlicht 1.7.3, einem
 * Opensource-Framework zur Spiele-Entwicklung. Insbesondere im Hinblick auf die
 * bereits komplett vorhandene Grafik-Engine wurde diese Komponente eingebunden.
 *
 * \subsection foreignIrrklang 3.3 irrKlang
 *
 * Neben irrlicht existiert ein passendes Audio-Framework, welches ebenfalls
 * eingebunden wurde: irrKlang in Version 1.40. Die Klasse AudioCore bedient
 * sich der Funktionen aus irrKlang.
 */



/// @brief _Beschreibung siehe irrlicht-Dokumentation._
namespace irr {
   /// @brief _Beschreibung siehe irrlicht-Dokumentation._
   namespace gui { }
}

/// @brief _Beschreibung siese irrKlang-Dokumentation._
namespace irrklang { }

