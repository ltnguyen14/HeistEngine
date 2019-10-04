#pragma once
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Core/Math/Math.h"

namespace Heist {

	struct RawModel3D {
		uint32 verticiesNum = 0;
		std::vector<real32> verticies;
		std::vector<real32> normals;
		std::vector<uint32> indicies;
		std::vector<real32> dataBuffer;
	};

	struct TextureData {

		TextureData(int32 width, int32 height, int32 comp, unsigned char* img) : width(width), height(height), comp(comp), img(img) {};
		~TextureData();

		int32 width;
		int32 height;
		int32 comp;
		unsigned char* img;
	};

	struct Material3D {
		Material3D(vec3 ambient, vec3 diffuse, vec3 specular, real32 reflectiveness = 64)
			: ambient(ambient), diffuse(diffuse), specular(specular), reflectiveness(reflectiveness){};
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		real32 reflectiveness;
	};

	struct Model3D {

		Model3D(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material3D> material, const std::shared_ptr<Texture>& texture, const std::shared_ptr<VertexArray>& vertexArray, bool useIndicies)
			: shader(shader), texture(texture), vertexArray(vertexArray), material(material),
			position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1), c_position(position), c_rotation(rotation), c_scale(scale), c_modelMatrix(1), useIndicies(useIndicies) {};

		mat4 GetModelMatrix() {
			if ((position != c_position) || (rotation != c_rotation) || (scale != c_scale)) {
				c_modelMatrix = MakeModelMatrix(position, rotation, scale);
				c_position = position;
				c_rotation = rotation;
				c_scale = scale;

				return c_modelMatrix;
			}
			else {
				return c_modelMatrix;
			}
		};

		bool useIndicies;

		std::shared_ptr<Shader> shader;
		std::shared_ptr<Material3D> material;
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

	struct Light3D {

		Light3D(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular)
			:position(position), ambient(ambient), diffuse(diffuse), specular(specular) {}

		vec3 position;

		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
	};

}