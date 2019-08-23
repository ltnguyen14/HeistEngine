#pragma once
#include "Core/Event/EventNode.h"

namespace Heist {
	struct Window : public EventNode {
		Window(EventBus *eventBus);
		~Window();
	};
}
