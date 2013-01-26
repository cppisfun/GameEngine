
#include "Precomp.h"

#include "GraphicsCore.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"

using namespace ge;


namespace ge {

   GraphicsCore::GraphicsCore (sf::RenderWindow* device)
   : device(device), clearColor(0, 0, 63), foreColor(255, 255, 255), backColor(0, 0, 0)
   {
      if (device == nullptr) throw error::NullPointer("Invalid window device pointer!", __FUNCTION__);

      SystemFont("../resources/graphics/fonts/cour.ttf");
      DefaultFont("../resources/graphics/fonts/arial.ttf");
   }

   GraphicsCore::~GraphicsCore ()
   {
   }

   void GraphicsCore::DrawText (float x, float y, const std::string& text, const sf::Font& font, int fontSizeInPixels)
   {
      sf::Text txt(text, font, (fontSizeInPixels > 0) ? fontSizeInPixels : 0);
      txt.setPosition(x, y);

      device->draw(txt);
   }

   GraphicsCore& GraphicsCore::SystemFont (const std::string& fontFile)
   {
      if (fontFile.empty()) throw error::InvalidParam("No font file specified!", __FUNCTION__);
      else if (!systemFont.loadFromFile(fontFile)) throw error::Read("Failed to read from font file \"" + fontFile + "\"!", __FUNCTION__);

      return *this;
   }

   GraphicsCore& GraphicsCore::DefaultFont (const std::string& fontFile)
   {
      if (fontFile.empty()) throw error::InvalidParam("No font file specified!", __FUNCTION__);
      else if (!defaultFont.loadFromFile(fontFile)) throw error::Read("Failed to read from font file \"" + fontFile + "\"!", __FUNCTION__);

      return *this;
   }

