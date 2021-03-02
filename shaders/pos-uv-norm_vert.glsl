#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec3 fragmentPosition;
out vec2 fragmentUV;
out vec3 fragmentNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspMatrix;

void main()
{
	vec4 globalPos = modelMatrix * vec4((vertexPosition), 1.0);
    gl_Position = perspMatrix * viewMatrix * globalPos;
	vec3 globalNormal = (modelMatrix * vec4(vertexNormal, 0.0)).xyz;

	fragmentPosition = globalPos.xyz;
    fragmentUV = vertexUV;
	fragmentNormal = globalNormal;
}
