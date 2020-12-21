#version 330 core

layout(location = 0) in vec3 posAttr;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspMatrix;

void main()
{
    vec4 temp = perspMatrix * viewMatrix * modelMatrix * vec4(posAttr, 1.0);
    gl_Position = temp;
}
