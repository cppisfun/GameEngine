
#pragma once

#include <irrlicht.h>

#include "Color.h"
#include "Rectangle.h"

#include "DLL_DEF.h"


namespace ge {

   class GEDLL GraphicsCore
   {
   public:
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
      GraphicsCore (irr::IrrlichtDevice* device);
      virtual ~GraphicsCore ();

      GraphicsCore& ClearColor (const Color& color) { clearColor = color; return *this; }
      GraphicsCore& ForeColor (const Color& color)  { foreColor = color; return *this; }
      GraphicsCore& BackColor (const Color& color)  { backColor = color; return *this; }

      GraphicsCore& SystemFont (const std::string& fontFile);
      GraphicsCore& DefaultFont (const std::string& fontFile);

      GraphicsCore& AddFont (const std::string& id, const std::string& fontFile);
      GraphicsCore& RemoveFont (const std::string& id);
      GraphicsCore& RemoveAllFonts ();

      GraphicsCore& AddTexture (const std::string& id, const std::string& textureFile);
      GraphicsCore& AddTexture (const std::string& id, const std::vector<char>& resource);
      GraphicsCore& RemoveTexture (const std::string& id);
      GraphicsCore& RemoveAllTextures ();

      void BeginScene ();
      void EndScene ();

      GraphicsCore& DrawPixel (int x, int y, const Color& color);
      GraphicsCore& DrawLine (int left, int top, int right, int bottom, const Color& color);
      GraphicsCore& DrawRectangle (int left, int top, int right, int bottom, const Color& colorTopLeft, const Color& colorTopRight, const Color& colorBottomRight, const Color& colorBottomLeft, const DrawType& type);
      GraphicsCore& DrawRectangle (int left, int top, int right, int bottom, const Color& color, const DrawType& type);

      GraphicsCore& DrawBox (int left, int top, int right, int bottom, const Color& outlineColor, const Color& fillColor)
      {
         return DrawRectangle(left, top, right, bottom, fillColor, Fill).DrawRectangle(left, top, right, bottom, outlineColor, Outline);
      }

      GraphicsCore& DrawPixel (int x, int y)                            { return DrawPixel(x, y, foreColor); }
      GraphicsCore& DrawLine (int left, int top, int right, int bottom) { return DrawLine(left, top, right, bottom, foreColor); }
      GraphicsCore& DrawBox (int left, int top, int right, int bottom)  { return DrawBox(left, top, right, bottom, foreColor, backColor); }

      GraphicsCore& DrawRectangle (int left, int top, int right, int bottom, const DrawType& type)
      {
         if (type == Outline) return DrawRectangle(left, top, right, bottom, foreColor, type);
         else                 return DrawRectangle(left, top, right, bottom, backColor, type);
      }

      GraphicsCore& Log (int x, int y, const std::string& text)                             { DrawText(x, y, text, systemFont); return *this; }
      GraphicsCore& Text (int x, int y, const std::string& text)                            { DrawText(x, y, text, defaultFont); return *this; }
      GraphicsCore& Text (int x, int y, const std::string& text, const std::string& fontId) { DrawText(x, y, text, Font(fontId)); return *this; }

      GraphicsCore& ScreenShot ();


      const Color& ClearColor () const { return clearColor; }
      const Color& ForeColor () const  { return foreColor; }
      const Color& BackColor () const  { return backColor; }

      irr::gui::IGUIFont* SystemFont () const  { return systemFont; }
      irr::gui::IGUIFont* DefaultFont () const { return defaultFont; }
      irr::gui::IGUIFont* Font (const std::string& id) const;
      irr::video::ITexture* Texture (const std::string& id) const;

      int ScreenWidth () const;
      int ScreenHeight () const;
      const Rectangle& Screen () const;

      int FPS () const;
   };

}

