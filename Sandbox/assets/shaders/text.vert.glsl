#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoords;
layout (location = 2) in vec4 aColor;

uniform mat4 projectionViewMatrix;
uniform mat4 modelMatrix;

out vec2 v_textureCoords;
out vec4 v_color;

void main() {
	gl_Position = projectionViewMatrix * modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
  v_textureCoords = aTextureCoords;
  v_color = aColor;
}
