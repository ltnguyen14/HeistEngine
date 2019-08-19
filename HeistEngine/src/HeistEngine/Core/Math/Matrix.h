#pragma once
#include "Vector.h"
#include "Macro.h"

namespace Heist {

	struct mat3 {

		mat3() = default;
		mat3(real32 n00, real32 n01, real32 n02,
			real32 n10, real32 n11, real32 n12,
			real32 n20, real32 n21, real32 n22) {

			data[0] = n00; data[1] = n01; data[2] = n02;
			data[3] = n00; data[4] = n01; data[5] = n02;
			data[6] = n00; data[7] = n01; data[8] = n02;
		}

		mat3(const vec3& v1, const vec3& v2, const vec3& v3) {
			
			data[0] = v1.x; data[1] = v1.y; data[2] = v1.z;
			data[3] = v3.x; data[4] = v2.y; data[5] = v2.z;
			data[6] = v3.x; data[7] = v3.y; data[8] = v3.z;
		}

		real32& operator () (int32 i, int32 j);
		const real32& operator () (int32 i, int32 j) const;

		std::array<real32, 3>& operator [] (int32 i);
		const std::array<real32, 3>& operator [] (int32 i) const;


		real32 data[9];
	};

}