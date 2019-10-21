#pragma once
#include "Core/Renderer/Camera.h"

namespace Heist {
	class CameraMovement {
	public:
		CameraMovement() {};
		virtual ~CameraMovement() {};

		virtual void AttachCamera(Camera* camera) { };
		virtual void Update() = 0;

		Camera* camera = nullptr;
	};
}
