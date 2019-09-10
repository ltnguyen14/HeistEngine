#include "hspch.h"
#include "Event.h"

namespace Heist {
	Event::Event(std::string eventName, int32 eventTypeMask): eventName(eventName), eventTypeMask(eventTypeMask), handled(false) {}
	Event::~Event() {}

	KeyEvent::KeyEvent(int32 value, int32 action)
		: Event("KeyEvent", KEYBOARD | INPUT), value(value), action(action) {
	}

	KeyEvent::~KeyEvent() {
	}
}