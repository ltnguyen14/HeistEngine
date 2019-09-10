#pragma once
#include "Core/Event/EventNode.h"

namespace Heist {

	class InputManager : public EventNode {
	public:
		InputManager(EventBus* eventBus);
		~InputManager();

		void StartUp();
		void ShutDown();

		inline bool GetKey(int32 key) const { return keys[key]; };

		void OnNotify(Event *event) override;

	private:
		bool keys[512] = { 0 };
	};

}