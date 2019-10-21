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
  float ambientStrength = 0.8f;
  float diffuseAmbientStrength = 0.1f;
  float specularStrength = 0.4f;
  float diffuseStrength = 1.0f;

	// Ambient	
	vec3 ambient = material.ambient * light.ambient * ambientStrength;

  // Diffuse ambient
  vec3 diffuseAmbient = material.diffuse * light.diffuse * diffuseAmbientStrength;
  
	// Diffuse
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(light.position - v_FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * material.diffuse * light.diffuse * diffuseStrength;

	// Specular
	vec3 viewDir = normalize(viewPosition - v_FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = material.specular * spec * light.specular * specularStrength;

	vec3 color;
  if (material.specularHighlight)
    color = ambient + diffuseAmbient + diffuse + specular;
  else
    color = ambient + diffuseAmbient + diffuse;
	return vec4(color, 1.0);
}

void main() {
	fragColor = CalculateLighting();
}