   GraphicsCore& GraphicsCore::AddFont (const std::string& id, const std::string& fontFile)
   {
      if (id.empty())                         throw error::InvalidParam("No id specified!", __FUNCTION__);
      else if (fontFile.empty())              throw error::InvalidParam("No font file specified!", __FUNCTION__);
      else if (fonts.find(id) != fonts.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in font map!", __FUNCTION__);

      sf::Font fnt;
      if (!fnt.loadFromFile(fontFile)) throw error::Create("Failed to create font from file \"" + fontFile + "\"!", __FUNCTION__);

      fonts.insert(std::make_pair(id, fnt));
      return *this;
   }

   GraphicsCore& GraphicsCore::AddFont (const std::string& id, const std::vector<char>& resource)
   {
      if (id.empty())                         throw error::InvalidParam("No id specified!", __FUNCTION__);
      else if (resource.empty())              throw error::InvalidParam("Font resource is empty!", __FUNCTION__);
      else if (fonts.find(id) != fonts.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in font map!", __FUNCTION__);

      sf::Font fnt;
      if (!fnt.loadFromMemory(resource.data(), resource.size())) throw error::Read("Failed to create font from resource!", __FUNCTION__);

      fonts.insert(std::make_pair(id, fnt));
      return *this;
   }

   GraphicsCore& GraphicsCore::RemoveFont (const std::string& id)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      const auto fnt = fonts.find(id);
      if (fnt != fonts.end()) fonts.erase(fnt);

      return *this;
   }

   GraphicsCore& GraphicsCore::AddTexture (const std::string& id, const std::string& textureFile)
   {
      if (id.empty())                               throw error::InvalidParam("No id specified!", __FUNCTION__);
      else if (textureFile.empty())                 throw error::InvalidParam("No texture file specified!", __FUNCTION__);
      else if (textures.find(id) != textures.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in texture map!", __FUNCTION__);

      sf::Texture tex;
      if (!tex.loadFromFile(textureFile)) throw error::Create("Failed to create texture from file \"" + textureFile + "\"!", __FUNCTION__);

      textures.insert(std::make_pair(id, tex));
      return *this;
   }

   GraphicsCore& GraphicsCore::AddTexture (const std::string& id, const std::vector<char>& resource)
   {
      if (id.empty())                               throw error::InvalidParam("No id specified!", __FUNCTION__);
      else if (resource.empty())                    throw error::InvalidParam("Texture resource is empty!", __FUNCTION__);
      else if (textures.find(id) != textures.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in texture map!", __FUNCTION__);

      sf::Texture tex;
      if (!tex.loadFromMemory(resource.data(), resource.size())) throw error::Create("Failed to create texture from resource!", __FUNCTION__);

      textures.insert(std::make_pair(id, tex));
      return *this;
   }

   GraphicsCore& GraphicsCore::RemoveTexture (const std::string& id)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      auto tex = textures.find(id);
      if (tex != textures.end()) textures.erase(tex);

      return *this;
   }

   void GraphicsCore::BeginScene ()
   {
      device->clear(clearColor.AsSFMLColor());
   }

   void GraphicsCore::EndScene ()
   {
      device->display();
   }

// FIXME: GE-42
//   GraphicsCore& GraphicsCore::DrawPixel (int x, int y, const Color& color)
//   {
//      driver->drawPixel(x, y, color.AsIrrColor());
//      return *this;
//   }

// FIXME: GE-42
//   GraphicsCore& GraphicsCore::DrawLine (int left, int top, int right, int bottom, const Color& color)
//   {
//      driver->draw2DLine(core::vector2d<int>(left, top), core::vector2d<int>(right, bottom), color.AsIrrColor());
//      return *this;
//   }

// FIXME: GE-42
//   GraphicsCore& GraphicsCore::DrawRectangle (int left, int top, int right, int bottom, const Color& colorTopLeft, const Color& colorTopRight, const Color& colorBottomLeft, const Color& colorBottomRight)
//   {
//      driver->draw2DRectangle(core::rect<int>(left, top, right, bottom), colorTopLeft.AsIrrColor(), colorTopRight.AsIrrColor(), colorBottomLeft.AsIrrColor(), colorBottomRight.AsIrrColor());
//      return *this;
//   }

// FIXME: GE-42
//   GraphicsCore& GraphicsCore::DrawRectangle (int left, int top, int right, int bottom, const Color& color, const DrawType& type)
//   {
//      if (type == Outline) driver->draw2DRectangleOutline(core::rect<int>(left, top, right, bottom), color.AsIrrColor());
//      else                 driver->draw2DRectangle(color.AsIrrColor(), core::rect<int>(left, top, right, bottom));
//
//      return *this;
//   }

   GraphicsCore& GraphicsCore::DrawTexture (const std::string& id, const Point<float>& pos)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      auto tex = textures.find(id);
      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", __FUNCTION__);

      sf::Sprite spr(tex->second);
      spr.setPosition(pos.AsSFMLVector());

      device->draw(spr);
      return *this;
   }

   GraphicsCore& GraphicsCore::DrawTexture (const std::string& id, const Rectangle<float>& rect)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      auto tex = textures.find(id);
      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", __FUNCTION__);

      const auto texSize = tex->second.getSize();

      sf::Sprite spr(tex->second);
      spr.setPosition(rect.Left(), rect.Top());
      spr.setScale(rect.Width() / texSize.x, rect.Height() / texSize.y);

      device->draw(spr);
      return *this;
   }

// FIXME: GE-42
//   GraphicsCore& GraphicsCore::DrawTexture (const std::string& id, const Rectangle& srcRect, const Point& dstPos)
//   {
//      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);
//
//      auto tex = textures.find(id);
//      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", __FUNCTION__);
//
//      driver->draw2DImage(tex->second, dstPos.AsIrrVector(), srcRect.AsIrrRect());
//      return *this;
//   }

// FIXME: GE-42
//   GraphicsCore& GraphicsCore::DrawTexture (const std::string& id, const Rectangle& srcRect, const Rectangle& dstRect)
//   {
//      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);
//
//      auto tex = textures.find(id);
//      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", __FUNCTION__);
//
//      driver->draw2DImage(tex->second, dstRect.AsIrrRect(), srcRect.AsIrrRect());
//      return *this;
//   }

   const sf::Font& GraphicsCore::Font (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      auto fnt = fonts.find(id);
      if (fnt == fonts.end()) throw error::NotFound("Font with id \"" + id + "\" does not exist!", __FUNCTION__);

      return fnt->second;
   }

   const sf::Texture& GraphicsCore::Texture (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      auto tex = textures.find(id);
      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", __FUNCTION__);

      return tex->second;
   }

// FIXME: GE-42
//   int GraphicsCore::ScreenWidth () const
//   {
//      return driver->getScreenSize().Width;
//   }

// FIXME: GE-42
//   int GraphicsCore::ScreenHeight () const
//   {
//      return driver->getScreenSize().Height;
//   }

// FIXME: GE-42
//   const Rectangle GraphicsCore::Screen () const
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
//   int GraphicsCore::FPS () const
//   {
//      return driver->getFPS();
//   }

}

