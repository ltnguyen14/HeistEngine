#include "hspch.h"
#include "Application.h"

namespace Heist {

	Application::Application() {}
	Application::~Application() {}

	void Application::Run() {
		vec3 v = { 1, 2, 3 };
		vec3 mul = v * 10;

		std::cout << mul.x << mul.y << mul.z << std::endl;
		while (true);
	}
}