#version 460 core

in vec2 texCoords;

uniform sampler2D text;
uniform vec3 fragColor;

out vec4 FragColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);
    FragColor = vec4(fragColor, 1.0f) * sampled;
}
