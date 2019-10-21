#include "hspch.h"
#include "Systems.h"

namespace Heist {
	void RenderSystem::Update(real32 delta) {
		auto renderableVec = BaseSystem::componentManager->GetComponents<RenderableComponent>();
		for (auto data : renderableVec) {
			std::shared_ptr<RenderableComponent> dataPointer = std::static_pointer_cast<RenderableComponent>(data);
			for (auto model : dataPointer->modelCollection->models) {
				Renderer::Submit(model);
			}
		}
	}
}

