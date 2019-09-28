#include "hspch.h"
#include "Camera.h"

namespace Heist {

	Camera::Camera(vec3 position, vec3 rotation, vec4 dimensions, bool ortho)
		:position(position), c_position(position), rotation(rotation), c_rotation(rotation), ortho(ortho)
	{
		if (ortho) {
			projectionMatrix = MakeOrthoMatrix(dimensions.x, dimensions.y, dimensions.w, dimensions.h, -1000, 1000);
		} else {
			projectionMatrix = MakePerspectiveMatrix(90, dimensions.y / dimensions.w, 0.1f, 100.0f);
		}

		CalculateViewMatrix();
	}

	Camera::~Camera() {

	}

	void Camera::Update() {
		if (position != c_position || rotation != c_rotation) {
			c_position = position;
			c_rotation = rotation;
			this->CalculateViewMatrix();
		}
	}

	void Camera::UpdateDimension(vec4 dimensions) {
		if (ortho) {
			projectionMatrix = MakeOrthoMatrix(dimensions.x, dimensions.y, dimensions.w, dimensions.h, -1000, 1000);
		}
		else {
			projectionMatrix = MakePerspectiveMatrix(90, dimensions.y / dimensions.w, 0.1f, 100.0f);
		}

		CalculateViewMatrix();
	}

	void Camera::CalculateViewMatrix() {
		viewMatrix = mat4(1);
		viewMatrix = translate(viewMatrix, { -position.x, -position.y, -position.z });

		viewMatrix = rotate(viewMatrix, rotation.x, { 1, 0, 0 });
		viewMatrix = rotate(viewMatrix, rotation.y, { 0, 1, 0 });
		viewMatrix = rotate(viewMatrix, rotation.z, { 0, 0, 1 });

		projectionViewMatrix = viewMatrix * projectionMatrix;
	}

	void Camera::CalculateProjectionMatrix(vec4 dimensions) {
		if (ortho) {
			projectionMatrix = MakeOrthoMatrix(dimensions.x, dimensions.y, dimensions.w, dimensions.h, -1000, 1000);
		}
		else {
			projectionMatrix = MakePerspectiveMatrix(45, dimensions.y / dimensions.w, 0.1f, 100.0f);
		}
	}
}