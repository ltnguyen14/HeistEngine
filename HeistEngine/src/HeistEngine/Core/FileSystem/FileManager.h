#pragma once
#include "Macro.h"
#include "External/json/json.hpp"

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

	struct FileManager
	{
		FileManager();
		~FileManager();

		static std::string ReadFile(const char* filePath);
		static json ReadJSON(const char* filePath);

		static void WriteFile();

		static TextureData ReadTexture(const char* texturePath);
	};
}