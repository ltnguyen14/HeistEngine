#include "hspch.h"
#include "ray.h"
#include "Platform/Assertions.h"

int test() {
  HS_CORE_INFO("Running tracer");
  uint32 outputHeight = 1080;
  uint32 outputWidth = 1920;

  uint32 outputPixelsSize = sizeof(uint32) * outputHeight * outputWidth;
  uint32 *outputPixels = (uint32*) malloc(outputPixelsSize);
  uint32 *out = outputPixels;

  for (int32 y = 0; y < outputHeight; ++y) {
    for (int32 x = 0; x < outputWidth; ++x) {
      *out++ = 0xFF0000FF;
    }
  }

  bitmap_header header = {};
  header.fileType = 0x4D42;
  header.fileSize = outputPixelsSize + sizeof(header);
  header.bitmapOffset = sizeof(header);
  header.size = sizeof(header) - 14;
  header.width = outputWidth;
  header.height = outputHeight;
  header.planes = 1;
  header.bitsPerPixel = 32;
  header.compression = 0;
  header.sizeOfBitmap = outputPixelsSize;
  header.horizontalResolution = 0;
  header.verticalResolution = 0;
  header.colorsUsed = 0;
  header.colorsImportant = 0;

  const char* outputFileName = "test.bmp";
  FILE *outFile = fopen(outputFileName, "wb");
  if (outFile) {
    fwrite(&header, sizeof(header), 1, outFile);
    fwrite(outputPixels, outputPixelsSize, 1, outFile);
    fclose(outFile);
  } else {
    HS_CORE_ERROR("Couldn't write to file {}", outputFileName);
  }

  exit(0);
  return 0;
}
