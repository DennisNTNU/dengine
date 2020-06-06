#version 330 core

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec2 vertexUV;
//in layout(location = 2) vec3 vertexNormal;


out vec2 fragmentUV;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspMatrix;

void main()
{
    gl_Position = perspMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);

    fragmentUV = vertexUV;
}