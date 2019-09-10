#include "hspch.h"
#include "InputManager.h"
#include "Core/Log/Log.h"
#include "Platform/Assertions.h"

namespace Heist {

	InputManager::InputManager(EventBus* eventBus)
		: EventNode(eventBus, "Input Manager") {

	}

	InputManager::~InputManager() {

	}

	void InputManager::StartUp() {

	}

	void InputManager::ShutDown() {

	}

	void InputManager::OnNotify(Event *event) {
		if (event->eventTypeMask == (INPUT | KEYBOARD)) {
			KeyEvent *keyEvent = dynamic_cast<KeyEvent*>(event);
			HS_CORE_ASSERT(keyEvent, "Error type casting event!");

			keys[keyEvent->value] = (keyEvent->action != HS_RELEASE);
		}
	}
}