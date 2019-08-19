#include <iostream>
#include <HeistEngine.h>

class Sandbox : public Heist::Application {

public:
	Sandbox() {};
	~Sandbox() {};

};

Heist::Application* Heist::CreateApplication() {
	HS_INFO("Creating application");
	return new Sandbox();
}