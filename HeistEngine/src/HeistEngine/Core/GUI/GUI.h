#pragma once

namespace Heist {

	struct GUIElement {
  public:
	GUIElement(uint32 id, vec4 rect, vec4 color) :id(id), rect(rect), color(color) {}
    uint32 id;
    vec4 rect;
    vec4 color;
	};

}
