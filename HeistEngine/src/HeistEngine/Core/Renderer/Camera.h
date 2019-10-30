#pragma once
#include "Core/Math/Math.h"
#include "Core/Event/EventNode.h"

namespace Heist {

	struct Camera {

		Camera(vec3 position, vec3 rotation, vec4 dimensions, bool ortho = true);
		~Camera();

		void Update();
		void UpdateDimension(vec4 dimensions);

		// ----------
		vec3 position;
		vec3 rotation;
		bool ortho;

		mat4 projectionMatrix;
		mat4 viewMatrix;
		mat4 projectionViewMatrix;

	private:
		vec3 c_position, c_rotation;
		void CalculateViewMatrix();
	};

}