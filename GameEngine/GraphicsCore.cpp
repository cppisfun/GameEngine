
#include "Precomp.h"

#include "GraphicsCore.h"

#include "../Base/Convert.h"
#include "../Base/Error.h"

using namespace ge;
using namespace irr;


namespace ge {

   GraphicsCore::GraphicsCore (IrrlichtDevice* device)
   : clearColor(0, 0, 63), foreColor(255, 255, 255), backColor(0, 0, 0), driver(nullptr), gui(nullptr)
   {
      Init(device);
   }

   GraphicsCore::~GraphicsCore ()
   {
      // Irrlicht handles font resources by itself - deleting or using drop() on them WILL CRASH the program!

      std::for_each(textures.begin(), textures.end(), [] (const std::pair<std::string, irr::video::ITexture*> tex) {
         tex.second->drop();
      });
   }

   void GraphicsCore::Init (IrrlichtDevice* device)
   {
      if (device == nullptr) throw error::NullPointer("Invalid Irrlicht device pointer!", __FUNCTION__);

      driver = device->getVideoDriver();
      if (driver == nullptr) throw error::Query("Failed to query Irrlicht video driver!", __FUNCTION__);

      gui = device->getGUIEnvironment();
      if (gui == nullptr) throw error::Query("Failed to query Irrlicht gui environment!", __FUNCTION__);

      SystemFont("../resources/graphics/fonts/fntSystem.xml");
      DefaultFont("../resources/graphics/fonts/fntDefault.xml");
   }

   void GraphicsCore::DrawText (int x, int y, const std::string& text, irr::gui::IGUIFont* font)   // TODO
   {
      auto fnt = (font != nullptr) ? font : gui->getBuiltInFont();
      fnt->draw(base::AsWString(text).c_str(), core::rect<int>(x, y, x + 100, y + 100), foreColor.AsIrrColor());
   }

   GraphicsCore& GraphicsCore::SystemFont (const std::string& fontFile)
   {
      if (fontFile.empty()) throw error::InvalidParam("No font file specified!", __FUNCTION__);

      systemFont = gui->getFont(fontFile.c_str());
      if (systemFont == nullptr) systemFont = gui->getBuiltInFont();

      return *this;
   }

   GraphicsCore& GraphicsCore::DefaultFont (const std::string& fontFile)
   {
      if (fontFile.empty()) throw error::InvalidParam("No font file specified!", __FUNCTION__);

      defaultFont = gui->getFont(fontFile.c_str());
      if (defaultFont == nullptr) defaultFont = gui->getBuiltInFont();

      return *this;
   }

   GraphicsCore& GraphicsCore::AddFont (const std::string& id, const std::string& fontFile)
   {
      if (id.empty())                         throw error::InvalidParam("No id specified!", __FUNCTION__);
      else if (fontFile.empty())              throw error::InvalidParam("No font file specified!", __FUNCTION__);
      else if (fonts.find(id) != fonts.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in map!", __FUNCTION__);

      auto fnt = gui->getFont(fontFile.c_str());
      if (fnt == nullptr) fnt = gui->getBuiltInFont();

      fonts.insert(std::make_pair(id, fnt));
      return *this;
   }

   GraphicsCore& GraphicsCore::RemoveFont (const std::string& id)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      const auto fnt = fonts.find(id);
      if (fnt == fonts.end()) return *this;

      fnt->second->drop();
      fonts.erase(fnt);

      return *this;
   }

   GraphicsCore& GraphicsCore::RemoveAllFonts ()
   {
      std::for_each(fonts.begin(), fonts.end(), [] (const std::pair<std::string, irr::gui::IGUIFont*> fnt) {
         fnt.second->drop();
      });

      fonts.clear();
      return *this;
   }

   GraphicsCore& GraphicsCore::AddTexture (const std::string& id, const std::string& textureFile)
   {
      if (id.empty())                               throw error::InvalidParam("No id specified!", __FUNCTION__);
      else if (textureFile.empty())                 throw error::InvalidParam("No texture file specified!", __FUNCTION__);
      else if (textures.find(id) != textures.end()) throw error::AlreadyExists("Specified id \"" + id + "\" already exists in map!", __FUNCTION__);

      auto tex = driver->getTexture(textureFile.c_str());
      if (tex == nullptr) throw error::Create("Failed to create texture from file \"" + textureFile + "\"!", __FUNCTION__);

      textures.insert(std::make_pair(id, tex));
      return *this;
   }

   GraphicsCore& GraphicsCore::RemoveTexture (const std::string& id)
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      auto tex = textures.find(id);
      if (tex == textures.end()) return *this;

      driver->removeTexture(tex->second);
      textures.erase(tex);

      return *this;
   }

   GraphicsCore& GraphicsCore::RemoveAllTextures ()
   {
      driver->removeAllTextures();
      textures.clear();

      return *this;
   }

   void GraphicsCore::BeginScene ()
   {
      driver->beginScene(true, true, clearColor.AsIrrColor());
   }

   void GraphicsCore::EndScene ()
   {
      driver->endScene();
   }

   GraphicsCore& GraphicsCore::DrawPixel (int x, int y, const Color& color)
   {
      driver->drawPixel(x, y, color.AsIrrColor());
      return *this;
   }

   GraphicsCore& GraphicsCore::DrawLine (int left, int top, int right, int bottom, const Color& color)
   {
      driver->draw2DLine(core::vector2d<int>(left, top), core::vector2d<int>(right, bottom), color.AsIrrColor());
      return *this;
   }

   GraphicsCore& GraphicsCore::DrawRectangle (int left, int top, int right, int bottom, const Color& color, const DrawType& type)
   {
      if (type == Outline) driver->draw2DRectangleOutline(core::rect<int>(left, top, right, bottom), color.AsIrrColor());
      else                 driver->draw2DRectangle(color.AsIrrColor(), core::rect<int>(left, top, right, bottom));
   
      return *this;
   }

   irr::gui::IGUIFont* GraphicsCore::Font (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      auto fnt = fonts.find(id);
      if (fnt == fonts.end()) throw error::NotFound("Font with id \"" + id + "\" does not exist!", __FUNCTION__);

      return fnt->second;
   }

   irr::video::ITexture* GraphicsCore::Texture (const std::string& id) const
   {
      if (id.empty()) throw error::InvalidParam("No id specified!", __FUNCTION__);

      auto tex = textures.find(id);
      if (tex == textures.end()) throw error::NotFound("Texture with id \"" + id + "\" does not exist!", __FUNCTION__);

      return tex->second;
   }

}

