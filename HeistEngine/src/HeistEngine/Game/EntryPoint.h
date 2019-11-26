#pragma once

#ifdef HEIST_PLATFORM_WINDOWS
#include <stdlib.h>

extern Heist::Application* Heist::CreateApplication();

int main(int argc, char** agrv) {

	Heist::Log::Init();

	/* auto app = Heist::CreateApplication(); */
	/* app->Run(); */
	/* delete app; */

  Heist::tracer();
}

#else
#error Engine only supports Windows
#endif
