#pragma once
#include "../Components/MovementComponent.h"

struct MovementSystem : public Heist::BaseSystem {
	MovementSystem() {}

	static void Update(real32 delta);
};
