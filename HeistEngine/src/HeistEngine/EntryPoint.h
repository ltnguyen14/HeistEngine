#pragma once

#ifdef HEIST_PLATFORM_WINDOWS

extern Heist::Application* Heist::CreateApplication();

int main(int argc, char** agrv) {
	auto app = Heist::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Engine only supports Windows
#endif