#pragma once
#include "Platform/Assertions.h"

int test();

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

