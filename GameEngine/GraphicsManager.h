
#pragma once

#include "Color.h"
#include "Position.h"
#include "Box.h"

#include "DLL_DEF.h"

struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Texture;
struct _TTF_Font; // TTF_Font cannot be forwarded directly due to a name clash issue


namespace ge {

   class GEDLL GraphicsManager
   {
      SDL_Renderer* device;

      Color clearColor;
      Color foreColor;
      Color backColor;
      Color textColor;

      _TTF_Font* systemFont;
      _TTF_Font* defaultFont;

      std::map<std::string, _TTF_Font*>   fonts;
      std::map<std::string, SDL_Texture*> textures;

      void LoadFont (const std::string& fontFile, int size, _TTF_Font** font);
      void RenderText (int x, int y, const std::string& text, const Color& color, _TTF_Font* font);
      void RenderTexture (const std::string& id, int srcLeft, int srcTop, int srcRight, int srcBottom, int dstLeft, int dstTop, int dstRight, int dstBottom);

      _TTF_Font* Font (const std::string& id) const;
      SDL_Texture* Texture (const std::string& id) const;

   public:
      GraphicsManager (SDL_Renderer* device);
      virtual ~GraphicsManager ();

      GraphicsManager& ClearColor (const Color& color) { clearColor = color; return *this; }
      GraphicsManager& ForeColor (const Color& color)  { foreColor = color; return *this; }
      GraphicsManager& BackColor (const Color& color)  { backColor = color; return *this; }
      GraphicsManager& TextColor (const Color& color)  { textColor = color; return *this; }

      GraphicsManager& SystemFont (const std::string& fontFile, int fontSize)  { LoadFont(fontFile, fontSize, &systemFont); return *this; }
      GraphicsManager& DefaultFont (const std::string& fontFile, int fontSize) { LoadFont(fontFile, fontSize, &defaultFont); return *this; }
      GraphicsManager& AddFont (const std::string& id, const std::string& fontFile, int fontSize);
      GraphicsManager& RemoveFont (const std::string& id);
      GraphicsManager& RemoveAllFonts ();

      GraphicsManager& AddTexture (const std::string& id, const std::string& textureFile);
      GraphicsManager& RemoveTexture (const std::string& id);
      GraphicsManager& RemoveAllTextures ();

      void BeginScene ();
      void EndScene ();

      GraphicsManager& DrawPixel (int x, int y, const Color& color);
      GraphicsManager& DrawPixel (const Position& pos, const Color& color) { return DrawPixel(pos.X(), pos.Y(), color); }
      GraphicsManager& DrawPixel (int x, int y)                            { return DrawPixel(x, y, foreColor); }
      GraphicsManager& DrawPixel (const Position& pos)                     { return DrawPixel(pos.X(), pos.Y(), foreColor); }

      GraphicsManager& DrawLine (int left, int top, int right, int bottom, const Color& color);
      GraphicsManager& DrawLine (const Position& topLeft, const Position& bottomRight, const Color& color) { return DrawLine(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), color); }
      GraphicsManager& DrawLine (const Box& rect, const Color& color)                                      { return DrawLine(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), color); }
      GraphicsManager& DrawLine (int left, int top, int right, int bottom)                                 { return DrawLine(left, top, right, bottom, foreColor); }
      GraphicsManager& DrawLine (const Position& topLeft, const Position& bottomRight)                     { return DrawLine(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), foreColor); }
      GraphicsManager& DrawLine (const Box& rect)                                                          { return DrawLine(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), foreColor); }

      GraphicsManager& DrawRectangle (int left, int top, int right, int bottom, const Color& color);
      GraphicsManager& DrawRectangle (const Position& topLeft, const Position& bottomRight, const Color& color) { return DrawRectangle(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), color); }
      GraphicsManager& DrawRectangle (const Box& rect, const Color& color)                                      { return DrawRectangle(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), color); }
      GraphicsManager& DrawRectangle (int left, int top, int right, int bottom)                                 { return DrawRectangle(left, top, right, bottom, foreColor); }
      GraphicsManager& DrawRectangle (const Position& topLeft, const Position& bottomRight)                     { return DrawRectangle(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), foreColor); }
      GraphicsManager& DrawRectangle (const Box& rect)                                                          { return DrawRectangle(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), foreColor); }

      GraphicsManager& FillRectangle (int left, int top, int right, int bottom, const Color& color);
      GraphicsManager& FillRectangle (const Position& topLeft, const Position& bottomRight, const Color& color) { return FillRectangle(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), color); }
      GraphicsManager& FillRectangle (const Box& rect, const Color& color)                                      { return FillRectangle(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), color); }
      GraphicsManager& FillRectangle (int left, int top, int right, int bottom)                                 { return FillRectangle(left, top, right, bottom, backColor); }
      GraphicsManager& FillRectangle (const Position& topLeft, const Position& bottomRight)                     { return FillRectangle(topLeft.X(), topLeft.Y(), bottomRight.X(), bottomRight.Y(), backColor); }
      GraphicsManager& FillRectangle (const Box& rect)                                                          { return FillRectangle(rect.Left(), rect.Top(), rect.Right(), rect.Bottom(), backColor); }

      GraphicsManager& DrawTexture (const std::string& id, const Position& dstPos)                     { RenderTexture(id, -1, -1, -1, -1, dstPos.X(), dstPos.Y(), -1, -1); return *this; }
      GraphicsManager& DrawTexture (const std::string& id, const Box& dstRect)                         { RenderTexture(id, -1, -1, -1, -1, dstRect.Left(), dstRect.Top(), dstRect.Right(), dstRect.Bottom()); return *this; }
      GraphicsManager& DrawTexture (const std::string& id, const Box& srcRect, const Position& dstPos) { RenderTexture(id, srcRect.Left(), srcRect.Top(), srcRect.Right(), srcRect.Bottom(), dstPos.X(), dstPos.Y(), -1, -1); return *this; }
      GraphicsManager& DrawTexture (const std::string& id, const Box& srcRect, const Box& dstRect)     { RenderTexture(id, srcRect.Left(), srcRect.Top(), srcRect.Right(), srcRect.Bottom(), dstRect.Left(), dstRect.Top(), dstRect.Right(), dstRect.Bottom()); return *this; }

      GraphicsManager& Log (int x, int y, const std::string& text)                                                 { RenderText(x, y, text, textColor, systemFont); return *this; }
      GraphicsManager& Log (int x, int y, const std::string& text, const Color& color)                             { RenderText(x, y, text, color, systemFont); return *this; }
      GraphicsManager& Text (int x, int y, const std::string& text)                                                { RenderText(x, y, text, textColor, defaultFont); return *this; }
      GraphicsManager& Text (int x, int y, const std::string& text, const Color& color)                            { RenderText(x, y, text, color, defaultFont); return *this; }
      GraphicsManager& Text (int x, int y, const std::string& text, const std::string& fontId)                     { RenderText(x, y, text, textColor, Font(fontId)); return *this; }
      GraphicsManager& Text (int x, int y, const std::string& text, const Color& color, const std::string& fontId) { RenderText(x, y, text, color, Font(fontId)); return *this; }

      const Color& ClearColor () const { return clearColor; }
      const Color& ForeColor () const  { return foreColor; }
      const Color& BackColor () const  { return backColor; }
      const Color& TextColor () const  { return textColor; }
   };

}

