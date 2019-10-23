#pragma once
#include <HeistEngine.h>

struct MovementComponent : public Heist::BaseComponent {

	MovementComponent(Heist::vec3 position, Heist::vec3 rotation)
		: position(position), rotation(rotation) {};

	Heist::vec3 position = { 0, 0, 0 };
  Heist::vec3 rotation = { 0, 0, 0 };

	static int32 componentTypeId;
	static std::string name;
};
