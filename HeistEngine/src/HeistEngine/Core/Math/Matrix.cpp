#include "hspch.h"
#include "Matrix.h"
#include "Assertions.h"

namespace Heist {

	std::array<real32, 3>& mat3::operator [] (int32 i) {
		HS_CORE_ASSERT(i >= 0 && i <= 3, "Index out of range");
		return data[i];
	}

	const std::array<real32, 3>& mat3::operator [] (int32 i) const {
		HS_CORE_ASSERT(i >= 0 && i <= 3, "Index out of range");
		return data[i];
	}
}