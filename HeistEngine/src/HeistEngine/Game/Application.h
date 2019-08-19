#pragma once
#include "../Macro.h"
#include "../Platform/Assertions.h"
#include "../Core/Math/Math.h"

namespace Heist {
	class HEIST_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	
	// To be defined in client
	Application* CreateApplication();
}