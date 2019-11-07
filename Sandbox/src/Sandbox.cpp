#include <iostream>
#include <HeistEngine.h>
#include <EntryPoint.h>
#include "Systems/MovementSystem.h"

struct TestLayer : public Heist::Layer {

	TestLayer() : Layer("Test Layer") {
	}

	real32 time;
	
	void OnAttach(const std::shared_ptr<Heist::ComponentManager>& componentManager) override {
		// Load assets
			// textureAtlas.reset(Heist::Texture::Create("assets/textures/woodBox.png"));
			// textureSpecAtlas.reset(Heist::Texture::Create("assets/textures/woodBox_spec.png"));
		this->componentManager = componentManager;

		shader.reset(Heist::Shader::Create("assets/shaders/rawMat.vert.glsl", "assets/shaders/rawMat.frag.glsl"));
		sunShader.reset(Heist::Shader::Create("assets/shaders/basic.vert.glsl", "assets/shaders/sun.frag.glsl"));

		// Material
	// std::shared_ptr<Heist::Material3D> material = std::make_shared<Heist::Material3D>(textureAtlas, textureSpecAtlas, 64.0f);

		// Test loading model
		auto planeRawModel = Heist::FileManager::ReadOBJFile("assets/models/", "plane.obj");
		Heist::Entity plane("Plane");
		componentManager->AddEntity(plane);
		componentManager->AddComponents<Heist::RenderableComponent>(plane, { { planeRawModel, shader } });
		componentManager->AddComponents<Heist::TransformComponent>(plane, { { {0, -2.0f, 0}, {} } });

		auto rockRawModel = Heist::FileManager::ReadOBJFile("assets/models/", "rock.obj");
		Heist::Entity rock("Rock 1");
		componentManager->AddEntity(rock);
		componentManager->AddComponents<Heist::RenderableComponent>(rock, { { rockRawModel, shader } });
		componentManager->AddComponents<Heist::TransformComponent>(rock, { { {2.0f, 0.0f, 4.5f}, {}, {0.5f, 0.5f, 0.5f} } });

		auto treeRawModel = Heist::FileManager::ReadOBJFile("assets/models/", "tree.obj");
		tree = new Heist::Entity("Tree 1");
		componentManager->AddEntity(*tree);
		componentManager->AddComponents<Heist::RenderableComponent>(*tree, { { treeRawModel, shader } });
		componentManager->AddComponents<Heist::TransformComponent>(*tree, { { {}, {}, {0.25f, 0.25f, 0.25f} } });

		auto personRawModel = Heist::FileManager::ReadOBJFile("assets/models/", "person.obj");
		person = new Heist::Entity("Person 1");
		componentManager->AddEntity(*person);
		componentManager->AddComponents<Heist::RenderableComponent>(*person, { { personRawModel, shader } });
		componentManager->AddComponents<Heist::TransformComponent>(*person, { { { 0.0f, 0.0f, 5.0f }, {} } });
		componentManager->AddComponents<MovementComponent>(*person, { { {}, {} } });

		Heist::vec3 lightPosition = { 10, 20, 5 };
		light = Heist::Light3D(lightPosition, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, {});

		auto sunRawModel = Heist::FileManager::ReadOBJFile("assets/models/", "sphere.obj");
		Heist::Entity sun("Sun");
		componentManager->AddEntity(sun);
		componentManager->AddComponents<Heist::RenderableComponent>(sun, { { sunRawModel, sunShader } });
		componentManager->AddComponents<Heist::TransformComponent>(sun, { { lightPosition, {0, 0, 0} } });
	}

	void OnUpdate(real64 time) override {
		this->time = time;
		auto movementComponent = componentManager->GetEntityComponent<MovementComponent>(*person);
		auto personTransform = componentManager->GetEntityComponent<Heist::TransformComponent>(*person);
		static bool goingDown = true;
		if (movementComponent && personTransform) {
			if (personTransform->position.x <= 0.0f) {
				goingDown = true;
				personTransform->rotation.y = 90.0f;
			}
			else if (personTransform->position.x >= 10.0f) {
				goingDown = false;
				personTransform->rotation.y = 270.0f;
			}

			if (goingDown) {
				movementComponent->position.x += 0.5f * time;
			}
			else {
				movementComponent->position.x -= 0.5f * time;
			}
		}

		MovementSystem::Update(time);
	}

	void OnRender(const std::shared_ptr<Heist::Camera>& camera) override {
		// Test loading models
		// sunModel->position = light.position;

		// --------------------
	}

	void OnOverlay() override {
		Heist::GUIManager::BeginFrame();
		{
			Heist::GUIManager::Layout({0.0f, 0.0f, 32.0f, 32.0f}, { 3, -1});
			{
			  for (int32 i = 0; i <= 2; i++) {
			    if (Heist::GUIManager::Button({ 200.0f, 100.0f }, { 0.26f, 0.68f, 0.84f, 1.f })) {
			      HS_CORE_INFO("Button {} is pressed", i);
			    }
			  }
			} Heist::GUIManager::PopLayout();

			std::string textSample = "Press me Press me Press me";

			Heist::GUIManager::ButtonP({ 100.0f, 0.0f, 500.0f }, { 0.2f, 0.4f, 0.8f, 1.0f }, "This is a button with text", { 0.8f, 0.4f, 0.2f, 1.0f }, 10.0f);
		}
		Heist::GUIManager::EndFrame();
	}

	void OnWindowResize(real32 left, real32 right, real32 bottom, real32 top) override {
	}

private:
	std::shared_ptr<Heist::Texture> textureAtlas;
	std::shared_ptr<Heist::Texture> textureSpecAtlas;

	std::shared_ptr<Heist::Shader> shader;
	std::shared_ptr<Heist::Shader> sunShader;

	Heist::Entity* tree;
	Heist::Entity* person;
};

class Sandbox : public Heist::Application {

public:
	Sandbox() : Application(1920, 1080, "Sandbox App") {
		camera->position = { 0, 20, 20 };
		AttachCameraMovement(&cameraMovement);

		// Subscribe new component
		componentManager->AddComponentType<Heist::RenderableComponent>();
		componentManager->AddComponentType<Heist::TransformComponent>();
		componentManager->AddComponentType<MovementComponent>();
		// ------------------------

		PushLayer(new TestLayer);
	};

	~Sandbox() {};

	Heist::ThirdPersonCameraMovement cameraMovement;
};

Heist::Application* Heist::CreateApplication() {
	return new Sandbox();
}
