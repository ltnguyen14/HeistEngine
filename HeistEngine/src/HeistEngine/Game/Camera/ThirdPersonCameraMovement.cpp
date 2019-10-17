#include "hspch.h"
#include "ThirdPersonCameraMovement.h"
#include "Core/Log/Log.h"

namespace Heist {
  real64 g_xPos = 100;
  real64 g_yPos = 100;

  ThirdPersonCameraMovement::ThirdPersonCameraMovement() {
    inputManager = InputManager::Instance();

    inputManager->SetMousePosition(g_xPos, g_yPos);
    old_x = g_xPos;
    old_y = g_yPos;
  }

  ThirdPersonCameraMovement::~ThirdPersonCameraMovement() { }

  void ThirdPersonCameraMovement::AttachCamera(Camera *camera) {
    this->camera = camera;
  }

  void ThirdPersonCameraMovement::Update() {
    vec3 displacement = { 0, 0, 0};
    real32 speed = 0.25f;

    if (camera) {
      // Camera Rotation
      static auto const BOUND = 80;
      constexpr real32 ROTATION_FACTOR = 0.05f;
      real64 change_x, change_y, new_x, new_y;

      new_x = inputManager->GetMousePosition().x;
      new_y = inputManager->GetMousePosition().y;

      if (!std::isinf(new_x) && !std::isinf(new_y)) {
        change_x = new_x - old_x;
        change_y = new_y - old_y;

        camera->rotation.y += change_x * ROTATION_FACTOR;
        camera->rotation.x += change_y * ROTATION_FACTOR;

        if (camera->rotation.x > BOUND) camera->rotation.x = BOUND;
        else if (camera->rotation.x < -BOUND) camera->rotation.x = -BOUND;

        if (camera->rotation.y > 360) camera->rotation.y = 0;
        else if (camera->rotation.y < 0) camera->rotation.y = 360;

        old_x = g_xPos;
        old_y = g_yPos;
        inputManager->SetMousePosition(g_xPos, g_yPos);
      }

      // Camera Movement
      if (inputManager->GetKey(HS_KEY_W)) {
        displacement.x = cos(radian(camera->rotation.y + 90)) * speed;
        displacement.z = sin(radian(camera->rotation.y + 90)) * speed;
      } else if (inputManager->GetKey(HS_KEY_S)) {
        displacement.x = -cos(radian(camera->rotation.y + 90)) * speed;
        displacement.z = -sin(radian(camera->rotation.y + 90)) * speed;
      };

      if (inputManager->GetKey(HS_KEY_A)) {
        displacement.x = -cos(radian(camera->rotation.y)) * speed;
        displacement.z = -sin(radian(camera->rotation.y)) * speed;
      } else if (inputManager->GetKey(HS_KEY_D)) {
        displacement.x = cos(radian(camera->rotation.y)) * speed;
        displacement.z = sin(radian(camera->rotation.y)) * speed;
      };

      camera->position.x += displacement.x;
      camera->position.y += displacement.y;
      camera->position.z += displacement.z;
    }
  }
}
