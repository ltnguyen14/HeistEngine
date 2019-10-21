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
    inline vec2 GetMouseScroll() const { return { (real32)xoffset, (real32)yoffset }; };
    inline void ResetScroll() { xoffset = 0; yoffset = 0; };

    void SetMousePosition(real64 xpos, real64 ypos);

		void OnNotify(Event *event) override;

	private:
		InputManager(): EventNode("InputManager") {};
		InputManager(InputManager const&): EventNode("InputManager") {};
		InputManager& operator=(InputManager const&) {};

		static InputManager* g_inputManager;

		int32 keys[512] = { 0 };
    real32 xoffset = 0;
    real32 yoffset = 0;
    real32 xpos, ypos;
    MemoryManager *g_memoryManager;
	};

}
