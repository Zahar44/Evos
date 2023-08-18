#version 460 core

uniform vec3 color;
uniform vec3 viewPosition;

in vec3 normal;
in vec3 fragmentPosition;

out vec4 FragColor;

struct DirectionalLight {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform DirectionalLight directional;

// calculates the color when using a directional light.
vec3 calculateDirectionalLight(vec3 normalizedNormal, vec3 viewDirection)
{
    vec3 lightDir = normalize(directional.direction);
    // diffuse shading
    float diff = max(dot(normalizedNormal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normalizedNormal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), 16.0f);
    // combine results
    vec3 ambient = directional.ambient;
    vec3 diffuse = directional.diffuse * diff;
    vec3 specular = directional.specular * spec;
    return (ambient + diffuse + specular);
}


void main()
{
    vec3 normalizedNormal = normalize(normal);
    vec3 viewDirection = normalize(viewPosition - fragmentPosition);

    vec3 result = calculateDirectionalLight(normalizedNormal, viewDirection);

    FragColor = vec4(color * result, 1.0f);
}
