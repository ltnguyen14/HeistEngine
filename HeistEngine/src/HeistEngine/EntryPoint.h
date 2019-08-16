#pragma once

#ifdef HEIST_PLATFORM_WINDOWS

extern Heist::Application* Heist::CreateApplication();

int main(int argc, char** agrv) {

	Heist::Log::Init();
	HS_CORE_WARN("Engine Logger Inititated");
	HS_INFO("Client Logger Inititated");

	auto app = Heist::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Engine only supports Windows
#endif