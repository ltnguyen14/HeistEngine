#version 410 core

in vec2 v_textureCoords;
in vec4 v_color;

out vec4 fragColor;
uniform sampler2D outTexture; 

void main() {
	float alpha = texture(outTexture, v_textureCoords).a;
  fragColor = vec4(v_color.r, v_color.g, v_color.b, alpha);
}
