#pragma once
#include "Core/Event/EventNode.h"
#include "Core/Math/Math.h"
#include "Core/Memory/Memory.h"

namespace Heist {

	class InputManager : public EventNode {
	public:
		static InputManager* Instance();
		~InputManager();

		void StartUp() override;
		void ShutDown() override;

		inline bool GetKey(int32 key) const { return keys[key]; };
		inline vec2 GetMousePosition() const { return { (real32)xpos, (real32 )ypos }; };

    void SetMousePosition(real64 xpos, real64 ypos);

		void OnNotify(Event *event) override;

	private:
		InputManager(): EventNode("InputManager") {};
		InputManager(InputManager const&): EventNode("InputManager") {};
		InputManager& operator=(InputManager const&) {};

		static InputManager* g_inputManager;

		bool keys[512] = { 0 };
    real64 xpos, ypos;
    MemoryManager *g_memoryManager;
	};

}
