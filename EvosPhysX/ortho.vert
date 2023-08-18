#version 460 core
layout (location = 0) in vec4 vertexPositionAndTexture;

uniform mat4 projection;
uniform float layer;
out vec2 texCoords;

void main()
{
    gl_Position = projection * vec4(vertexPositionAndTexture.xy, layer, 1.0);
    texCoords = vertexPositionAndTexture.zw;
}
