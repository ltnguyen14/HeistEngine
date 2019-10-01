#pragma once
#include "Macro.h"
#include "External/json/json.hpp"
#include "Core/Math/Math.h"
#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Texture.h"
#include "Core/Renderer/VertexArray.h"

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

	struct RawModel3D {
		uint32 verticiesNum = 0;
		std::vector<real32> verticies;
		std::vector<real32> normals;
		std::vector<uint32> indicies;
		std::vector<real32> dataBuffer;
	};

	struct Model3D {

		Model3D(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, const std::shared_ptr<VertexArray>& vertexArray, bool useIndicies)
			: shader(shader), texture(texture), vertexArray(vertexArray), 
			position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1), c_position(position), c_rotation(rotation), c_scale(scale), c_modelMatrix(1), useIndicies(useIndicies) {};

		mat4 GetModelMatrix() {
			if ((position != c_position) || (rotation != c_rotation) || (scale != c_scale)) {
				c_modelMatrix = MakeModelMatrix(position, rotation, scale);
				c_position = position;
				c_rotation = rotation;
				c_scale = scale;

				return c_modelMatrix;
			} else {
				return c_modelMatrix;
			}
		};

		bool useIndicies;

		std::shared_ptr<Shader> shader;
		std::shared_ptr<Texture> texture;
		std::shared_ptr<VertexArray> vertexArray;

		vec3 position;
		vec3 rotation;
		vec3 scale;

		vec3 c_position;
		vec3 c_rotation;
		vec3 c_scale;

		mat4 c_modelMatrix;
	};

	struct FileManager
	{
		FileManager();
		~FileManager();

		static std::string ReadFile(const char* filePath);
		static Model3D* CreateModelFromRawData(RawModel3D *rawModel, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture);
		static RawModel3D ReadOBJFile(const char* filePath);
		static json ReadJSON(const char* filePath);

		static void WriteFile();

		static TextureData ReadTexture(const char* texturePath);
	};
}