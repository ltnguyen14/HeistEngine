#pragma once
#include "Platform/Assertions.h"
#include "Core/Math/Math.h"

namespace Heist {
  int tracer();

#pragma pack(push, 1)
  struct bitmap_header {
    uint16 fileType;
    uint32 fileSize;
    uint16 reserved1;
    uint16 reserved2;
    uint32 bitmapOffset;
    uint32 size;
    int32 width;
    int32 height;
    uint16 planes;
    uint16 bitsPerPixel;
    uint32 compression;
    uint32 sizeOfBitmap;
    int32 horizontalResolution;
    int32 verticalResolution;
    uint32 colorsUsed;
    uint32 colorsImportant;
  };
#pragma pack(pop)

  struct image_u32 {
    uint32 width;
    uint32 height;
    uint32 *pixels;
  };

  struct material {
    vec3 color;
  };

  struct plane {
    vec3 normal;
    real32 d;
    uint32 matIndex;
  };

  struct sphere {
    vec3 position;
    real32 r;
    uint32 matIndex;
  };

  struct world {
    uint32 materialCount;
    material *materials;

    uint32 planeCount;
    plane *planes;

    uint32 sphereCount;
    sphere *spheres;
  };
}
