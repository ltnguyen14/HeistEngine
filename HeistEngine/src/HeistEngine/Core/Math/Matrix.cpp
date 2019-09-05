#include "hspch.h"
#include "Matrix.h"
#include "Platform/Assertions.h"

namespace Heist {

	std::array<real32, 3>& mat3::operator [] (int32 i) {
		HS_CORE_ASSERT(i >= 0 && i <= 3, "Index out of range");
		return data[i];
	}

	const std::array<real32, 3>& mat3::operator [] (int32 i) const {
		HS_CORE_ASSERT(i >= 0 && i <= 3, "Index out of range");
		return data[i];
	}

	mat3::mat3(bool identity = false) {
		if (identity) {
			data[0][0] = 1; data[0][1] = 0; data[0][2] = 0; 
			data[1][0] = 0; data[1][1] = 1; data[1][2] = 0; 
			data[2][0] = 0; data[2][1] = 0; data[2][2] = 1; 
		}
		else {
			data[0][0] = 0; data[0][1] = 0; data[0][2] = 0;
			data[1][0] = 0; data[1][1] = 0; data[1][2] = 0;
			data[2][0] = 0; data[2][1] = 0; data[2][2] = 0;
		}
	}

	//---------------------------------------------------------------------

	mat4::mat4(bool identity) {
		if (identity) {
			data[0][0] = 1; data[0][1] = 0; data[0][2] = 0; data[0][3] = 0;
			data[1][0] = 0; data[1][1] = 1; data[1][2] = 0; data[1][3] = 0;
			data[2][0] = 0; data[2][1] = 0; data[2][2] = 1; data[2][3] = 0;
			data[3][0] = 0; data[3][1] = 0; data[3][2] = 0; data[3][3] = 1;
		}
		else {
			data[0][0] = 0; data[0][1] = 0; data[0][2] = 0; data[0][3] = 0;
			data[1][0] = 0; data[1][1] = 0; data[1][2] = 0; data[1][3] = 0;
			data[2][0] = 0; data[2][1] = 0; data[2][2] = 0; data[2][3] = 0;
			data[3][0] = 0; data[3][1] = 0; data[3][2] = 0; data[3][3] = 0;
		}
	}

	std::array<real32, 4> & mat4::operator[](int32 i) {
		HS_CORE_ASSERT(i >= 0 && i <= 4, "Index out of range");
		return data[i];
	}

	const std::array<real32, 4> & mat4::operator[](int32 i) const {
		HS_CORE_ASSERT(i >= 0 && i <= 4, "Index out of range");
		return data[i];
	}

	mat4 mat4::translate(vec3 v) {
		return {
			data[0][0], data[0][1], data[0][2], data[0][3],
			data[1][0], data[1][1], data[1][2], data[1][3],
			data[2][0], data[2][1], data[2][2], data[2][3],
			v.x,		-v.y,		v.z,		data[3][3],
		};
	}

	//---------------------------------------------------------------------

	mat4 MakeOrthoMatrix(real32 left, real32 right, real32 top, real32 bottom, real32 farPlane, real32 nearPlane)
	{
		mat4 data = mat4(1);

		data[0][0] =  2 / (right - left); 
		data[1][1] =  2 / (top - bottom); 
		data[2][2] = -2 / (farPlane - nearPlane);
		
		data[3][0] = -(right + left) / (right - left);
		data[3][1] = -(top + bottom) / (top - bottom);
		data[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);

		return data;
	}
}