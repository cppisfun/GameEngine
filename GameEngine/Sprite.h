
#pragma once

#include "DLL_DEF.h"

#include "Position.h"
#include "Size.h"
#include "Factor.h"
#include "Box.h"


namespace ge {

   class GEDLL Sprite
   {
   public:
      enum FlipType {
         None,
         Horizontal,
         Vertical,
         Both
      };

   private:
      ge::Position position;
      Size         size;
      Factor       scale;
      std::string  textureId;
      Position     currentImage;
      FlipType     flipState;
      double       rotationAngle;

//   public:
//      Sprite ();
//      virtual ~Sprite ();
//
//      Sprite& Position (const ge::Position& val)       { position = val; return *this; }
//      Sprite& Size (const ge::Size& val)               { size = val; return *this; }
//      Sprite& Scale (const Factor& val)                { scale = val; return *this; }
//      Sprite& TextureID (const std::string& val)       { textureId = val; return *this; }
//      Sprite& CurrentImage (size_t column, size_t row) { currentImage.Set(column * size.X(), row * size.Y()); }
//
//      virtual void Update () { }
//      virtual void Draw ();
//
//      const ge::Position& Position () const     { return position; }
//      const ge::Size& Size () const             { return size; }
//      const Factor& Scale () const              { return scale; }
//      const std::string& TextureID () const     { return textureId; }
//      const ge::Position& CurrentImage () const { return currentImage; }
//      FlipType FlipState () const               { return flipState; }
//
//      const Box& BoundingBox () const           { return Box(position.X(), position.Y(), size.X(), size.Y()); }
   };

}

