
#include "Precomp.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "GraphicsManager.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"
#include "../Base/File.h"
#include "../Base/Tools.h"

using namespace base;


namespace ge {

   GraphicsManager::GraphicsManager (SDL_Renderer* device)
   : device(device), clearColor(0, 0, 63), foreColor(255, 255, 255), backColor(0, 0, 0), textColor(255, 255, 255), systemFont(nullptr), defaultFont(nullptr)
   {
      if (device == nullptr)    throw error::NullPointer("Invalid window device pointer!", ERROR_LOCATION);
      else if (TTF_Init() != 0) throw error::Create("Failed to initialize SDL_ttf!", ERROR_LOCATION);

      SystemFont("../resources/graphics/fonts/cour.ttf", 16);
      DefaultFont("../resources/graphics/fonts/arial.ttf", 16);
   }

   GraphicsManager::~GraphicsManager ()
   {
      RemoveAllFonts();

      if (systemFont != nullptr)  { TTF_CloseFont(systemFont); systemFont = nullptr; }
      if (defaultFont != nullptr) { TTF_CloseFont(defaultFont); defaultFont = nullptr; }

      TTF_Quit();
   }

   void GraphicsManager::LoadFont (const std::string& fontFile, int size, TTF_Font** font)
   {
      if (fontFile.empty())          throw error::InvalidParam("No font file specified!", ERROR_LOCATION);
      else if (!ExistFile(fontFile)) throw error::NotFound("Specified font file does not exist!", ERROR_LOCATION);

      if (*font != nullptr) {
         TTF_CloseFont(*font);
         *font = nullptr;
      }

      *font = TTF_OpenFont(fontFile.c_str(), size);
      if (*font == nullptr) throw error::Create("Failed to create font from file \"" + fontFile + "\"!", ERROR_LOCATION);
   }

   void GraphicsManager::RenderText (int x, int y, const std::string& text, const Color& color, TTF_Font* font)
   {
      SDL_Color sdlColor   = { color.Red(), color.Green(), color.Blue(), color.Alpha() };
      SDL_Surface* surface = nullptr;
      SDL_Texture* texture = nullptr;

      ScopeGuard guard([&surface, &texture] () {
         if (texture != nullptr) { SDL_DestroyTexture(texture); texture = nullptr; }
         if (surface != nullptr) { SDL_FreeSurface(surface); surface = nullptr; }
      });

      surface = TTF_RenderText_Blended(font, text.c_str(), sdlColor);
      if (surface == nullptr) throw error::Create("Failed to create surface!", ERROR_LOCATION);

      texture = SDL_CreateTextureFromSurface(device, surface);
      if (texture == nullptr) throw error::Create("Failed to create texture from surface!", ERROR_LOCATION);

      SDL_Rect destRect = { x, y, 0, 0 };

      SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
      SDL_RenderCopy(device, texture, nullptr, &destRect);
   }

   void GraphicsManager::RenderTexture (const std::string& id, int srcLeft, int srcTop, int srcRight, int srcBottom, int dstLeft, int dstTop, int dstRight, int dstBottom)
   {
      SDL_Rect* srcRect = nullptr;
      SDL_Rect* dstRect = nullptr;

      ScopeGuard guard([&srcRect, &dstRect] () {
         if (srcRect != nullptr) { delete srcRect; srcRect = nullptr; }
         if (dstRect != nullptr) { delete dstRect; dstRect = nullptr; }
      });

      auto texture = Texture(id);

      if (srcLeft != -1 || srcTop != -1 || srcRight != -1 || srcBottom != -1) {
         srcRect    = new SDL_Rect;
         srcRect->x = srcLeft;
         srcRect->y = srcTop;
         srcRect->w = srcRight - srcLeft;
         srcRect->h = srcBottom - srcTop;
      }

      if (dstLeft != -1 || dstTop != -1 || dstRight != -1 || dstBottom != -1) {
         dstRect    = new SDL_Rect;
         dstRect->x = dstLeft;
         dstRect->y = dstTop;

         if (dstRight != -1 || dstBottom != -1) {
            dstRect->w = dstRight - dstLeft;
            dstRect->h = dstBottom - dstTop;
         }
         else {
            SDL_QueryTexture(texture, nullptr, nullptr, &dstRect->w, &dstRect->h);
         }
      }

      SDL_RenderCopy(device, Texture(id), srcRect, dstRect);
   }

   TTF_Font* GraphicsManager::Font (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto fnt = fonts.find(id);
      if (fnt == fonts.end()) throw error::NotFound("Font with id \"" + id + "\" does not exist!", ERROR_LOCATION);

      return fnt->second;
   }

