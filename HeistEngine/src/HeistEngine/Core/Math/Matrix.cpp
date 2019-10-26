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

	std::array<real32, 4>& mat4::operator[](int32 i) {
		HS_CORE_ASSERT(i >= 0 && i <= 4, "Index out of range");
		return data[i];
	}

	const std::array<real32, 4>& mat4::operator[](int32 i) const {
		HS_CORE_ASSERT(i >= 0 && i <= 4, "Index out of range");
		return data[i];
	}

	//---------------------------------------------------------------------

	mat4 MakeOrthoMatrix(real32 left, real32 right, real32 bottom, real32 top, real32 nearPlane, real32 farPlane)
	{
		mat4 data = mat4(1);

		data[0][0] = 2 / (right - left);
		data[1][1] = 2 / (top - bottom);
		data[2][2] = -2 / (farPlane - nearPlane);

		data[3][0] = -(right + left) / (right - left);
		data[3][1] = -(top + bottom) / (top - bottom);
		data[3][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);

		return data;
	}

	mat4 MakePerspectiveMatrix(real32 fov, real32 aspect, real32 nearPlane, real32 farPlane) {
		mat4 data = mat4(1);
		float cotangent = 1.0f / tan(radian(fov) / 2);

		data[0][0] = cotangent / aspect;
		data[1][1] = cotangent;
		data[2][2] = (nearPlane + farPlane) / (nearPlane - farPlane);
		data[3][3] = 0.0f;

		data[3][2] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
		data[2][3] = -1.0f;

		return data;
	}

	real32 radian(real32 degree) {
		return degree * PI / 180;
	}

	real32 degree(real32 radian) {
		return radian * (180 / PI);
	}

	mat4 translate(mat4 mat, vec3 v) {
		mat4 translationMatrix = {
			1,		0,		0,		0,
			0,		1,		0,		0,
			0,		0,		1,		0,
			v.x,	v.y,	v.z,	1
		};

		return mat * translationMatrix;
	}

	mat4 scale(mat4 mat, vec3 v) {
		mat4 scaleMatrix = {
			v.x,	0,		0,		0,
			0,		v.y,	0,		0,
			0,		0,		v.z,	0,
			0,		0,		0,		1
		};

		return mat * scaleMatrix;
	}

	mat4 rotate(mat4 mat, real32 rotation, vec3 axis) {
		mat4 xRot = {
			1, 0, 0, 0,
			0, cos(radian(-axis.x * rotation)), -sin(radian(-axis.x * rotation)),	0,
			0, sin(radian(-axis.x * rotation)), cos(radian(-axis.x * rotation)),	0,
			0, 0, 0, 1
		};

		mat4 yRot = {
			 cos(radian(-axis.y * rotation)), 0, sin(radian(-axis.y * rotation)), 0,
			 0,		1,		0,		0,
	   -sin(radian(-axis.y * rotation)), 0, cos(radian(-axis.y * rotation)), 0,
			 0,		0,		0,		1
		};

		mat4 zRot = {
			cos(radian(-axis.z * rotation)), -sin(radian(-axis.z * rotation)), 0, 0,
			sin(radian(-axis.z * rotation)),  cos(radian(-axis.z * rotation)), 0, 0,
			0,		0,		1,		0,
			0,		0,		0,		1
		};

		return mat * xRot * yRot * zRot;
	}

	mat4 MakeModelMatrix(const vec3& position, const vec3& rotation, const vec3& scaleVec) {
		mat4 modelMatrix = mat4(1);

		modelMatrix = translate(modelMatrix, position);

		modelMatrix = rotate(modelMatrix, rotation.x, { 1, 0, 0 });
		modelMatrix = rotate(modelMatrix, rotation.y, { 0, 1, 0 });
		modelMatrix = rotate(modelMatrix, rotation.z, { 0, 0, 1 });

		modelMatrix = scale(modelMatrix, scaleVec);

		return modelMatrix;
	}
}
