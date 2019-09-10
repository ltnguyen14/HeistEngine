#pragma once
#include "Core/Event/EventNode.h"

namespace Heist {

	class InputManager : public EventNode {
	public:
		static InputManager* Instance();
		~InputManager();

		void StartUp() override;
		void ShutDown() override;

		inline bool GetKey(int32 key) const { return keys[key]; };

		void OnNotify(Event *event) override;

	private:
		InputManager(): EventNode("InputManager") {};
		InputManager(InputManager const&): EventNode("InputManager") {};
		InputManager& operator=(InputManager const&) {};

		static InputManager* g_inputManager;

		bool keys[512] = { 0 };
	};

}