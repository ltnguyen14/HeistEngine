#include "hspch.h"
#include "ThirdPersonCameraMovement.h"
#include "Core/Log/Log.h"

namespace Heist {
  ThirdPersonCameraMovement::ThirdPersonCameraMovement() {
    inputManager = InputManager::Instance();
  }

  ThirdPersonCameraMovement::~ThirdPersonCameraMovement() { }

  void ThirdPersonCameraMovement::AttachCamera(Camera *camera) {
    this->camera = camera;
  }

  void ThirdPersonCameraMovement::Update() {
    vec3 displacement = { 0, 0, 0};
    real32 speed = 0.25f;

    if (camera) {
      // Camera Movement
      if (inputManager->GetKey(HS_KEY_W) != HS_RELEASE) {
        displacement.x = -cos(radian(camera->rotation.y + 90)) * speed;
        displacement.z = -sin(radian(camera->rotation.y + 90)) * speed;
      } else if (inputManager->GetKey(HS_KEY_S) != HS_RELEASE) {
        displacement.x = cos(radian(camera->rotation.y + 90)) * speed;
        displacement.z = sin(radian(camera->rotation.y + 90)) * speed;
      };

      if (inputManager->GetKey(HS_KEY_A) != HS_RELEASE) {
        displacement.x = -cos(radian(camera->rotation.y)) * speed;
        displacement.z = -sin(radian(camera->rotation.y)) * speed;
        } else if (inputManager->GetKey(HS_KEY_D) != HS_RELEASE) {
        displacement.x = cos(radian(camera->rotation.y)) * speed;
        displacement.z = sin(radian(camera->rotation.y)) * speed;
      };

      camera->position.x += displacement.x;
      camera->position.y += displacement.y;
      camera->position.z += displacement.z;

      // Camera Rotation
      constexpr real32 ROTATION_FACTOR = 0.05f;
      real64 change_x, change_y, new_x, new_y;

      // Enter rotation mode
      if (!rotationMode && inputManager->GetKey(HS_MOUSE_BUTTON_MIDDLE) == HS_PRESS) {
        old_x = inputManager->GetMousePosition().x;
        old_y = inputManager->GetMousePosition().y;
        rotationMode = true;
      }

      if (rotationMode && inputManager->GetKey(HS_MOUSE_BUTTON_MIDDLE) == HS_RELEASE) {
        rotationMode = false;
      }

      if (rotationMode) {
        new_x = inputManager->GetMousePosition().x;
        new_y = inputManager->GetMousePosition().y;

        change_x = new_x - old_x;
        change_y = new_y - old_y;

        camera->rotation.y += change_x * ROTATION_FACTOR;
        camera->rotation.x += change_y * ROTATION_FACTOR;

        old_x = new_x;
        old_y = new_y;
      }
    }
  }
}
