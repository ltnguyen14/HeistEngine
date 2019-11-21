#pragma once
#include "Macro.h"
#include "Core/Math/Math.h"

namespace Heist {

	struct GUIElement {
  public:
	GUIElement(uint32 id, vec4 rect, vec4 color) :id(id), rect(rect), color(color) {}
    uint32 id;
    vec4 rect;
    vec4 color;
	};

	struct GUIAutoLayout {
  GUIAutoLayout(vec4 rect, vec2 dimensionLimit) : rect(rect), dimensionLimit(dimensionLimit), xOffset(0), yOffset(0), xCount(0), yCount(0) {}

		vec4 rect;
		real32 xOffset, yOffset;
    uint32 xCount, yCount; // This is just the running count, not total
    vec2 dimensionLimit;
	};
}
