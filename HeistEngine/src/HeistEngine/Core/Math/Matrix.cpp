#include "hspch.h"
#include "Matrix.h"
#include "Assertions.h"

namespace Heist {

	real32& mat3::operator () (int32 i, int32 j) {
		return (*this)[i][j];
	}

	const real32& mat3::operator () (int32 i, int32 j) const {
		return (*this)[i][j];
	}

	std::array<real32, 3>& mat3::operator [] (int32 i) {
		HS_CORE_ASSERT(i >= 0 && i <= 3, "Index out of range");
		return std::array<real32, 3>{ data[i * 3], data[i * 3 + 1], data[i * 3 + 2] };
	}

	const std::array<real32, 3>& mat3::operator [] (int32 i) const {
		HS_CORE_ASSERT(i >= 0 && i <= 3, "Index out of range");
		return std::array<real32, 3>{ data[i * 3], data[i * 3 + 1], data[i * 3 + 2] };
	}
}