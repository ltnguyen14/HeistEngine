#include "hspch.h"
#include "GLTexture.h"
#include "glad/glad.h"
#include "Core/FileSystem/FileManager.h"

namespace Heist {

	GLTexture::GLTexture(const char* texturePath) {
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		TextureData textureData = FileManager::ReadTexture(texturePath);
		width = textureData.width;
		height = textureData.height;
		comp = textureData.comp;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.img);
	}

	GLTexture::~GLTexture() {

	}

	void GLTexture::Bind(int32 textureSlot) {
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void GLTexture::Unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}