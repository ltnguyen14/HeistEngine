#pragma once
#include "Macro.h"
#include "External/json/json.hpp"
#include "Core/Math/Math.h"

using json = nlohmann::json;

namespace Heist {

	struct TextureData {

		TextureData(int32 width, int32 height, int32 comp, unsigned char* img) : width(width), height(height), comp(comp), img(img) {};
		~TextureData();

		int32 width;
		int32 height;
		int32 comp;
		unsigned char* img;
	};

	struct Model3D {
		std::vector<real32> verticies;
		std::vector<uint32> indicies;
		vec3 position;
		vec3 rotation;
		vec3 scale;
	};

	struct FileManager
	{
		FileManager();
		~FileManager();

		static std::string ReadFile(const char* filePath);
		static Model3D ReadOBJFile(const char* filePath);
		static json ReadJSON(const char* filePath);

		static void WriteFile();

		static TextureData ReadTexture(const char* texturePath);
	};
}