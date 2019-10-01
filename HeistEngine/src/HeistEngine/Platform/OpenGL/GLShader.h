#pragma once
#include "Core/Renderer/Shader.h"

namespace Heist {

	struct GLShader : public Shader {

		GLShader(const char* vertexPath, const char* fragPath);
		virtual ~GLShader();

		int32 LoadShader(const char* vertexPath, const char* fragPath);
		void UploadUniformMat4(const char* uniformName, const mat4* matrix) override;
		void UploadUniformVec3(const char* uniformName, const vec3* vector) override;
		void UploadUniformVec4(const char* uniformName, const vec4* vector) override;

		void Bind() const;
		void Unbind() const;

	private:

		void CheckCompileStatus(int32 shaderId, const char* shaderName) const;
		void CheckLinkingStatus() const;
	};

}