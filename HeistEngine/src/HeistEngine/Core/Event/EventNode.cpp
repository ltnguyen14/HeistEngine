#include "hspch.h"
#include "EventNode.h"
#include "Core/Log/Log.h"

namespace Heist {

	EventNode::EventNode(std::string name): name(name) {
	}

	EventNode::~EventNode() {}

	void EventNode::SubscribeToBus(EventBus* eventBus) {
		this->eventBus = eventBus;
		this->eventBus->AddReceiver(this->GetNotificationFunc());
	}


	void EventNode::OnNotify(Event *event) {
	}
}