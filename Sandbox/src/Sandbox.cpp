#include <iostream>
#include <HeistEngine.h>

struct TestLayer : public Heist::Layer {

	TestLayer() : Layer("Test Layer") {
	}

};

class Sandbox : public Heist::Application {

public:
	Sandbox(): Application(190, 160, "Sandbox App") {
		PushLayer(new TestLayer);
	};

	~Sandbox() {};
};

Heist::Application* Heist::CreateApplication() {
	return new Sandbox();
}