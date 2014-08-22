
#pragma once

#include "Color.h"
#include "Rectangle.h"

#include "DLL_DEF.h"

struct SDL_Renderer;
struct _TTF_Font; // TTF_Font cannot be forwarded directly due to a name clash issue


namespace ge {

   class GEDLL GraphicsManager
   {
   public:
      enum DrawType {
         Fill = 0,
         Outline
      };

   private:
      SDL_Renderer* device;

      Color clearColor;
      Color foreColor;
      Color backColor;

      _TTF_Font* systemFont;
      _TTF_Font* defaultFont;

      std::map<std::string, _TTF_Font*> fonts;

//      std::map<std::string, sf::Texture> textures;

      void LoadFont (const std::string& fontFile, int size, _TTF_Font** font);
      void Text (int x, int y, const std::string& text, const Color& color, _TTF_Font* font);

      _TTF_Font* Font (const std::string& id) const;

   public:
      GraphicsManager (SDL_Renderer* device);
      virtual ~GraphicsManager ();

      GraphicsManager& ClearColor (const Color& color) { clearColor = color; return *this; }
      GraphicsManager& ForeColor (const Color& color)  { foreColor = color; return *this; }
      GraphicsManager& BackColor (const Color& color)  { backColor = color; return *this; }

      GraphicsManager& SystemFont (const std::string& fontFile, int fontSize)  { LoadFont(fontFile, fontSize, &systemFont); return *this; }
      GraphicsManager& DefaultFont (const std::string& fontFile, int fontSize) { LoadFont(fontFile, fontSize, &defaultFont); return *this; }
      GraphicsManager& AddFont (const std::string& id, const std::string& fontFile, int fontSize);
      GraphicsManager& AddFont (const std::string& id, const Binary& resource, int fontSize);
      GraphicsManager& RemoveFont (const std::string& id);
      GraphicsManager& RemoveAllFonts ();

      GraphicsManager& AddTexture (const std::string& id, const std::string& textureFile);
      GraphicsManager& AddTexture (const std::string& id, const Binary& resource);
      GraphicsManager& RemoveTexture (const std::string& id);
//      GraphicsManager& RemoveAllTextures () { textures.clear(); return *this; }

