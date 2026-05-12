#version 460 core
out vec4 FragColor;

in vec3 vPos;
in vec3 vNorm;
in vec2 texCoord;

uniform sampler2D texture0;

uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{
	FragColor = texture(texture0, texCoord);
}