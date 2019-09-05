#pragma once
#include "Vector.h"
#include "Macro.h"

namespace Heist {

	struct mat3 {

		mat3(bool identity);
		mat3(real32 n00, real32 n01, real32 n02,
			real32 n10, real32 n11, real32 n12,
			real32 n20, real32 n21, real32 n22) {

			data[0][0] = n00; data[0][1] = n01; data[0][2] = n02;
			data[1][0] = n10; data[1][1] = n11; data[1][2] = n12;
			data[2][0] = n20; data[2][1] = n21; data[2][2] = n22;
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

	struct mat4 {

		mat4() = default;
		mat4(bool identity);
		mat4(real32 n00, real32 n01, real32 n02, real32 n03,
			 real32 n10, real32 n11, real32 n12, real32 n13,
			 real32 n20, real32 n21, real32 n22, real32 n23,
			 real32 n30, real32 n31, real32 n32, real32 n33) {
			 
			data[0][0] = n00; data[0][1] = n01; data[0][2] = n02; data[0][3] = n03;
			data[1][0] = n10; data[1][1] = n11; data[1][2] = n12; data[1][3] = n13;
			data[2][0] = n20; data[2][1] = n21; data[2][2] = n22; data[2][3] = n23;
			data[3][0] = n30; data[3][1] = n31; data[3][2] = n32; data[3][3] = n33;
		}

		mat4(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4) {

			data[0][0] = v1.x; data[0][1] = v1.y; data[0][2] = v1.z; data[0][3] = v1.q;
			data[1][0] = v3.x; data[1][1] = v2.y; data[1][2] = v2.z; data[1][3] = v2.q;
			data[2][0] = v3.x; data[2][1] = v3.y; data[2][2] = v3.z; data[2][3] = v3.q;
			data[3][0] = v4.x; data[3][1] = v4.y; data[3][2] = v4.z; data[3][3] = v4.q;
		}

		std::array<real32, 4> & mat4::operator [] (int32 i);
		const std::array<real32, 4> & mat4::operator [] (int32 i) const;

		mat4 translate(vec3 v);

		std::array<std::array<real32, 4>, 4> data;
	};

	mat4 MakeOrthoMatrix(real32 left, real32 right, real32 top, real32 bottom, real32 farPlane, real32 nearPlane);
}