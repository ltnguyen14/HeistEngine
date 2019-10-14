#include <iostream>
#include <HeistEngine.h>

struct TestLayer : public Heist::Layer {

	TestLayer() : Layer("Test Layer") {
	}

	void OnAttach() override {
    // Load assets
		textureAtlas.reset(Heist::Texture::Create("assets/textures/woodBox.png"));
		textureSpecAtlas.reset(Heist::Texture::Create("assets/textures/woodBox_spec.png"));

		shader.reset(Heist::Shader::Create("assets/shaders/basic.vert.glsl", "assets/shaders/basic.frag.glsl"));
		sunShader.reset(Heist::Shader::Create("assets/shaders/basic.vert.glsl", "assets/shaders/sun.frag.glsl"));

		// Material
		std::shared_ptr<Heist::Material3D> material = std::make_shared<Heist::Material3D>(textureAtlas, textureSpecAtlas, 64.0f);

		// Test loading model
		auto rawModel = Heist::FileManager::ReadOBJFile("assets/models/cube_texture.obj");
		testModel.reset(Heist::FileManager::CreateModelFromRawData(&rawModel, material, shader, textureAtlas));
		testModel->position = { 0, 0, 5 };

		auto sunRawModel = Heist::FileManager::ReadOBJFile("assets/models/sphere.obj");
		sunModel.reset(Heist::FileManager::CreateModelFromRawData(&sunRawModel, material, sunShader, textureAtlas));

		Heist::vec3 lightPosition = { -5, 0, -2 };
		light = Heist::Light3D(lightPosition, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f });
	}

	void OnUpdate(real64 time) override {
		testModel->rotation.y += 0.3f;
    // testModel->rotation.x += 0.3f;
	}

	void OnRender(const std::shared_ptr<Heist::Camera>& camera) override {
		// Test loading models
		sunModel->position = light.position;

		Heist::Renderer::BeginScene(camera, &light);

		Heist::Renderer::Submit(testModel);
		Heist::Renderer::Submit(sunModel);

		Heist::Renderer::EndScene();

		// --------------------
	}

	void OnWindowResize(real32 left, real32 right, real32 bottom, real32 top) override {
	}

private:
	std::shared_ptr<Heist::Texture> textureAtlas;
	std::shared_ptr<Heist::Texture> textureSpecAtlas;

	std::shared_ptr<Heist::Shader> shader;
	std::shared_ptr<Heist::Shader> sunShader;

	std::shared_ptr<Heist::Model3D> testModel;
	std::shared_ptr<Heist::Model3D> sunModel;
	Heist::Light3D light;
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
