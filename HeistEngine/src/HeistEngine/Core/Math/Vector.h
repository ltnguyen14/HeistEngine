#pragma once
#include "Macro.h"

// Vectors
namespace Heist {
	typedef union vec3 {
		vec3() = default;
		vec3(real32 x, real32 y, real32 z) : x(x), y(y), z(z) {};
		struct {
			real32 x;
			real32 y;
			real32 z;
		};
		struct {
			real32 r;
			real32 g;
			real32 b;
		};
	} vec3;

	typedef union vec4 {
		vec4() = default;
		vec4(real32 x, real32 y, real32 z, real32 q) : x(x), y(y), z(z), q(q) {};

		struct {
			real32 x;
			real32 y;
			real32 z;
			real32 q;
		};
		struct {
			real32 r;
			real32 g;
			real32 b;
			real32 a;
		};
		struct {
			real32 x;
			real32 y;
			real32 w;
			real32 h;
		};
	} vec4;

	// vec3 ------------------------------------------
	// -----------------------------------------------

	// Scalar mul
	inline vec3 operator * (const vec3& v, real32 s) {
		return vec3{ v.x * s, v.y * s, v.z * s };
	}

	inline vec3 operator / (const vec3& v, real32 s) {
		s = 1.0f / s;
		return v * s;
	}

	inline vec3 operator - (const vec3& v) {
		return vec3{ -v.x, -v.y, -v.y };
	}

	inline vec3 operator + (const vec3& v, const vec3& v2) {
		return vec3{ v.x + v2.x, v.y + v2.y, v.z + v2.z };
	}

	inline vec3 operator - (const vec3& v, const vec3& v2) {
		return vec3{ v.x + v2.x, v.y + v2.y, v.z + v2.z };
	}

	inline real32 Magnitude(const vec3& v) {
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	inline vec3 Normalize(const vec3& v) {
		return (v / Magnitude(v));
	}

	// -----------------------------------------------
	// vec3 ------------------------------------------
	// -----------------------------------------------

	// Scalar mul
	inline vec4 operator * (const vec4& v, real32 s) {
		return vec4{ v.x * s, v.y * s, v.z * s, v.q * s };
	}

	inline vec4 operator / (const vec4& v, real32 s) {
		s = 1.0f / s;
		return v * s;
	}

	inline vec4 operator - (const vec4& v) {
		return vec4{ -v.x, -v.y, -v.y, -v.q };
	}

	inline vec4 operator + (const vec4& v, const vec4& v2) {
		return vec4{ v.x + v2.x, v.y + v2.y, v.z + v2.z, v.q + v2.q };
	}

	inline vec4 operator - (const vec4& v, const vec4& v2) {
		return vec4{ v.x - v2.x, v.y - v2.y, v.z - v2.z, v.q - v2.q };
	}

	inline real32 Magnitude(const vec4& v) {
		return (real32)sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.q * v.q);
	}

	inline vec4 Normalize(const vec4& v) {
		return (v / Magnitude(v));
	}

	// -----------------------------------------------
}
