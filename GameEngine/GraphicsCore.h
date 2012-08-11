
#pragma once

#include <irrlicht.h>

#include "Color.h"

#include "DLL_DEF.h"


class GEDLL GraphicsCore
{
   irr::video::IVideoDriver* driver;
   irr::gui::IGUIEnvironment* gui;

   Color clearColor;
   Color foreColor;
   Color backColor;

   void Init (irr::IrrlichtDevice* device);

public:
   GraphicsCore (irr::IrrlichtDevice* device);
   virtual ~GraphicsCore ();

   GraphicsCore& ClearColor (const Color& color) { clearColor = color; return *this; }
   GraphicsCore& ForeColor (const Color& color)  { foreColor = color; return *this; }
   GraphicsCore& BackColor (const Color& color)  { backColor = color; return *this; }

   void BeginScene ();
   void EndScene ();

   GraphicsCore& Text (int x, int y, const std::string& text);

   const Color& ClearColor () const { return clearColor; }
   const Color& ForeColor () const  { return foreColor; }
   const Color& BackColor () const  { return backColor; }
};

