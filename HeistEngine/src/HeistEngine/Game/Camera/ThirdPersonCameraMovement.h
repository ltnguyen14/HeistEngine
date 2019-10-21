#pragma once
#include "CameraMovement.h"
#include "Core/Manager/InputManager.h"

namespace Heist {
	class ThirdPersonCameraMovement : public CameraMovement {
	public:
		ThirdPersonCameraMovement();
		~ThirdPersonCameraMovement();

    void AttachCamera(Camera *camera) override;
		void Update() override;

	private:
		InputManager *inputManager;
    real64 old_x, old_y;
    bool rotationMode = false;
    bool movingMode = false;
    vec3 displacement = { 0, 0, 0};
	};
}
