#pragma once
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Core/Math/Math.h"

namespace Heist {

	struct RawModel {
		RawModel(std::shared_ptr<Shader>& shader,
			std::shared_ptr<Texture>& texture,
			std::shared_ptr<VertexArray>& vertexArray,
			mat4* modelMatrix) 
			:shader(shader), texture(texture), vertexArray(vertexArray), modelMatrix(modelMatrix) {
		};

		std::shared_ptr<Shader>& shader;
		std::shared_ptr<Texture>& texture;
		std::shared_ptr<VertexArray>& vertexArray;
		mat4* modelMatrix;
	};

}