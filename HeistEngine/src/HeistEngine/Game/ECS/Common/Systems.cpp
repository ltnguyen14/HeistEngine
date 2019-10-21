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
					// model->position = model->position + transformPointer->position;
					// model->rotation = model->rotation + transformPointer->rotation;
					// model->scale.x = model->scale.x * transformPointer->scale.x;
					// model->scale.y = model->scale.y * transformPointer->scale.y;
					// model->scale.z = model->scale.z * transformPointer->scale.z;
					model->scale = transformPointer->scale;
				}
				Renderer::Submit(model);
			}
		}
	}
}

