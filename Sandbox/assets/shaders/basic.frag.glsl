#version 410 core

in vec2 v_Normals;

out vec4 fragColor;
uniform sampler2D outTexture; 

vec4 CalculateLighting(vec3 lightColor, vec3 objectColor) {
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;

	vec3 color = ambient * objectColor;
	return vec4(color, 1.0);
}

void main() {
	// fragColor = texture(outTexture, v_TexCoords);
	vec3 lightColor = vec3(1, 1, 1);
	vec3 objectColor = vec3(0.2, 0.4, 0.8);
	fragColor = CalculateLighting(lightColor, objectColor);
}