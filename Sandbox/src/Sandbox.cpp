#include <iostream>
#include <HeistEngine.h>

class Sandbox : public Heist::Application {

public:
	Sandbox(): Application(1920, 1080, "Sandbox App") {};
	~Sandbox() {};
};

Heist::Application* Heist::CreateApplication() {
	return new Sandbox();
}