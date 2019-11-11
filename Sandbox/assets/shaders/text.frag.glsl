#version 410 core

in vec2 v_textureCoords;
in vec4 v_color;

out vec4 fragColor;
uniform sampler2D outTexture; 

const float width = 0.45f;
const float edge = 0.15f;

void main() {
	float distance =  1.0f - texture(outTexture, v_textureCoords).a;
  float alpha = 1.0f - smoothstep(width, width + edge, distance);

  fragColor = vec4(v_color.r, v_color.g, v_color.b, alpha);
  // fragColor = vec4(0.2f, 0.4f, 0.9f, 1.0f);
}
