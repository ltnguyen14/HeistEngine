#include "hspch.h"
#include "Platform/Assertions.h"
#include "ray.h"
#include "float.h"

#define F32Max FLT_MAX
#define F32Min -FLT_MAX

namespace Heist {
  uint32 GetTotalPixelSize(image_u32 image) {
    return image.width * image.height * sizeof(uint32);
  }

  image_u32 AllocateImage(uint32 width, uint32 height) {
    image_u32 image = {};
    image.width = width;
    image.height = height;
    uint32 outputPixelsSize = GetTotalPixelSize(image);
    image.pixels = (uint32*) malloc(outputPixelsSize);

    return image;
  }

  void WriteImage(image_u32 image, char *fileName) {
    uint32 outputPixelsSize = GetTotalPixelSize(image);

    bitmap_header header = {};
    header.fileType = 0x4D42;
    header.fileSize = outputPixelsSize + sizeof(header);
    header.bitmapOffset = sizeof(header);
    header.size = sizeof(header) - 14;
    header.width = image.width;
    header.height = image.height;
    header.planes = 1;
    header.bitsPerPixel = 32;
    header.compression = 0;
    header.sizeOfBitmap = outputPixelsSize;
    header.horizontalResolution = 0;
    header.verticalResolution = 0;
    header.colorsUsed = 0;
    header.colorsImportant = 0;

    FILE *outFile = fopen(fileName, "wb");
    if (outFile) {
      fwrite(&header, sizeof(header), 1, outFile);
      fwrite(image.pixels, outputPixelsSize, 1, outFile);
      fclose(outFile);
    } else {
      HS_CORE_ERROR("Couldn't write to file {}", fileName);
    }
  }

  vec3 RayCast(world *world, const vec3& rayOrigin, const vec3& rayDirection) {
    vec3 result = world->materials[0].color;
    real32 hitDistance = F32Max;

    for (uint32 planeIndex = 0; planeIndex < world->planeCount; ++planeIndex) {
      plane plane = world->planes[planeIndex];

      real32 tolerance = 0.00001f;
      real32 denom = Inner(plane.normal, rayDirection);
      if ((denom < -tolerance) || (denom > tolerance)) {
        real32 distance = (-plane.d - Inner(plane.normal, rayOrigin)) / denom;
        if ((distance < hitDistance) && (distance > 0)) {
          hitDistance = distance;
          result = world->materials[plane.matIndex].color;
        }
      }
    }

    return result;
  }

  int tracer() {
    vec3 cameraPosition = {0, 10.0f, 1.0f};

    vec3 cameraRotationZ = Normalize(cameraPosition);
    vec3 cameraRotationX = Normalize(Cross(cameraRotationZ, vec3(0, 0, 1)));
    vec3 cameraRotationY = Normalize(Cross(cameraRotationZ, cameraRotationX));

    material materials[2] = {};
    materials[0].color = vec3(0, 0, 0);
    materials[1].color = vec3(1, 0, 0);

    plane plane = {};
    plane.normal = vec3(0.0f, 0.0f, 1.0f);
    plane.d = 0;
    plane.matIndex = 1;

    world world = {};
    world.materialCount = 2;
    world.materials = materials;
    world.planeCount = 1;
    world.planes = &plane;
    world.sphereCount = 0;
    world.spheres = NULL;

    uint32 outputWidth = 1920;
    uint32 outputHeight = 1080;
    image_u32 image = AllocateImage(outputWidth, outputHeight);

    uint32 *out = image.pixels;
    real32 filmDist = 1.0f;
    real32 filmW = 1.0f;
    real32 filmH = 1.0f;
    real32 halfFilmW = filmW * 0.5f;
    real32 halfFilmH = filmH * 0.5f;
    vec3 filmCenter = cameraPosition - cameraRotationZ * filmDist;

    for (int32 y = 0; y < outputHeight; ++y) {
      real32 filmY = -1.0f + 2.0f * ((real32)y / (real32)image.height);
      for (int32 x = 0; x < outputWidth; ++x) {
        real32 filmX = -1.0f + 2.0f * ((real32)x / (real32)image.width);
        vec3 filmP = filmCenter + cameraRotationX * filmX * halfFilmW + cameraRotationY * filmY * halfFilmH;
        vec3 rayOrigin = cameraPosition;
        vec3 rayDirection = Normalize(filmP - cameraPosition);

        vec3 color = RayCast(&world, rayOrigin, rayDirection);

        *out = BGRAPack4x8(vec4(color * 255.0f, 255.0f));
        out++;
      }
    }

    WriteImage(image, "test.bmp");

    exit(0);
    return 0;
  }
}
