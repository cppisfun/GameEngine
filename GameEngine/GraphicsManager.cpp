
#include "Precomp.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "GraphicsManager.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"
#include "../Base/File.h"
#include "../Base/Tools.h"

using namespace base;


namespace ge {

   GraphicsManager::GraphicsManager (SDL_Renderer* device)
   : device(device), clearColor(0, 0, 63), foreColor(255, 255, 255), backColor(0, 0, 0), systemFont(nullptr), defaultFont(nullptr)
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

   void GraphicsManager::Text (int x, int y, const std::string& text, const Color& color, TTF_Font* font)
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

   _TTF_Font* GraphicsManager::Font (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

      auto fnt = fonts.find(id);
      if (fnt == fonts.end()) throw error::NotFound("Font with id \"" + id + "\" does not exist!", ERROR_LOCATION);

      return fnt->second;
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
      else if (textureFile.empty())                 throw error::InvalidParam("No texture file specified!", ERROR_LOCATION);
//      else if (textures.find(id) != textures.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in texture map!", ERROR_LOCATION);
//
//      sf::Texture tex;
//      if (!tex.loadFromFile(textureFile)) throw error::Create("Failed to create texture from file \"" + textureFile + "\"!", ERROR_LOCATION);
//
//      textures.insert(std::make_pair(id, tex));
      return *this;
   }

   GraphicsManager& GraphicsManager::AddTexture (const std::string& id, const Binary& resource)
   {
      if (id.empty())                               throw error::InvalidParam("No id specified!", ERROR_LOCATION);
      else if (resource.empty())                    throw error::InvalidParam("Texture resource is empty!", ERROR_LOCATION);
//      else if (textures.find(id) != textures.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in texture map!", ERROR_LOCATION);
//
//      sf::Texture tex;
//      if (!tex.loadFromMemory(resource.data(), resource.size())) throw error::Create("Failed to create texture from resource!", ERROR_LOCATION);
//
//      textures.insert(std::make_pair(id, tex));
      return *this;
   }

   GraphicsManager& GraphicsManager::RemoveTexture (const std::string& id)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

//      auto tex = textures.find(id);
//      if (tex != textures.end()) textures.erase(tex);

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

// FIXME: GE-42
//   GraphicsManager& GraphicsManager::DrawPixel (int x, int y, const Color& color)
//   {
//      driver->drawPixel(x, y, color.AsIrrColor());
//      return *this;
//   }

// FIXME: GE-42
//   GraphicsManager& GraphicsManager::DrawLine (int left, int top, int right, int bottom, const Color& color)
//   {
//      driver->draw2DLine(core::vector2d<int>(left, top), core::vector2d<int>(right, bottom), color.AsIrrColor());
//      return *this;
//   }

// FIXME: GE-42
//   GraphicsManager& GraphicsManager::DrawRectangle (int left, int top, int right, int bottom, const Color& colorTopLeft, const Color& colorTopRight, const Color& colorBottomLeft, const Color& colorBottomRight)
//   {
//      driver->draw2DRectangle(core::rect<int>(left, top, right, bottom), colorTopLeft.AsIrrColor(), colorTopRight.AsIrrColor(), colorBottomLeft.AsIrrColor(), colorBottomRight.AsIrrColor());
//      return *this;
//   }

// FIXME: GE-42
//   GraphicsManager& GraphicsManager::DrawRectangle (int left, int top, int right, int bottom, const Color& color, const DrawType& type)
//   {
//      if (type == Outline) driver->draw2DRectangleOutline(core::rect<int>(left, top, right, bottom), color.AsIrrColor());
//      else                 driver->draw2DRectangle(color.AsIrrColor(), core::rect<int>(left, top, right, bottom));
//
//      return *this;
//   }

   GraphicsManager& GraphicsManager::DrawTexture (const std::string& id, const Point<float>& pos)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

//      auto tex = textures.find(id);
//      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", ERROR_LOCATION);
//
//      sf::Sprite spr(tex->second);
//      spr.setPosition(pos.AsSFMLVector());
//
//      device->draw(spr);
      return *this;
   }

   GraphicsManager& GraphicsManager::DrawTexture (const std::string& id, const Rectangle<float>& rect)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);

//      auto tex = textures.find(id);
//      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", ERROR_LOCATION);
//
//      const auto texSize = tex->second.getSize();
//
//      sf::Sprite spr(tex->second);
//      spr.setPosition(rect.Left(), rect.Top());
//      spr.setScale(rect.Width() / texSize.x, rect.Height() / texSize.y);
//
//      device->draw(spr);
      return *this;
   }

// FIXME: GE-42
//   GraphicsManager& GraphicsManager::DrawTexture (const std::string& id, const Rectangle& srcRect, const Point& dstPos)
//   {
//      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);
//
//      auto tex = textures.find(id);
//      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", ERROR_LOCATION);
//
//      driver->draw2DImage(tex->second, dstPos.AsIrrVector(), srcRect.AsIrrRect());
//      return *this;
//   }

// FIXME: GE-42
//   GraphicsManager& GraphicsManager::DrawTexture (const std::string& id, const Rectangle& srcRect, const Rectangle& dstRect)
//   {
//      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);
//
//      auto tex = textures.find(id);
//      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", ERROR_LOCATION);
//
//      driver->draw2DImage(tex->second, dstRect.AsIrrRect(), srcRect.AsIrrRect());
//      return *this;
//   }

//   const sf::Texture& GraphicsManager::Texture (const std::string& id) const
//   {
//      if (id.empty()) throw error::InvalidParam("No id specified!", ERROR_LOCATION);
//
//      auto tex = textures.find(id);
//      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", ERROR_LOCATION);
//
//      return tex->second;
//   }

// FIXME: GE-42
//   int GraphicsManager::ScreenWidth () const
//   {
//      return driver->getScreenSize().Width;
//   }

// FIXME: GE-42
//   int GraphicsManager::ScreenHeight () const
//   {
//      return driver->getScreenSize().Height;
//   }

// FIXME: GE-42
//   const Rectangle GraphicsManager::Screen () const
//   {
//      auto dims = driver->getScreenSize();
//
//      int right = dims.Width - 1;
//      if (right < 0) right = 0;
//
//      int bottom = dims.Height - 1;
//      if (bottom < 0) bottom = 0;
//
//      return Rectangle(0, 0, right, bottom);
//   }

// FIXME: GE-42
//   int GraphicsManager::FPS () const
//   {
//      return driver->getFPS();
//   }

}

