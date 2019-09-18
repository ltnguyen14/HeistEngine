# HeistEngine

This repository houses the source code for HEIST Engine.

## Building

This project is using premake5. On Windows, run the generateProject.bat should
generate a VS2019 project file that you can open using VisualStudio 2019. If you
are not on Windows then you are out of luck :)

## Branches

Development take places in the main branch.

Stable release is in the Release branch.

## Future Roadmap

Trello board can be found here: https://trello.com/b/eYYYpAAv/heist-engine
## ECS Documentation

At the moment the engine is using a very simple ECS system for gameplay programming. Here is a simple example on how to use ECS:

1. Create a `ComponentManager` instance in Application.
2. Create a struct that inherit from `Component`:

```
struct TestComponent : public BaseComponent {
	TestComponent(int32 x, int32 y) : x(x), y(y) {};
	int32 x;
	int32 y;

	static int32 componentTypeId;
	static std::string name;
};
```
NOTE: `componentTypeId` and `name` needs to be there, but only `name` needs to be initialized (`componentTypeId` will be initialized when registered in `componentManager`). Components also need a constructor.

3. Register the component:
```
componentManager->AddComponentType<TestComponent>();
```

4. Create a new entity:
```
Entity ent1("Entity 1");
```

5. Register the entity:
```
componentManager->AddEntity(ent1);
```

6. To add component to an entity:
```
componentManager->AddComponents<TestComponent>(ent1, { {10, 20} });
```
NOTE: The initializor list should match the constructor

7. Create a system inherit from BaseSystem
```
struct TestSystem : public BaseSystem {
	TestSystem() {};

	static void Update(real32 delta);
};
```
NOTE: A `System` needs a static Update function

8. Implement the Update function:
```
  void TestSystem::Update(real32 delta) {
    auto dataVec = BaseSystem::componentManager->GetComponents<TestComponent>();
    for (auto data : dataVec) {
      std::shared_ptr<TestComponent> dataPointer = std::static_pointer_cast<TestComponent>(data);
      HS_CORE_INFO("Updating component type {}, data x {}, data y {}", dataPointer->componentTypeId, dataPointer->x, dataPointer->y);
    }
  }
```

9. Call Update in game update loop and you are done!
```
TestSystem::Update(time);
```
