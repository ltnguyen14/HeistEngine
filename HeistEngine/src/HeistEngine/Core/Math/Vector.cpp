#include "hspch.h"
#include "Math.h"

namespace Heist {
	// vec3 and ivec3 --------------------------------
	// -----------------------------------------------

	// Scalar mul
	inline vec3 operator * (const vec3& v, real32 s) {
		return vec3{ v.x * s, v.y * s, v.z * s };
	}

	inline ivec3 operator * (const ivec3& v, int32 s) {
		return ivec3{ v.x * s, v.y * s, v.z * s };
	}

	inline vec3 operator / (const vec3& v, real32 s) {
		s = 1.0f / s;
		return v * s;
	}

	// NOTE(LAM): This might be a bit weird
	inline ivec3 operator / (const ivec3& v, real32 s) {
		s = 1.0f / s;
		return v * s;
	}

	inline vec3 operator - (const vec3& v) {
		return vec3{ -v.x, -v.y, -v.y };
	}

	inline ivec3 operator - (const ivec3& v) {
		return ivec3{ -v.x, -v.y, -v.z };
	}

	inline vec3 operator + (const vec3& v, const vec3& v2) {
		return vec3{ v.x + v2.x, v.y + v2.y, v.z + v2.z };
	}

	inline ivec3 operator + (const ivec3& v, const ivec3& v2) {
		return ivec3{ v.x + v2.x, v.y + v2.y, v.z + v2.z };
	}

	inline vec3 operator - (const vec3& v, const vec3& v2) {
		return vec3{ v.x + v2.x, v.y + v2.y, v.z + v2.z };
	}

	inline ivec3 operator - (const ivec3& v, const ivec3& v2) {
		return ivec3{ v.x + v2.x, v.y + v2.y, v.z + v2.z };
	}

	inline real32 Magnitude(const vec3& v) {
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	inline real32 Magnitude(const ivec3& v) {
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	inline vec3 Normalize(const vec3& v) {
		return (v / Magnitude(v));
	}

	inline ivec3 Normalize(const ivec3& v) {
		return (v / Magnitude(v));
	}

	// -----------------------------------------------
	// vec4 and ivec4 --------------------------------
	// -----------------------------------------------

	// Scalar mul
	inline vec4 operator * (const vec4& v, real32 s) {
		return vec4{ v.x * s, v.y * s, v.z * s, v.q * s };
	}

	inline ivec4 operator * (const ivec4& v, int32 s) {
		return ivec4{ v.x * s, v.y * s, v.z * s, v.q * s };
	}

	inline vec4 operator / (const vec4& v, real32 s) {
		s = 1.0f / s;
		return v * s;
	}

	// NOTE(LAM): This might be a bit weird
	inline ivec4 operator / (const ivec4& v, real32 s) {
		s = 1.0f / s;
		return v * s;
	}

	inline vec4 operator - (const vec4& v) {
		return vec4{ -v.x, -v.y, -v.y, -v.q };
	}

	inline ivec4 operator - (const ivec4& v) {
		return ivec4{ -v.x, -v.y, -v.z, -v.q };
	}

	inline vec4 operator + (const vec4& v, const vec4& v2) {
		return vec4{ v.x + v2.x, v.y + v2.y, v.z + v2.z, v.q + v2.q };
	}

	inline ivec4 operator + (const ivec4& v, const ivec4& v2) {
		return ivec4{ v.x + v2.x, v.y + v2.y, v.z + v2.z, v.q + v2.q };
	}

	inline vec4 operator - (const vec4& v, const vec4& v2) {
		return vec4{ v.x - v2.x, v.y - v2.y, v.z - v2.z, v.q - v2.q };
	}

	inline ivec4 operator - (const ivec4& v, const ivec4& v2) {
		return ivec4{ v.x - v2.x, v.y - v2.y, v.z - v2.z, v.q - v2.q };
	}

	inline real32 Magnitude(const vec4& v) {
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.q * v.q);
	}

	inline real32 Magnitude(const ivec4& v) {
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.q * v.q);
	}

	inline vec4 Normalize(const vec4& v) {
		return (v / Magnitude(v));
	}

	inline ivec4 Normalize(const ivec4& v) {
		return (v / Magnitude(v));
	}
	// -----------------------------------------------
}