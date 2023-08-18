#version 460 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in mat4 model;

struct Wave {
    vec2 direction;
    float frequency;
    float amplitude;
    float time;
};

uniform mat4 view;
uniform mat4 projection;
uniform Wave wave;

out vec3 normal;
out vec3 fragmentPosition;

void main()
{
    vec2 vertexXZ = vertexPosition.xz;

    float worldX = model[3][0];
    float worldZ = model[3][2];
    float waveX = worldX * wave.direction.x + worldZ * wave.direction.y;

    float vertexY = (vertexPosition.y + 1) / 2.0f;
    float waveY = sin(waveX * wave.frequency + wave.time) * wave.amplitude;
    vec2 displacement = vertexY * waveY * wave.direction;
    vertexXZ = vertexXZ + displacement;

    vec3 updatedVertexPosition = vec3(vertexXZ.x, vertexPosition.y, vertexXZ.y);

    vec4 worldVertexPosition = model * vec4(updatedVertexPosition, 1.0);
    gl_Position = projection * view * worldVertexPosition;

    normal = normalize(mat3(transpose(inverse(model))) * vertexNormal);
    fragmentPosition = vec3(worldVertexPosition);
}
