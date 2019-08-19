#pragma once
#include "../Macro.h"

// Vectors
namespace Heist {
	typedef union vec3 {
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

	typedef union ivec3 {
		struct {
			int32 x;
			int32 y;
			int32 z;
		};
		struct {
			int32 r;
			int32 g;
			int32 b;
		};
	} ivec3;

	typedef union vec4 {
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

	typedef union ivec4 {
		struct {
			int32 x;
			int32 y;
			int32 z;
			int32 q;
		};
		struct {
			int32 r;
			int32 g;
			int32 b;
			int32 a;
		};
		struct {
			int32 x;
			int32 y;
			int32 w;
			int32 h;
		};
	} ivec4;

}
