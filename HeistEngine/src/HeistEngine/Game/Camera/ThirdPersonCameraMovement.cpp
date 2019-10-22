#include "hspch.h"
#include "ThirdPersonCameraMovement.h"
#include "Core/Log/Log.h"

namespace Heist {
  ThirdPersonCameraMovement::ThirdPersonCameraMovement() {
    inputManager = InputManager::Instance();
  }

  ThirdPersonCameraMovement::~ThirdPersonCameraMovement() { }

  void ThirdPersonCameraMovement::AttachCamera(Camera *camera) {
    // Set up the camera to look down
    this->camera = camera;
    camera->rotation.x = 45.0f;
  }

  void ThirdPersonCameraMovement::Update() {

    displacement = displacement * 0.8f;
    if (camera) {

      // Enter rotation mode
      if (!movingMode && inputManager->GetKey(HS_MOUSE_BUTTON_RIGHT) == HS_PRESS) {
        old_x = inputManager->GetMousePosition().x;
        old_y = inputManager->GetMousePosition().y;
        movingMode = true;
      }

      if (movingMode && inputManager->GetKey(HS_MOUSE_BUTTON_RIGHT) == HS_RELEASE) {
        movingMode = false;
      }

      // Camera Movement
      if (movingMode) {
        real64 change_x, change_y, new_x, new_y;
        real32 speed = 0.02f;

        new_x = inputManager->GetMousePosition().x;
        new_y = inputManager->GetMousePosition().y;

        change_x = new_x - old_x;
        change_y = new_y - old_y;

        // Forward
        displacement.x = -cos(radian(camera->rotation.y + 90)) * speed * change_y;
        displacement.z = -sin(radian(camera->rotation.y + 90)) * speed * change_y;

        // Sideways
        displacement.x -= cos(radian(camera->rotation.y)) * speed * change_x;
        displacement.z -= sin(radian(camera->rotation.y)) * speed * change_x;

        old_x = new_x;
        old_y = new_y;
      }

      camera->position = camera->position + displacement;

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

      // Camera levitation
      real32 yoffset = inputManager->GetMouseScroll().y;
      real32 levitationFactor = 0.6f;
      if (yoffset != 0) {
        camera->position.y -= yoffset * levitationFactor;
      }

    }
  }
}
