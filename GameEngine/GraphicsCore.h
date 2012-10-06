
#pragma once

#include <irrlicht.h>

#include "Color.h"
#include "Rectangle.h"

#include "DLL_DEF.h"


namespace ge {

   /// @brief Grafik-Basisklasse zur Steuerung von Grafik und Textausgabe.
   /// Wird über Core::Graphics() geliefert.
   class GEDLL GraphicsCore
   {
   public:
      /// @brief Auflistung der möglichen Modusangaben zur Verwendung mit
      /// GraphicsCore::DrawRectangle().
      enum DrawType {
         Fill = 0,
         Outline
      };

   private:
      irr::video::IVideoDriver* driver;
      irr::gui::IGUIEnvironment* gui;

      Color clearColor;
      Color foreColor;
      Color backColor;

      irr::gui::IGUIFont* systemFont;
      irr::gui::IGUIFont* defaultFont;

      std::map<std::string, irr::gui::IGUIFont*> fonts;
      std::map<std::string, irr::video::ITexture*> textures;

      void Init (irr::IrrlichtDevice* device);
      void DrawText (int x, int y, const std::string& text, irr::gui::IGUIFont* font);

   public:
      /// @brief Konstruktor. Benötigt einen Pointer zu einem validen
      /// irrlicht-Device (wird automatisch bei der Initialisierung über Core
      /// übergeben).
      GraphicsCore (irr::IrrlichtDevice* device);

      /// @brief Destruktor. Gibt automatisch alle in GraphicsCore gehaltenen
      /// Textur- und Font-Ressourcen frei.
      virtual ~GraphicsCore ();


      /// @brief Legt die Farbe fest, mit welcher der Grafik-Puffer "gelöscht"
      /// wird.
      GraphicsCore& ClearColor (const Color& color) { clearColor = color; return *this; }

      /// @brief Legt die Farbe fest, welche bei Zeichenoperationen als
      /// Vordergrundfarbe/Zeichenfarbe verwendet wird.
      GraphicsCore& ForeColor (const Color& color) { foreColor = color; return *this; }

      /// @brief Legt die Farbe fest, welche bei Zeichenoperationen als
      /// @brief Hintergrundfarbe/Füllfarbe verwendet wird.
      GraphicsCore& BackColor (const Color& color) { backColor = color; return *this; }


      /// @brief Erstellt die Schriftart für System-Ausgaben und Logging aus
      /// einer entsprechenden XML-Datei.
      /// @param fontFile Dateipfad
      GraphicsCore& SystemFont (const std::string& fontFile);

      /// @brief Erstellt die Schriftart für Standard-Ausgaben aus einer
      /// entsprechenden XML-Datei.
      /// @param fontFile Dateipfad
      GraphicsCore& DefaultFont (const std::string& fontFile);

      /// @brief Fügt eine Schriftart aus einer entsprechenden XML-Datei hinzu.
      /// @param id Eindeutiger Bezeichner der Schriftart im Schriftarten-Pool
      /// @param fontFile Dateipfad
      GraphicsCore& AddFont (const std::string& id, const std::string& fontFile);

      /// @brief Entfernt eine Schriftart.
      /// @param id Eindeutiger Bezeichner der Schriftart im Schriftarten-Pool
      GraphicsCore& RemoveFont (const std::string& id);

      /// @brief Entfernt alle Schriftarten (bis auf System-Schriftart und
      /// Standard-Schriftart).
      GraphicsCore& RemoveAllFonts ();


      /// @brief Fügt eine Textur aus einer entsprechenden Datei hinzu.
      /// @param id Eindeutiger Bezeichner der Textur im Texturen-Pool
      /// @param textureFile Dateipfad
      GraphicsCore& AddTexture (const std::string& id, const std::string& textureFile);

      /// @brief Entfernt eine Textur.
      /// @param id Eindeutiger Bezeichner der Textur im Texturen-Pool
      GraphicsCore& RemoveTexture (const std::string& id);

