#pragma once
#include "CameraMovement.h"
#include "Core/Manager/InputManager.h"

namespace Heist {
	class ThirdPersonCameraMovement : public CameraMovement {
	public:
		ThirdPersonCameraMovement();
		~ThirdPersonCameraMovement();

    void AttachCamera(Camera *camera);

		void Update() override;

	private:
		InputManager *inputManager;
    real64 old_x, old_y;
	};
}
