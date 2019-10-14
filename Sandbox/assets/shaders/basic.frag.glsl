#version 410 core

// Structs
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float reflectiveness;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// In
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_FragPosition;

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

// Out
out vec4 fragColor;


vec4 CalculateLighting() {
	// Ambient	
	vec3 ambient = vec3(texture(material.diffuse, v_TexCoord)) * light.ambient;
  
	// Diffuse
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(light.position - v_FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(texture(material.diffuse, v_TexCoord)) * light.diffuse;

	// Specular
	vec3 viewDir = normalize(viewPosition - v_FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.reflectiveness);
	vec3 specular = vec3(texture(material.specular, v_TexCoord)) * spec * light.specular;

	vec3 color = ambient + diffuse + specular;
	return vec4(color, 1.0);
}

void main() {
	fragColor = CalculateLighting();
}