      /// @brief Entfernt alle Texturen.
      GraphicsCore& RemoveAllTextures ();


      /// @brief Bereitet das irrlicht-Device auf den Beginn der
      /// Zeichenoperationen vor und _muss_ daher vor der ersten
      /// Zeichenoperation aufgerufen werden.
      void BeginScene ();

      /// @brief Bereitet das irrlicht-Device auf das Anzeigen des geänderten
      /// Grafikpuffers vor und _muss_ daher nach der letzten Zeichenoperation
      /// aufgerufen werden.
      void EndScene ();


      /// @brief Zeichnet einen Punkt.
      GraphicsCore& DrawPixel (int x, int y, const Color& color);

      /// @brief Zeichnet eine Linie.
      GraphicsCore& DrawLine (int left, int top, int right, int bottom, const Color& color);

      /// @brief Zeichnet ein Rechteck unter Verwendung einer angegebenen Farbe
      /// für jede Ecke (hieraus werden automatisch entsprechende Farbverläufe
      /// generiert).
      /// @param left Linke Position
      /// @param top Obere Position
      /// @param right Rechte Position
      /// @param bottom Untere Position
      /// @param colorTopLeft Farbe der linken oberen Ecke
      /// @param colorTopRight Farbe der rechten oberen Ecke
      /// @param colorBottomRight Farbe der rechten unteren Ecke
      /// @param colorBottomLeft Farbe der linken unteren Ecke
      GraphicsCore& DrawRectangle (int left, int top, int right, int bottom, const Color& colorTopLeft, const Color& colorTopRight, const Color& colorBottomRight, const Color& colorBottomLeft);

      /// @brief Zeichnet ein Rechteck unter Verwendung einer Farbe.
      /// @param left Linke Position
      /// @param top Obere Position
      /// @param right Rechte Position
      /// @param bottom Untere Position
      /// @param color Farbe (wird für die gesamte Zeichenoperation verwendet)
      /// @param type Modusangabe aus GraphicsCore::DrawType
      GraphicsCore& DrawRectangle (int left, int top, int right, int bottom, const Color& color, const DrawType& type);

      /// @brief Zeichnet ein gefülltes Rechteck mit Rahmen.
      /// @param left Linke Position
      /// @param top Obere Position
      /// @param right Rechte Position
      /// @param bottom Untere Position
      /// @param outlineColor Rahmenfarbe
      /// @param fillColor Füllfarbe
      GraphicsCore& DrawBox (int left, int top, int right, int bottom, const Color& outlineColor, const Color& fillColor)
      {
         return DrawRectangle(left, top, right, bottom, fillColor, Fill).DrawRectangle(left, top, right, bottom, outlineColor, Outline);
      }


      /// @brief Zeichnet einen Pixel unter Verwendung der eingestellten
      /// Vordergrundfarbe.
      GraphicsCore& DrawPixel (int x, int y) { return DrawPixel(x, y, foreColor); }

      /// @brief Zeichnet eine Linie unter Verwendung der eingestellten
      /// Vordergrundfarbe.
      GraphicsCore& DrawLine (int left, int top, int right, int bottom) { return DrawLine(left, top, right, bottom, foreColor); }

      /// @brief Zeichnet ein gefülltes Rechteck mit Rahmen unter Verwendung der
      /// eingestellten Vorder- und Hintergrundfarbe.
      GraphicsCore& DrawBox (int left, int top, int right, int bottom) { return DrawBox(left, top, right, bottom, foreColor, backColor); }

