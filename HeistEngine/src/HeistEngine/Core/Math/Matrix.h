#pragma once
#include "Vector.h"
#include "Macro.h"

namespace Heist {

	struct mat3 {

		mat3() = default;
		mat3(real32 n00, real32 n01, real32 n02,
			real32 n10, real32 n11, real32 n12,
			real32 n20, real32 n21, real32 n22) {

			data[0][0] = n00; data[0][1] = n01; data[0][2] = n02;
			data[1][0] = n00; data[1][1] = n01; data[1][2] = n02;
			data[2][0] = n00; data[2][1] = n01; data[2][2] = n02;
		}

		mat3(const vec3& v1, const vec3& v2, const vec3& v3) {
			
			data[0][0] = v1.x; data[0][1] = v1.y; data[0][2] = v1.z;
			data[1][0] = v3.x; data[1][1] = v2.y; data[1][2] = v2.z;
			data[2][0] = v3.x; data[2][1] = v3.y; data[2][2] = v3.z;
		}

		std::array<real32, 3>& mat3::operator [] (int32 i);
		const std::array<real32, 3>& mat3::operator [] (int32 i) const;

		std::array<real32, 3> data[3];
	};

}