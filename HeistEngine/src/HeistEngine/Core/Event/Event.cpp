#include "hspch.h"
#include "Event.h"

namespace Heist {
	Event::Event(std::string eventName, int32 eventTypeMask): eventName(eventName), eventTypeMask(eventTypeMask), handled(false) {}
	Event::~Event() {}
}