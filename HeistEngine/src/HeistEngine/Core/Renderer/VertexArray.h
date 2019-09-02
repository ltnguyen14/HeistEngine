#pragma once
#include "Macro.h"

namespace Heist {

	struct VertexArray {
		virtual ~VertexArray() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexArray* Create();

		uint32 vao;
	};
}