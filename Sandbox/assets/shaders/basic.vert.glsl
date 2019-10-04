#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 projectionViewMatrix;
uniform mat4 modelMatrix;

out vec3 v_Normal;
out vec2 v_TexCoord;
out vec3 v_FragPosition;

void main() {
	gl_Position = projectionViewMatrix * modelMatrix * vec4(aPos, 1.0);
	v_Normal = mat3(transpose(inverse(modelMatrix))) * aNormal; // This does not account for non-uniform scaling
	v_FragPosition = vec3(modelMatrix * vec4(aPos, 1.0));
	v_TexCoord = aTexCoord;
}