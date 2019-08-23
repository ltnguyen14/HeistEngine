#pragma once
#include "Macro.h"

namespace Heist {

	enum EVENT_TYPE {
		NONE,
		MOUSE = BIT(0),
		KEYBOARD = BIT(1),
		APPLICATION = BIT(2),
		INPUT = BIT(3)
	};

	struct Event {
		Event(std::string eventName, int32 eventTypeMask);
		~Event();

		bool handled;
		std::string eventName;
		int32 eventTypeMask;
	};

}