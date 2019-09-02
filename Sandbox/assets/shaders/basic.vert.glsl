#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 v_Color;

void main() {
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	v_Color = aColor;
}