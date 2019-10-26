#pragma once
#include "Macro.h"

namespace Heist {

	static int32 entityId = 0;

	struct Entity {
		Entity(std::string name) : name(name) { id = ++entityId; };
		int32 id;
		std::string name;
	};

}