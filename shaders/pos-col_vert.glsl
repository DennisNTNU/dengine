#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;

out vec4 fragmentColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspMatrix;

void main()
{
    gl_Position = perspMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);

    fragmentColor = vertexColor;
}