#include "hspch.h"
#include "InputManager.h"
#include "Core/Log/Log.h"
#include "Platform/Assertions.h"
#include "Core/Event/Event.h"

namespace Heist {

	InputManager* InputManager::g_inputManager = nullptr;

	InputManager* InputManager::Instance() {
		if (!g_inputManager) {
			g_inputManager = new InputManager();
		}

		return g_inputManager;
	}

	InputManager::~InputManager() {

	}

	void InputManager::StartUp() {
    g_memoryManager = MemoryManager::Instance();
	}

	void InputManager::ShutDown() {

	}

  void InputManager::SetMousePosition(real64 xpos, real64 ypos) {
    MousePositionSetEvent *event = (MousePositionSetEvent*)g_memoryManager->Alloc(sizeof(MousePositionSetEvent));
    new(event) MousePositionSetEvent(xpos, ypos);

    SendEvent(event);
  }

	void InputManager::OnNotify(Event *event) {
		if (event->eventTypeMask == (INPUT | KEYBOARD)) {
			KeyEvent *keyEvent = dynamic_cast<KeyEvent*>(event);
			HS_CORE_ASSERT(keyEvent, "Error type casting event!");

			keys[keyEvent->value] = (keyEvent->action != HS_RELEASE);
		} else if (event->eventTypeMask == (INPUT | MOUSE | POSITION)) {
      MousePositionEvent *mouseEvent = dynamic_cast<MousePositionEvent*>(event);
			HS_CORE_ASSERT(mouseEvent, "Error type casting event!");

      xpos = mouseEvent->xpos;
      ypos = mouseEvent->ypos;
    }
	}
}
