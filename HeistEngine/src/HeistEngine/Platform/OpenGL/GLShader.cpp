#include "hspch.h"
#include "GLShader.h"
#include "glad/glad.h"

#include "Platform/Assertions.h"
#include "Core/FileSystem/FileManager.h"

namespace Heist {

	GLShader::GLShader(const char* vertexPath, const char* fragPath) {
		this->LoadShader(vertexPath, fragPath);
	}

	GLShader::~GLShader() {
		glDeleteProgram(programId);
	}

	int32 GLShader::LoadShader(const char* vertexPath, const char* fragPath) {
		std::string vertexSource = FileManager::ReadFile(vertexPath);
		std::string fragSource = FileManager::ReadFile(fragPath);

		const char* vertexContent = vertexSource.c_str();
		const char* fragContent = fragSource.c_str();

		// vertex shader
		uint32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexContent, nullptr);
		glCompileShader(vertexShader);
		this->CheckCompileStatus(vertexShader, "vertex shader");

		// fragment shader
		uint32 fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragContent, nullptr);
		glCompileShader(fragShader);
		this->CheckCompileStatus(fragShader, "fragment shader");

		// Link shader
		programId = glCreateProgram();
		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragShader);
		glLinkProgram(programId);
		this->CheckLinkingStatus();

		// Cleanup
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);

		this->Bind();

		return programId;
	}

	void GLShader::UploadUniformMat4(const char* uniformName, const mat4* matrix) {
		int32 matrixLocation = glGetUniformLocation(programId, uniformName);
		glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &(*matrix)[0][0]);
	}

	void GLShader::UploadUniformVec3(const char* uniformName, const vec3* vector) {
		int32 matrixLocation = glGetUniformLocation(programId, uniformName);
		glUniform3f(matrixLocation, vector->x, vector->y, vector->z);
	}
	void GLShader::UploadUniformVec4(const char* uniformName, const vec4* vector) {
		int32 matrixLocation = glGetUniformLocation(programId, uniformName);
		glUniform4f(matrixLocation, vector->x, vector->y, vector->z, vector->q);
	}

	void GLShader::Bind() const {
		glUseProgram(programId);
	}

	void GLShader::Unbind() const {
		glUseProgram(0);
	}

	void GLShader::CheckCompileStatus(int32 shaderId, const char* shaderName) const {
		int32 success;
		char infoLog[512];
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
			HS_CORE_ERROR("Compiling {0} failed: {1}", shaderName, infoLog);
		}
	}

	void GLShader::CheckLinkingStatus() const {
		int32 success;
		char infoLog[512];
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(programId, 512, nullptr, infoLog);
			HS_CORE_ERROR("Linking shaders failed: {0}", infoLog);
		}
	}

}