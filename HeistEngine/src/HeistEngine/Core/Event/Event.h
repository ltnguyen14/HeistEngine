#pragma once
#include "Macro.h"

namespace Heist {

	enum EVENT_TYPE {
		NONE,
		MOUSE = BIT(0),
		KEYBOARD = BIT(1),
		APPLICATION = BIT(2),
		INPUT = BIT(3),
		POSITION = BIT(4),
		SCROLL = BIT(5),
		SET = BIT(6)
	};

	struct Event {
		Event(std::string eventName, int32 eventTypeMask);
		virtual ~Event();

		bool handled;
		std::string eventName;
		int32 eventTypeMask;
	};

	struct KeyEvent : public Event {
		KeyEvent(int32 value, int32 action);
		~KeyEvent() {};

		int32 value, action;
	};

	struct MousePositionEvent : public Event {
		MousePositionEvent(real64 xpos, real64 ypos);
		~MousePositionEvent() {};

		real64 xpos, ypos;
	};

	struct MousePositionSetEvent : public Event {
		MousePositionSetEvent(real64 xpos, real64 ypos);
		~MousePositionSetEvent() {};

		real64 xpos, ypos;
	};

	struct ScrollEvent : public Event {
		ScrollEvent(real64 xoffset, real64 yoffset);
		~ScrollEvent() {};

		real64 xoffset, yoffset;
	};
}
