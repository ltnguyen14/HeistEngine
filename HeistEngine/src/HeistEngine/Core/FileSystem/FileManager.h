#pragma once
#include "Macro.h"
#include "External/json/json.hpp"
#include "Core/Math/Math.h"
#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Texture.h"
#include "Core/Renderer/VertexArray.h"
#include "Core/Renderer/Model.h"

using json = nlohmann::json;

namespace Heist {

	struct FileManager
	{
		FileManager();
		~FileManager();

		static std::string ReadFile(const char* filePath);
		static Model3D* CreateModelFromRawData(RawModel3D *rawModel, const std::shared_ptr<Material3D> material, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture);
		static RawModel3D ReadOBJFile(const char* filePath, const char* fileName);
		static json ReadJSON(const char* filePath);
    static RawMaterial3D ReadMTLFile(const char* filePath);

		static void WriteFile();

		static TextureData ReadTexture(const char* texturePath);
	};
}
