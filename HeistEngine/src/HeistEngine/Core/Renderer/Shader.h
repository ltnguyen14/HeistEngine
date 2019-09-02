#pragma once
#include "Macro.h"

namespace Heist {

	struct Shader
	{
		virtual ~Shader() {};

		virtual int32 LoadShader(const char* vertexPath, const char* fragPath) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		uint32 programId;

		static Shader* Create(const char* vertexPath, const char* fragPath);
	};

}