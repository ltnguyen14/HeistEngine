#include "hspch.h"
#include "EventBus.h"

namespace Heist {

	EventBus::EventBus() {}
	EventBus::~EventBus() {}

	void EventBus::AddReceiver(std::function<void(Event)> receiver) {
		receivers.push_back(receiver);
	}

	void EventBus::SendEvent(Event event) {
		events.push(event);
	}

	void EventBus::Notify() {
		while (!events.empty()) {
			for (auto receiver : receivers) {
				if (!events.front().handled)
					receiver(events.front());
			}
			events.pop();
		}
	}

}