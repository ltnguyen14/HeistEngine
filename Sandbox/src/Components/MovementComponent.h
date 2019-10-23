#pragma once
#include <HeistEngine.h>

struct MovementComponent : public Heist::BaseComponent {

	MovementComponent(Heist::vec3 position, Heist::vec3 rotation, Heist::vec3 scale)
		: position(position), rotation(rotation), scale(scale) {};

	Heist::vec3 position = { 0, 0, 0 };
  Heist::vec3 rotation = { 0, 0, 0 };
  Heist::vec3 scale = { 1, 1, 1 };

	static int32 componentTypeId;
	static std::string name;
};
