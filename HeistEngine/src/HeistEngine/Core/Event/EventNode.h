#pragma once
#include "EventBus.h"
#include "Event.h"

namespace Heist {

	struct EventNode {

		EventNode(EventBus *eventBus, std::string name);
		~EventNode();

		virtual void OnNotify(Event *event);

		std::function<void(Event*)> GetNotificationFunc() {
			return [=](Event *event) {
				return OnNotify(event);
			};
		}

		void SendEvent(Event *event) {
			eventBus->SendEvent(event);
		}

	private:
		EventBus* eventBus;
		std::string name;
	};

}