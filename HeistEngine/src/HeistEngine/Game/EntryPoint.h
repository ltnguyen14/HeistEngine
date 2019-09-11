#pragma once

#ifdef HEIST_PLATFORM_WINDOWS
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

extern Heist::Application* Heist::CreateApplication();

int main(int argc, char** agrv) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Heist::Log::Init();

	auto app = Heist::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Engine only supports Windows
#endif