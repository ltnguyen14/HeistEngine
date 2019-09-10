#pragma once
#include "Event.h"
#include "queue"
#include "functional"

namespace Heist {
	struct EventBus {

		EventBus();
		~EventBus();

		void AddReceiver(std::function<void(Event*)> receiver);
		void SendEvent(Event *event);

		void Notify();

	private:
		std::vector<std::function<void(Event*)>> receivers;
		std::queue<Event*> events;
	};
}