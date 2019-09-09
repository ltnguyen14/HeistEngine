#version 410 core

in vec2 v_TexCoords;

out vec4 fragColor;
uniform sampler2D outTexture; 

void main() {
	fragColor = texture(outTexture, v_TexCoords);
}