#include "hspch.h"
#include "EventNode.h"
#include "Core/Log/Log.h"

namespace Heist {

	EventNode::EventNode(EventBus *eventBus, std::string name): eventBus(eventBus), name(name) {
		eventBus->AddReceiver(this->GetNotificationFunc());
	}

	EventNode::~EventNode() {}

	void EventNode::OnNotify(Event event) {
	}
}