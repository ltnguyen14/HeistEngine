#pragma once
#include "Macro.h"
#include "Core/Math/Math.h"

namespace Heist {

	struct Shader
	{
		virtual ~Shader() {};

		virtual int32 LoadShader(const char* vertexPath, const char* fragPath) = 0;

		virtual void UploadUniformMat4(const char* uniformName, const mat4* matrix) = 0;
		virtual void UploadUniformVec3(const char* uniformName, const vec3* vector) = 0;
		virtual void UploadUniformVec4(const char* uniformName, const vec4* vector) = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		uint32 programId;

		static Shader* Create(const char* vertexPath, const char* fragPath);
	};

}