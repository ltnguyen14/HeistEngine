#include "MovementSystem.h"

void MovementSystem::Update(real32 delta) {
  auto transformVec = Heist::BaseSystem::componentManager->GetComponents<Heist::TransformComponent>();
  auto movementVec = Heist::BaseSystem::componentManager->GetComponents<MovementComponent>();
  for (auto data: transformVec) {
    std::shared_ptr<Heist::TransformComponent> dataPointer = std::static_pointer_cast<Heist::TransformComponent>(data.second);
    std::shared_ptr<MovementComponent> movementPointer = std::static_pointer_cast<MovementComponent>(movementVec[data.first]);
    if (movementPointer) {
      dataPointer->position = dataPointer->position + movementPointer->position;
      dataPointer->rotation = dataPointer->rotation + movementPointer->rotation;

      movementPointer->position = movementPointer->position * 0.8f;
      movementPointer->rotation = movementPointer->rotation * 0.8f;
    }
  }
}
