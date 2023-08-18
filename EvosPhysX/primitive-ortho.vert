#version 460 core
layout (location = 0) in vec2 vertexPosition;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    vec4 position = projection * model * vec4(vertexPosition, 0.0, 1.0);
    position.z = model[3][2]; // z layer
    gl_Position = position;
}
