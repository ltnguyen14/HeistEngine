#include "hspch.h"
#include "EventNode.h"
#include "Core/Log.h"

namespace Heist {

	EventNode::EventNode(EventBus *eventBus, std::string name): eventBus(eventBus), name(name) {}
	EventNode::~EventNode() {}

	void EventNode::OnUpdate() {
		HS_CORE_TRACE(name + " does not implement OpUpdate function!");
	}

	void EventNode::OnNotify(Event event) {
		HS_CORE_TRACE(name + " does not implement OnNotify function!");
	}
}