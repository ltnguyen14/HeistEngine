#pragma once
#include "Core/Math/Math.h"
#include "Core/Event/EventNode.h"

namespace Heist {

	struct Camera {

		Camera(vec3 position, vec3 rotation, vec4 dimensions, bool ortho = true);
		~Camera();

		void Update();

		// ----------
		vec3 position, c_position;
		vec3 rotation, c_rotation;
		bool ortho;

		mat4 projectionMatrix;
		mat4 viewMatrix;
		mat4 projectionViewMatrix;

	private:
		void CalculateViewMatrix();
	};

}