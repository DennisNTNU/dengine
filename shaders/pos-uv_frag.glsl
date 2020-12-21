#version 330 core

in vec2 fragmentUV;

out vec4 color;

uniform sampler2D textureSampler;

void main()
{
    //color = vec4(fragmentUV, texture(textureSampler, fragmentUV).b, 1.0);
    color = texture(textureSampler, fragmentUV);
}