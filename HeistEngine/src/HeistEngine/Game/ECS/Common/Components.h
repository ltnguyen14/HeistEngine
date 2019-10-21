#pragma once
#include "../BaseComponent.h"
#include "Core/Math/Math.h"
#include "Core/Renderer/Renderer.h"
#include <string>

namespace Heist {
	struct TransformComponent : public BaseComponent {
		TransformComponent(vec3 position, vec3 scale, vec3 rotation) : position(position), rotation(rotation), scale(scale) {};
		vec3 position;
		vec3 scale;
		vec3 rotation;

		static int32 componentTypeId;
		static std::string name;
	};

	struct RenderableComponent : public BaseComponent {
		 RenderableComponent(std::shared_ptr<RawModelCollection3D> rawModelCollection, std::shared_ptr<Shader> shader) {
			modelCollection = Heist::FileManager::CreateModelFromRawData(rawModelCollection, nullptr, shader, nullptr);
		 };

		std::shared_ptr<ModelCollection3D> modelCollection;
		static int32 componentTypeId;
		static std::string name;
	};
}
