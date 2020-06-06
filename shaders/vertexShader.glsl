#version 330 core

layout(location = 0) in vec2 posAttr;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspMatrix;

void main()
{
    vec4 temp = perspMatrix * viewMatrix * modelMatrix * vec4(posAttr, 0.0, 1.0);
    gl_Position = temp;
}
