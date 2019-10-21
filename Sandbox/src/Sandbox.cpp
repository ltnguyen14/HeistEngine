#include <iostream>
#include <HeistEngine.h>

struct TestLayer : public Heist::Layer {

	TestLayer() : Layer("Test Layer") {
	}

	void OnAttach(const std::shared_ptr<Heist::ComponentManager>& componentManager) override {
    // Load assets
		// textureAtlas.reset(Heist::Texture::Create("assets/textures/woodBox.png"));
		// textureSpecAtlas.reset(Heist::Texture::Create("assets/textures/woodBox_spec.png"));

		shader.reset(Heist::Shader::Create("assets/shaders/rawMat.vert.glsl", "assets/shaders/rawMat.frag.glsl"));
		sunShader.reset(Heist::Shader::Create("assets/shaders/basic.vert.glsl", "assets/shaders/sun.frag.glsl"));

		// Material
    // std::shared_ptr<Heist::Material3D> material = std::make_shared<Heist::Material3D>(textureAtlas, textureSpecAtlas, 64.0f);

		// Test loading model
		auto planeRawModel = Heist::FileManager::ReadOBJFile("assets/models/", "plane.obj");
		Heist::Entity plane("Plane");
		componentManager->AddEntity(plane);
		// componentManager->AddComponents<Heist::RenderableComponent>(plane, { { planeRawModel, shader } });

		auto treeRawModel = Heist::FileManager::ReadOBJFile("assets/models/", "tree.obj");
		Heist::Entity tree("Tree 1");
		componentManager->AddEntity(tree);
		componentManager->AddComponents<Heist::RenderableComponent>(tree, {{ treeRawModel, shader }});
		componentManager->AddComponents<Heist::TransformComponent>(tree, { { {0, 0, 0}, {0, 0, 0}, {0.25f, 0.25f, 0.25f} } });

		auto sunRawModel = Heist::FileManager::ReadOBJFile("assets/models/", "sphere.obj");
		Heist::Entity sun("Sun");
		componentManager->AddEntity(sun);
		componentManager->AddComponents<Heist::RenderableComponent>(sun, { { sunRawModel, sunShader } });

		Heist::vec3 lightPosition = { 10, 20, 5 };
		light = Heist::Light3D(lightPosition, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f });

	}

	void OnUpdate(real64 time) override {
	}

	void OnRender(const std::shared_ptr<Heist::Camera>& camera) override {
		// Test loading models
		// sunModel->position = light.position;

		// --------------------
	}

	void OnWindowResize(real32 left, real32 right, real32 bottom, real32 top) override {
	}

private:
	std::shared_ptr<Heist::Texture> textureAtlas;
	std::shared_ptr<Heist::Texture> textureSpecAtlas;

	std::shared_ptr<Heist::Shader> shader;
	std::shared_ptr<Heist::Shader> sunShader;
};

class Sandbox : public Heist::Application {

public:
	Sandbox(): Application(1920, 1080, "Sandbox App") {
    AttachCameraMovement(&cameraMovement);
		PushLayer(new TestLayer);
	};

	~Sandbox() {};

  Heist::ThirdPersonCameraMovement cameraMovement;
};

Heist::Application* Heist::CreateApplication() {
	return new Sandbox();
}
