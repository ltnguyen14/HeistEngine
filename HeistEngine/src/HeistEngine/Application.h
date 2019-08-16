#pragma once
#include "Macro.h"

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