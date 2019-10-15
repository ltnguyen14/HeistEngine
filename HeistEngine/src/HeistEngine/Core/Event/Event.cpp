#include "hspch.h"
#include "Event.h"

namespace Heist {
	Event::Event(std::string eventName, int32 eventTypeMask): eventName(eventName), eventTypeMask(eventTypeMask), handled(false) {}
	Event::~Event() {}

	KeyEvent::KeyEvent(int32 value, int32 action)
		: Event("KeyEvent", KEYBOARD | INPUT), value(value), action(action) {
	}

  MousePositionEvent::MousePositionEvent(real64 xpos, real64 ypos)
    : Event("MousePositionEvent", INPUT | MOUSE | POSITION), xpos(xpos), ypos(ypos){
  }

  MousePositionSetEvent::MousePositionSetEvent(real64 xpos, real64 ypos)
    : Event("MousePositionEvent", INPUT | MOUSE | POSITION | SET), xpos(xpos), ypos(ypos){
  }
}
