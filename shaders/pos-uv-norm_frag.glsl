#version 330 core

in vec3 fragmentPosition;
in vec2 fragmentUV;
in vec3 fragmentNormal;

out vec4 color;

vec3 sunDir = vec3(0.0, 0.7071067, 0.7071067);
//vec3 sunColor = vec3(1.0, 0.9, 0.7);
vec3 sunColor = vec3(1.0, 0.0, 0.0);

uniform mat4 viewMatrix;
uniform sampler2D textureSampler;

void main()
{
	mat4 viewInv = inverse(viewMatrix);
	vec3 camPos = vec3(viewInv[3][0], viewInv[3][1], viewInv[3][2]);

	//vec3 textureColor = texture(textureSampler, fragmentUV).xyz;
	vec3 textureColor = vec3(0.8, 0.8, 0.8);

	vec3 Idiff = textureColor * max(dot(fragmentNormal, sunDir), 0.0);  
	Idiff = clamp(Idiff, 0.0, 1.0);

	vec3 reflectDir = normalize(2.0*dot(sunDir, fragmentNormal)*(fragmentNormal) - sunDir);
	vec3 viewDir = normalize(camPos - fragmentPosition);
	float specular = min(pow(min(max(0.0, dot(reflectDir, viewDir)), 1.0), 32.0), 1.0);
	vec3 Ispec = clamp(specular*sunColor, 0.0, 1.0);

    color = vec4(clamp(0.1*textureColor + Ispec + Idiff, 0.0, 1.0), 1.0);
    //color = vec4(0.1, 0.1, 0.1, 0.5);
}
