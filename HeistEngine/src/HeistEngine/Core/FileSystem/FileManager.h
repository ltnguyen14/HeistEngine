#pragma once

namespace Heist {

	struct TextureData {
		int32 width;
		int32 height;
		int32 comp;
		unsigned char* img;

		~TextureData();
		TextureData(int32 width, int32 height, int32 comp, unsigned char* img) : width(width), height(height), comp(comp), img(img){};
	};

	struct FileManager
	{
		FileManager();
		~FileManager();

		static std::string ReadFile(const char* filePath);
		static void WriteFile();

		static TextureData ReadTexture(const char* texturePath);
	};
}