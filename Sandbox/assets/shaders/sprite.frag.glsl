#version 410 core

in vec4 v_Color;

out vec4 fragColor;
uniform sampler2D outTexture; 

void main() {
	fragColor = v_Color;
}