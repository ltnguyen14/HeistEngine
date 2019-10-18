#version 410 core

// Structs
struct Material {
  vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
  bool specularHighlight;
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
	vec3 ambient = material.ambient * light.ambient;
  
	// Diffuse
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(light.position - v_FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * material.diffuse * light.diffuse;

	// Specular
	vec3 viewDir = normalize(viewPosition - v_FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = material.specular * spec * light.specular;

	vec3 color;
  if (material.specularHighlight)
    color = ambient + diffuse + specular;
  else
    color = ambient + diffuse;
	return vec4(color, 1.0);
}

void main() {
	fragColor = CalculateLighting();
}
