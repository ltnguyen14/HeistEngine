#pragma once
#include "EventBus.h"
#include "Event.h"

namespace Heist {

	struct EventNode {

		EventNode(const std::string& name);
		~EventNode();

		void SubscribeToBus(EventBus* eventBus);
		virtual void StartUp() = 0;
		virtual void ShutDown() = 0;

		virtual void OnNotify(Event* event);

		std::function<void(Event*)> GetNotificationFunc() {
			return [=](Event* event) {
				return OnNotify(event);
			};
		}

		void SendEvent(Event* event) {
			eventBus->SendEvent(event);
		}

	private:
		EventBus* eventBus;
		std::string name;
	};

}