      void BeginScene ();
      void EndScene ();

//      GraphicsManager& DrawPixel (int x, int y, const Color& color);
//      GraphicsManager& DrawPixel (const Point& pos, const Color& color) { return DrawPixel(pos.X(), pos.Y(), color); }
//      GraphicsManager& DrawPixel (int x, int y)                         { return DrawPixel(x, y, foreColor); }
//      GraphicsManager& DrawPixel (const Point& pos)                     { return DrawPixel(pos.X(), pos.Y(), foreColor); }

//      GraphicsManager& DrawLine (int left, int top, int right, int bottom, const Color& color);
//      GraphicsManager& DrawLine (const Point& topLeft, const Point& bottomRight, const Color& color) { return DrawLine(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), color); }
//      GraphicsManager& DrawLine (int left, int top, int right, int bottom)                           { return DrawLine(left, top, right, bottom, foreColor); }
//      GraphicsManager& DrawLine (const Point& topLeft, const Point& bottomRight)                     { return DrawLine(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), foreColor); }

//      GraphicsManager& DrawRectangle (int left, int top, int right, int bottom, const Color& colorTopLeft, const Color& colorTopRight, const Color& colorBottomLeft, const Color& colorBottomRight);
//      GraphicsManager& DrawRectangle (const Point& topLeft, const Point& bottomRight, const Color& colorTopLeft, const Color& colorTopRight, const Color& colorBottomLeft, const Color& colorBottomRight) { return DrawRectangle(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), colorTopLeft, colorTopRight, colorBottomLeft, colorBottomRight); }
//      GraphicsManager& DrawRectangle (const Rectangle& rect, const Color& colorTopLeft, const Color& colorTopRight, const Color& colorBottomLeft, const Color& colorBottomRight)                          { return DrawRectangle(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), colorTopLeft, colorTopRight, colorBottomLeft, colorBottomRight); }

//      GraphicsManager& DrawRectangle (int left, int top, int right, int bottom, const Color& color, const DrawType& type);
//      GraphicsManager& DrawRectangle (const Point& topLeft, const Point& bottomRight, const Color& color, const DrawType& type) { return DrawRectangle(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), color, type); }
//      GraphicsManager& DrawRectangle (const Rectangle& rect, const Color& color, const DrawType& type)                          { return DrawRectangle(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), color, type); }

//      GraphicsManager& DrawBox (int left, int top, int right, int bottom, const Color& outlineColor, const Color& fillColor)       { return DrawRectangle(left, top, right, bottom, fillColor, Fill).DrawRectangle(left, top, right, bottom, outlineColor, Outline); }
//      GraphicsManager& DrawBox (const Point& topLeft, const Point& bottomRight, const Color& outlineColor, const Color& fillColor) { return DrawBox(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), outlineColor, fillColor); }
//      GraphicsManager& DrawBox (const Rectangle& rect, const Color& outlineColor, const Color& fillColor)                          { return DrawBox(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), outlineColor, fillColor); }

//      GraphicsManager& DrawRectangle (int left, int top, int right, int bottom, const DrawType& type)
//      {
//         if (type == Outline) return DrawRectangle(left, top, right, bottom, foreColor, type);
//         else                 return DrawRectangle(left, top, right, bottom, backColor, type);
//      }

//      GraphicsManager& DrawRectangle (const Point& topLeft, const Point& bottomRight, const DrawType& type) { return DrawRectangle(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), type); }
//      GraphicsManager& DrawRectangle (const Rectangle& rect, const DrawType& type)                          { return DrawRectangle(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), type); }

//      GraphicsManager& DrawBox (int left, int top, int right, int bottom)       { return DrawBox(left, top, right, bottom, foreColor, backColor); }
//      GraphicsManager& DrawBox (const Point& topLeft, const Point& bottomRight) { return DrawBox(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), foreColor, backColor); }
//      GraphicsManager& DrawBox (const Rectangle& rect)                          { return DrawBox(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), foreColor, backColor); }

      GraphicsManager& DrawTexture (const std::string& id, const Point<float>& pos);
      GraphicsManager& DrawTexture (const std::string& id, const Rectangle<float>& rect);
//      GraphicsManager& DrawTexture (const std::string& id, const Rectangle& srcRect, const Point& dstPos);
//      GraphicsManager& DrawTexture (const std::string& id, const Rectangle& srcRect, const Rectangle& dstRect);

      GraphicsManager& Log (int x, int y, const std::string& text)                                                 { Text(x, y, text, foreColor, systemFont); return *this; }
      GraphicsManager& Log (int x, int y, const std::string& text, const Color& color)                             { Text(x, y, text, color, systemFont); return *this; }
      GraphicsManager& Text (int x, int y, const std::string& text)                                                { Text(x, y, text, foreColor, defaultFont); return *this; }
      GraphicsManager& Text (int x, int y, const std::string& text, const Color& color)                            { Text(x, y, text, color, defaultFont); return *this; }
      GraphicsManager& Text (int x, int y, const std::string& text, const std::string& fontId)                     { Text(x, y, text, foreColor, Font(fontId)); return *this; }
      GraphicsManager& Text (int x, int y, const std::string& text, const Color& color, const std::string& fontId) { Text(x, y, text, color, Font(fontId)); return *this; }

      const Color& ClearColor () const { return clearColor; }
      const Color& ForeColor () const  { return foreColor; }
      const Color& BackColor () const  { return backColor; }

//      const sf::Texture& Texture (const std::string& id) const;

//      int ScreenWidth () const;
//      int ScreenHeight () const;
//      const Rectangle Screen () const;

//      int FPS () const;

//      sf::Image ScreenShot () const { return device->capture(); }
   };

}

