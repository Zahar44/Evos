#version 460 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 normal;
out vec3 fragmentPosition;

void main()
{
    vec4 worldVertexPosition = model * vec4(vertexPosition, 1.0);
    gl_Position = projection * view * worldVertexPosition;

    normal = normalize(mat3(transpose(inverse(model))) * vertexNormal);
    fragmentPosition = vec3(worldVertexPosition);
}