   SDL_Texture* GraphicsManager::Texture (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto tex = textures.find(id);
      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", ERROR_LOCATION);

      return tex->second;
   }

   GraphicsManager& GraphicsManager::AddFont (const std::string& id, const std::string& fontFile, int fontSize)
   {
      if (id.empty())                         throw error::InvalidParam("No id specified!", ERROR_LOCATION);
      else if (fonts.find(id) != fonts.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in font map!", ERROR_LOCATION);

      TTF_Font* font = nullptr;
      LoadFont(fontFile, fontSize, &font);

      fonts.insert(std::make_pair(id, font));
      return *this;
   }

   GraphicsManager& GraphicsManager::RemoveFont (const std::string& id)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      const auto fnt = fonts.find(id);
      if (fnt == fonts.end()) return *this;

      if (fnt->second != nullptr) TTF_CloseFont(fnt->second);
      fonts.erase(fnt);

      return *this;
   }

   GraphicsManager& GraphicsManager::RemoveAllFonts ()
   {
      for (const auto& font : fonts) {
         if (font.second != nullptr) TTF_CloseFont(font.second);
      }

      fonts.clear();
      return *this;
   }

   GraphicsManager& GraphicsManager::AddTexture (const std::string& id, const std::string& textureFile)
   {
      if (id.empty())                               throw error::InvalidParam("No id specified!", ERROR_LOCATION);
      else if (textures.find(id) != textures.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in texture map!", ERROR_LOCATION);
      else if (textureFile.empty())                 throw error::InvalidParam("No texture file specified!", ERROR_LOCATION);
      else if (!ExistFile(textureFile))             throw error::NotFound("Specified texture file does not exist!", ERROR_LOCATION);

      SDL_Surface* surface = nullptr;

      ScopeGuard guard([&surface] () {
         if (surface != nullptr) { SDL_FreeSurface(surface); surface = nullptr; }
      });

      surface = IMG_Load(textureFile.c_str());
      if (surface == nullptr) throw error::Create("Failed to create surface from file \"" + textureFile + "\"!", ERROR_LOCATION);

      auto texture = SDL_CreateTextureFromSurface(device, surface);
      if (texture == nullptr) throw error::Create("Failed to create texture from surface!", ERROR_LOCATION);

      textures.insert(std::make_pair(id, texture));
      return *this;
   }

   GraphicsManager& GraphicsManager::RemoveTexture (const std::string& id)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      const auto tex = textures.find(id);
      if (tex == textures.end()) return *this;

      if (tex->second != nullptr) SDL_DestroyTexture(tex->second);
      textures.erase(tex);

      return *this;
   }

   GraphicsManager& GraphicsManager::RemoveAllTextures ()
   {
      for (const auto& texture : textures) {
         if (texture.second != nullptr) SDL_DestroyTexture(texture.second);
      }

      textures.clear();
      return *this;
   }

   void GraphicsManager::BeginScene ()
   {
      SDL_SetRenderDrawColor(device, clearColor.Red(), clearColor.Green(), clearColor.Blue(), clearColor.Alpha());
      SDL_RenderClear(device);
   }

   void GraphicsManager::EndScene ()
   {
      SDL_RenderPresent(device);
   }

   GraphicsManager& GraphicsManager::DrawPixel (int x, int y, const Color& color)
   {
      SDL_SetRenderDrawColor(device, color.Red(), color.Green(), color.Blue(), color.Alpha());
      SDL_RenderDrawPoint(device, x, y);

      return *this;
   }

   GraphicsManager& GraphicsManager::DrawLine (int left, int top, int right, int bottom, const Color& color)
   {
      SDL_SetRenderDrawColor(device, color.Red(), color.Green(), color.Blue(), color.Alpha());
      SDL_RenderDrawLine(device, left, top, right, bottom);

      return *this;
   }

   GraphicsManager& GraphicsManager::DrawRectangle (int left, int top, int right, int bottom, const Color& color)
   {
      SDL_Rect rect;
      rect.x = left;
      rect.y = top;
      rect.w = right - left;
      rect.h = bottom - top;

      SDL_SetRenderDrawColor(device, color.Red(), color.Green(), color.Blue(), color.Alpha());
      SDL_RenderDrawRect(device, &rect);

      return *this;
   }

   GraphicsManager& GraphicsManager::FillRectangle (int left, int top, int right, int bottom, const Color& color)
   {
      SDL_Rect rect;
      rect.x = left;
      rect.y = top;
      rect.w = right - left;
      rect.h = bottom - top;

      SDL_SetRenderDrawColor(device, color.Red(), color.Green(), color.Blue(), color.Alpha());
      SDL_RenderFillRect(device, &rect);

      return *this;
   }

}

