#include "hspch.h"
#include "Systems.h"

namespace Heist {
	void RenderSystem::Update(real32 delta) {
		auto renderableVec = BaseSystem::componentManager->GetComponents<RenderableComponent>();
		auto transformVec = BaseSystem::componentManager->GetComponents<TransformComponent>();
		for (auto data : renderableVec) {
			std::shared_ptr<RenderableComponent> dataPointer = std::static_pointer_cast<RenderableComponent>(data.second);
			std::shared_ptr<TransformComponent> transformPointer = std::static_pointer_cast<TransformComponent>(transformVec[data.first]);
			for (auto model : dataPointer->modelCollection->models) {
				if (transformPointer) {
					vec3 position = model->position + transformPointer->position;
					vec3 rotation = model->rotation + transformPointer->rotation;
					vec3 scale = { model->scale.x * transformPointer->scale.x, model->scale.y * transformPointer->scale.y, model->scale.z * transformPointer->scale.z };

					Renderer::Submit(model, MakeModelMatrix(position, rotation, scale));
				}
				else {
					Renderer::Submit(model);
				}
			}
		}
	}
}

