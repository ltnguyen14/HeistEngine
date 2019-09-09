#include "hspch.h"
#include "FileManager.h"
#include "Platform/Assertions.h"

#define STB_IMAGE_IMPLEMENTATION
#include "External/stb_image.h"

namespace Heist {

	TextureData::~TextureData() {
		if (img) {
			stbi_image_free(img);
		}
	}

	FileManager::FileManager() {
	}

	FileManager::~FileManager() {
	}

	std::string FileManager::ReadFile(const char* filePath) {
		std::ifstream file(filePath);
		HS_CORE_ASSERT(!file.fail(), "Cannot open file path: " + std::string(filePath));
		std::string content;

		file.seekg(0, std::ios::end);
		content.reserve(file.tellg());
		file.seekg(0, std::ios::beg);

		content.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		file.close();
		return content;
	}

	void FileManager::WriteFile() {
	}

	TextureData FileManager::ReadTexture(const char* texturePath) {
		int32 width, height, comp;
		// stbi_set_flip_vertically_on_load(1);
		unsigned char* img = stbi_load(texturePath, &width, &height, &comp, 4);

		if (!img) {
			HS_CORE_ERROR("Fail to load texture: {}", texturePath);
		} else {
			HS_CORE_TRACE("Texture loaded: {}", texturePath);
		}
		
		return {width, height, comp, img};
	}

}