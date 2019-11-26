#pragma once
#include "Macro.h"

// Vectors
namespace Heist {
	typedef union vec2 {
		vec2() = default;
		vec2(real32 x, real32 y) : x(x), y(y) {};
		struct {
			real32 x;
			real32 y;
		};
	} vec2;

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
  vec4(const vec3& vector, real32 a) : x(vector.r), y(vector.g), z(vector.b), a(a) {};

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

	// vec2 ------------------------------------------
	// -----------------------------------------------

	// Scalar mul
	inline vec2 operator * (const vec2& v, real32 s) {
		return vec2{ v.x * s, v.y * s };
	}

	inline vec2 operator / (const vec2& v, real32 s) {
		s = 1.0f / s;
		return v * s;
	}

	inline vec2 operator - (const vec2& v) {
		return vec2{ -v.x, -v.y };
	}

	inline vec2 operator + (const vec2& v, const vec2& v2) {
		return vec2{ v.x + v2.x, v.y + v2.y };
	}

	inline vec2 operator - (const vec2& v, const vec2& v2) {
		return v + (-v2);
	}

	inline bool operator == (const vec2& v, const vec2& v2) {
		return (v.x == v2.x) && (v.y == v2.y);
	}

	inline bool operator != (const vec2& v, const vec2& v2) {
		return !(v == v2);
	}

	inline real32 Magnitude(const vec2& v) {
		return sqrt(v.x * v.x + v.y * v.y);
	}

	inline vec2 Normalize(const vec2& v) {
		return (v / Magnitude(v));
	}

	// vec3 ------------------------------------------
	// -----------------------------------------------

	// Scalar mul
	inline vec3 operator * (const vec3& v, real32 s) {
		return vec3{ v.x * s, v.y * s, v.z * s };
	}

	inline vec3 operator * (real32 s, const vec3& v) {
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
		return v + (-v2);
	}

	inline bool operator == (const vec3& v, const vec3& v2) {
		return (v.x == v2.x) && (v.y == v2.y) && (v.z == v2.z);
	}

	inline bool operator != (const vec3& v, const vec3& v2) {
		return !(v == v2);
	}

	inline real32 Magnitude(const vec3& v) {
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	inline vec3 Normalize(const vec3& v) {
		return (v / Magnitude(v));
	}

  inline vec3 Cross(const vec3& v1, const vec3& v2) {
    vec3 result = {};

    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;

    return result;
  }

	// -----------------------------------------------
	// vec4 ------------------------------------------
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
		return v + (-v2);
	}

	inline bool operator == (const vec4& v, const vec4& v2) {
		return (v.x == v2.x) && (v.y == v2.y) && (v.z == v2.z) && (v.q == v2.q);
	}

	inline bool operator != (const vec4& v, const vec4& v2) {
		return !(v == v2);
	}

	inline real32 Magnitude(const vec4& v) {
		return (real32)sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.q * v.q);
	}

	inline vec4 Normalize(const vec4& v) {
		return (v / Magnitude(v));
	}

	// -----------------------------------------------

  inline uint32 RoundReal32ToUInt32(real32 value)
  {
    return (uint32)roundf(value);
  }

  inline uint32 BGRAPack4x8(vec4 unpacked) {
    uint32 result = ((RoundReal32ToUInt32(unpacked.a) << 24) |
                     (RoundReal32ToUInt32(unpacked.r) << 16) |
                     (RoundReal32ToUInt32(unpacked.g) << 8) |
                     (RoundReal32ToUInt32(unpacked.b) << 0));
    return result;
  }

  inline real32 Inner(const vec3& v1, const vec3& v2) {
    real32 result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
    return result;
  }

  inline real32 Inner(const vec2& v1, const vec2& v2) {
    real32 result = (v1.x * v2.x) + (v1.y * v2.y);
  }
}
