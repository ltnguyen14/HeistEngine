#version 410 core

in vec3 v_Normal;
in vec3 v_FragPosition;

out vec4 fragColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

vec4 CalculateLighting(vec3 lightColor, vec3 objectColor) {
	// Ambient	
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(lightPosition - v_FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// Specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPosition - v_FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 color = (ambient + diffuse + specular) * objectColor;
	return vec4(color, 1.0);
}

void main() {
	vec3 lightColor = vec3(1, 1, 1);
	vec3 objectColor = vec3(0.2, 0.4, 0.8);
	fragColor = CalculateLighting(lightColor, objectColor);
}