      /// @brief Zeichnet ein Rechteck unter Verwendung der entsprechenden
      /// eingestellten Farbe.
      ///
      /// Bei DrawType::Fill wird die eingestellte Hintergrundfarbe verwendet,
      /// bei DrawType::Outline die eingestellte Vordergrundfarbe.
      /// @param left Linke Position
      /// @param top Obere Position
      /// @param right Rechte Position
      /// @param bottom Untere Position
      /// @param type Modusangabe aus GraphicsCore::DrawType
      GraphicsCore& DrawRectangle (int left, int top, int right, int bottom, const DrawType& type)
      {
         if (type == Outline) return DrawRectangle(left, top, right, bottom, foreColor, type);
         else                 return DrawRectangle(left, top, right, bottom, backColor, type);
      }


      /// @brief Gibt einen Log-Text aus (hierfür wird die System-Schriftart verwendet).
      GraphicsCore& Log (int x, int y, const std::string& text) { DrawText(x, y, text, systemFont); return *this; }

      /// @brief Gibt einen Text aus (hierfür wird die Standard-Schriftart verwendet).
      GraphicsCore& Text (int x, int y, const std::string& text) { DrawText(x, y, text, defaultFont); return *this; }

      /// @brief Gibt einen Text aus (hierfür wird eine Schriftart aus dem Schriftarten-Pool verwendet).
      /// @param x X-Position der linken oberen Ecke
      /// @param y Y-Position der linken oberen Ecke
      /// @param text Auszugebender Text
      /// @param fontId Eindeutiger Bezeichner der Schriftart im Schriftarten-Pool.
      GraphicsCore& Text (int x, int y, const std::string& text, const std::string& fontId) { DrawText(x, y, text, Font(fontId)); return *this; }


      /// @brief Erzeugt einen Screenshot. DUMMY, BITTE SINNVOLL DOKUMENTIEREN, WENNS FERTIG IST!
      GraphicsCore& ScreenShot ();


      /// @brief Zeichnet eine Texture. DUMMY, BITTE SINNVOLL DOKUMENTIEREN, WENNS FERTIG IST!
      GraphicsCore& DrawTexture (const std::string& id);


      /// @brief Liefert die Farbe, mit welcher der Grafik-Puffer "gelöscht"
      /// wird.
      const Color& ClearColor () const { return clearColor; }

      /// @brief Liefert die Farbe, welche bei Zeichenoperationen als
      /// Vordergrundfarbe/Zeichenfarbe verwendet wird.
      const Color& ForeColor () const { return foreColor; }

      /// @brief Liefert die Farbe, welche bei Zeichenoperationen als
      /// Hintergrundfarbe/Füllfarbe verwendet wird.
      const Color& BackColor () const { return backColor; }


      /// @brief Liefert den Pointer zum irrlicht-Font, welches für die
      /// System-Schriftart verwendet wird.
      irr::gui::IGUIFont* SystemFont () const  { return systemFont; }

      /// @brief Liefert den Pointer zum irrlicht-Font, welches für die
      /// Standard-Schriftart verwendet wird.
      irr::gui::IGUIFont* DefaultFont () const { return defaultFont; }

      /// @brief Liefert den Pointer zum irrlicht-Font, welches für eine
      /// Schriftart aus dem Schriftarten-Pool verwendet wird.
      /// @param id Eindeutiger Bezeichner der Schriftart im Schriftarten-Pool
      irr::gui::IGUIFont* Font (const std::string& id) const;


      /// @brief Liefert den Pointer zur irrlicht-Textur, welche für eine
      /// Textur im Texturen-Pool verwendet wird.
      /// @param id Eindeutiger Bezeichner der Textur im Texturen-Pool
      irr::video::ITexture* Texture (const std::string& id) const;


      /// @brief Ermittelt die Breite des Zeichenbereiches.
      int ScreenWidth () const;

      /// @brief Ermittelt die Höhe des Zeichenbereiches.
      int ScreenHeight () const;

      /// @brief Liefert die Dimensionen des Zeichenbereiches als Rechteck.
      const Rectangle Screen () const;


      /// @brief Ermittelt die Anzahl Frames pro Sekunde.
      int FPS () const;
   };

}

