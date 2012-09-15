
#pragma once

#include <irrlicht.h>

#include "Color.h"

#include "DLL_DEF.h"


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

   ge::Color clearColor;
   ge::Color foreColor;
   ge::Color backColor;

   void Init (irr::IrrlichtDevice* device);

public:
   GraphicsCore (irr::IrrlichtDevice* device);
   virtual ~GraphicsCore ();

   GraphicsCore& ClearColor (const ge::Color& color) { clearColor = color; return *this; }
   GraphicsCore& ForeColor (const ge::Color& color)  { foreColor = color; return *this; }
   GraphicsCore& BackColor (const ge::Color& color)  { backColor = color; return *this; }

   void BeginScene ();
   void EndScene ();

   GraphicsCore& DrawPixel (int x, int y, const ge::Color& color);
   GraphicsCore& DrawLine (int left, int top, int right, int bottom, const ge::Color& color);
   GraphicsCore& DrawRectangle (int left, int top, int right, int bottom, const ge::Color& colorTopLeft, const ge::Color& colorTopRight, const ge::Color& colorBottomRight, const ge::Color& colorBottomLeft, const DrawType& type);
   GraphicsCore& DrawRectangle (int left, int top, int right, int bottom, const ge::Color& color, const DrawType& type);

   GraphicsCore& DrawBox (int left, int top, int right, int bottom, const ge::Color& outlineColor, const ge::Color& fillColor)
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

   GraphicsCore& Text (int x, int y, const std::string& text);

   const ge::Color& ClearColor () const { return clearColor; }
   const ge::Color& ForeColor () const  { return foreColor; }
   const ge::Color& BackColor () const  { return backColor; }
};

