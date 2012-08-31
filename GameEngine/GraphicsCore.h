
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

   GraphicsCore& Text (int x, int y, const std::string& text);

   const Color& ClearColor () const { return clearColor; }
   const Color& ForeColor () const  { return foreColor; }
   const Color& BackColor () const  { return backColor; }
};

