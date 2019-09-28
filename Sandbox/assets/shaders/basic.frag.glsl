#version 410 core

in vec2 v_TexCoords;

out vec4 fragColor;
uniform sampler2D outTexture; 

void main() {
	// fragColor = texture(outTexture, v_TexCoords);
	fragColor = vec4(0.2f, 0.4f, 0.8f, 1.0f);
}